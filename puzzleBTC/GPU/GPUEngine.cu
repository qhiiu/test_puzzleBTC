
#include "GPUEngine.h"
#include <cuda.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#include <stdint.h>
#include "../hash/sha256.h" 
#include "../hash/ripemd160.h"
#include "../Timer.h"

#include "GPUMath.h"
#include "GPUHash.h"
#include "GPUBase58.h"
#include "GPUCompute.h"

// ---------------------------------------------------------------------------------------
#define CudaSafeCall( err ) __cudaSafeCall( err, __FILE__, __LINE__ )

inline void __cudaSafeCall(cudaError err, const char* file, const int line)
{
	if (cudaSuccess != err)
	{
		fprintf(stderr, "cudaSafeCall() failed at %s:%i : %s\n", file, line, cudaGetErrorString(err));
		exit(-1);
	}
	return;
}
// ---------------------------------------------------------------------------------------

// mode single address

__global__ void compute_keys_comp_mode_sa(uint32_t mode, uint32_t* hash160, uint64_t* keys, uint32_t maxFound, uint32_t* found)
{
	int xPtr = (blockIdx.x * blockDim.x) * 8;
	int yPtr = xPtr + 4 * blockDim.x;

	// printf("hiiu==computr_keys_comp_mode_sa -- gpuengine.cu------\n"); //result : much

	ComputeKeysSEARCH_MODE_SA(mode, keys + xPtr, keys + yPtr, hash160, maxFound, found);
}

// ---------------------------------------------------------------------------------------

using namespace std;

int _ConvertSMVer2Cores(int major, int minor)
{
	// Defines for GPU Architecture types (using the SM version to determine the # of cores per SM
	typedef struct {
		int SM;  // 0xMm (hexidecimal notation), M = SM Major version,
		// and m = SM minor version
		int Cores;
	} sSMtoCores;

	sSMtoCores nGpuArchCoresPerSM[] = {
		{0x20, 32}, // Fermi Generation (SM 2.0) GF100 class
		{0x21, 48}, // Fermi Generation (SM 2.1) GF10x class
		{0x30, 192},
		{0x32, 192},
		{0x35, 192},
		{0x37, 192},
		{0x50, 128},
		{0x52, 128},
		{0x53, 128},
		{0x60,  64},
		{0x61, 128},
		{0x62, 128},
		{0x70,  64},
		{0x72,  64},
		{0x75,  64},
		{0x80,  64},
		{0x86, 128},
		{-1, -1}
	};

	int index = 0;

	while (nGpuArchCoresPerSM[index].SM != -1) {
		if (nGpuArchCoresPerSM[index].SM == ((major << 4) + minor)) {return nGpuArchCoresPerSM[index].Cores;	}
		index++;
	}
	return 0;
}

// ----------------------------------------------------------------------------

GPUEngine::GPUEngine(Secp256K1* secp, int nbThreadGroup, int nbThreadPerGroup, int gpuId, uint32_t maxFound,
	int searchMode, int compMode, int coinType, const uint32_t* hashORxpoint)
{
	// Initialise CUDA
	this->nbThreadPerGroup = nbThreadPerGroup;
	this->searchMode = searchMode;
	this->compMode = compMode;
	this->coinType = coinType;

	initialised = false;

	int deviceCount = 0;
	CudaSafeCall(cudaGetDeviceCount(&deviceCount));

	CudaSafeCall(cudaSetDevice(gpuId));

	cudaDeviceProp deviceProp;
	CudaSafeCall(cudaGetDeviceProperties(&deviceProp, gpuId));

	if (nbThreadGroup == -1)
		nbThreadGroup = deviceProp.multiProcessorCount * 8;

	this->nbThread = nbThreadGroup * nbThreadPerGroup;
	this->maxFound = maxFound;
	this->outputSize = (maxFound * ITEM_SIZE_A + 4);

	char tmp[512];
	sprintf(tmp, "GPU #%d %s (%dx%d cores) Grid(%dx%d) \n",
		gpuId, deviceProp.name, deviceProp.multiProcessorCount,
		_ConvertSMVer2Cores(deviceProp.major, deviceProp.minor),
		nbThread / nbThreadPerGroup,
		nbThreadPerGroup);
	
	// printf("gpuId,deviceProp.name,deviceProp.multiProcessorCount,_ConvertSMVer2Cores(deviceProp.major,deviceProp.minor),nbThread / nbThreadPerGroup = nbThreadGroup,nbThreadPerGroup) \n\n");

	deviceName = std::string(tmp);

	// Prefer L1 (We do not use __shared__ at all)
	CudaSafeCall(cudaDeviceSetCacheConfig(cudaFuncCachePreferL1));

	size_t stackSize = 49152;
	CudaSafeCall(cudaDeviceSetLimit(cudaLimitStackSize, stackSize));

	// Allocate memory
	CudaSafeCall(cudaMalloc((void**)&inputKey, nbThread * 32 * 2));
	CudaSafeCall(cudaHostAlloc(&inputKeyPinned, nbThread * 32 * 2, cudaHostAllocWriteCombined | cudaHostAllocMapped));

	CudaSafeCall(cudaMalloc((void**)&outputBuffer, outputSize));
	CudaSafeCall(cudaHostAlloc(&outputBufferPinned, outputSize, cudaHostAllocWriteCombined | cudaHostAllocMapped));

	int K_SIZE = 5;

	CudaSafeCall(cudaMalloc((void**)&inputHashORxpoint, K_SIZE * sizeof(uint32_t)));
	CudaSafeCall(cudaHostAlloc(&inputHashORxpointPinned, K_SIZE * sizeof(uint32_t), cudaHostAllocWriteCombined | cudaHostAllocMapped));

	memcpy(inputHashORxpointPinned, hashORxpoint, K_SIZE * sizeof(uint32_t));

	CudaSafeCall(cudaMemcpy(inputHashORxpoint, inputHashORxpointPinned, K_SIZE * sizeof(uint32_t), cudaMemcpyHostToDevice));
	CudaSafeCall(cudaFreeHost(inputHashORxpointPinned));
	inputHashORxpointPinned = NULL;

	// generator table
	InitGenratorTable(secp);


	CudaSafeCall(cudaGetLastError());

	compMode = SEARCH_COMPRESSED;
	initialised = true;

}

// ----------------------------------------------------------------------------

void GPUEngine::InitGenratorTable(Secp256K1* secp)
{
	// generator table
	uint64_t* _2GnxPinned;
	uint64_t* _2GnyPinned;

	uint64_t* GxPinned;
	uint64_t* GyPinned;

	uint64_t size = (uint64_t)GRP_SIZE;

	CudaSafeCall(cudaMalloc((void**)&__2Gnx, 4 * sizeof(uint64_t)));
	CudaSafeCall(cudaHostAlloc(&_2GnxPinned, 4 * sizeof(uint64_t), cudaHostAllocWriteCombined | cudaHostAllocMapped));

	CudaSafeCall(cudaMalloc((void**)&__2Gny, 4 * sizeof(uint64_t)));
	CudaSafeCall(cudaHostAlloc(&_2GnyPinned, 4 * sizeof(uint64_t), cudaHostAllocWriteCombined | cudaHostAllocMapped));

	size_t TSIZE = (size / 2) * 4 * sizeof(uint64_t);
	CudaSafeCall(cudaMalloc((void**)&_Gx, TSIZE));
	CudaSafeCall(cudaHostAlloc(&GxPinned, TSIZE, cudaHostAllocWriteCombined | cudaHostAllocMapped));

	CudaSafeCall(cudaMalloc((void**)&_Gy, TSIZE));
	CudaSafeCall(cudaHostAlloc(&GyPinned, TSIZE, cudaHostAllocWriteCombined | cudaHostAllocMapped));


	Point* Gn = new Point[size];
	Point g = secp->G;
	Gn[0] = g;
	g = secp->DoubleDirect(g);
	Gn[1] = g;
	for (int i = 2; i < size; i++) {
		g = secp->AddDirect(g, secp->G);
		Gn[i] = g;
	}
	// _2Gn = CPU_GRP_SIZE*G
	Point _2Gn = secp->DoubleDirect(Gn[size / 2 - 1]);

	int nbDigit = 4;
	for (int i = 0; i < nbDigit; i++) {
		_2GnxPinned[i] = _2Gn.x.bits64[i];
		_2GnyPinned[i] = _2Gn.y.bits64[i];

	}
	for (int i = 0; i < size / 2; i++) {
		for (int j = 0; j < nbDigit; j++) {
			GxPinned[i * nbDigit + j] = Gn[i].x.bits64[j];
			GyPinned[i * nbDigit + j] = Gn[i].y.bits64[j];
		}
	}

	delete[] Gn;

	CudaSafeCall(cudaMemcpy(__2Gnx, _2GnxPinned, 4 * sizeof(uint64_t), cudaMemcpyHostToDevice));
	CudaSafeCall(cudaFreeHost(_2GnxPinned));
	_2GnxPinned = NULL;

	CudaSafeCall(cudaMemcpy(__2Gny, _2GnyPinned, 4 * sizeof(uint64_t), cudaMemcpyHostToDevice));
	CudaSafeCall(cudaFreeHost(_2GnyPinned));
	_2GnyPinned = NULL;

	CudaSafeCall(cudaMemcpy(_Gx, GxPinned, TSIZE, cudaMemcpyHostToDevice));
	CudaSafeCall(cudaFreeHost(GxPinned));
	GxPinned = NULL;

	CudaSafeCall(cudaMemcpy(_Gy, GyPinned, TSIZE, cudaMemcpyHostToDevice));
	CudaSafeCall(cudaFreeHost(GyPinned));
	GyPinned = NULL;

	CudaSafeCall(cudaMemcpyToSymbol(_2Gnx, &__2Gnx, sizeof(uint64_t*)));
	CudaSafeCall(cudaMemcpyToSymbol(_2Gny, &__2Gny, sizeof(uint64_t*)));
	CudaSafeCall(cudaMemcpyToSymbol(Gx, &_Gx, sizeof(uint64_t*)));
	CudaSafeCall(cudaMemcpyToSymbol(Gy, &_Gy, sizeof(uint64_t*)));

}

// ----------------------------------------------------------------------------

int GPUEngine::GetGroupSize()
{	return GRP_SIZE; }

// ----------------------------------------------------------------------------

void GPUEngine::PrintCudaInfo()
{
	printf("GPUEngine::PrintCudaInfo() : ");
	const char* sComputeMode[] = {
		"Multiple host threads",
		"Only one host thread",
		"No host thread",
		"Multiple process threads",
		"Unknown",
		NULL
	};

	int deviceCount = 0;
	CudaSafeCall(cudaGetDeviceCount(&deviceCount));

	for (int i = 0; i < deviceCount; i++) {
		CudaSafeCall(cudaSetDevice(i));
		cudaDeviceProp deviceProp;
		CudaSafeCall(cudaGetDeviceProperties(&deviceProp, i));
		printf("GPU #%d %s (%dx%d cores) (Cap %d.%d) (%.1f MB) (%s)\n",
			i, deviceProp.name, deviceProp.multiProcessorCount,
			_ConvertSMVer2Cores(deviceProp.major, deviceProp.minor),
			deviceProp.major, deviceProp.minor, (double)deviceProp.totalGlobalMem / 1048576.0,
			sComputeMode[deviceProp.computeMode]);
	}
}

// ----------------------------------------------------------------------------

GPUEngine::~GPUEngine()
{
	CudaSafeCall(cudaFree(inputKey));
	CudaSafeCall(cudaFree(inputHashORxpoint));
	CudaSafeCall(cudaFreeHost(outputBufferPinned));
	CudaSafeCall(cudaFree(outputBuffer));
	CudaSafeCall(cudaFree(__2Gnx));
	CudaSafeCall(cudaFree(__2Gny));
	CudaSafeCall(cudaFree(_Gx));
	CudaSafeCall(cudaFree(_Gy));
}

// ----------------------------------------------------------------------------

int GPUEngine::GetNbThread()
{	return nbThread; }

// ----------------------------------------------------------------------------

bool GPUEngine::callKernelSEARCH_MODE_SA()
{
	// Reset nbFound
	CudaSafeCall(cudaMemset(outputBuffer, 0, 4));

	// printf("hiiu----nbThread/nbThreadPerGroup---:%d\n", nbThread / nbThreadPerGroup);
	// printf("hiiu----nbThreadPerGroup---:%d\n", nbThreadPerGroup);

	compute_keys_comp_mode_sa << < nbThread / nbThreadPerGroup, nbThreadPerGroup >> >
				(compMode, inputHashORxpoint, inputKey, maxFound, outputBuffer);

	return true;

}

bool GPUEngine::SetKeys(Point* p)
{
	// Sets the starting keys for each thread
	// p must contains nbThread public keys
	for (int i = 0; i < nbThread; i += nbThreadPerGroup) {
		for (int j = 0; j < nbThreadPerGroup; j++) {

			inputKeyPinned[8 * i + j + 0 * nbThreadPerGroup] = p[i + j].x.bits64[0];
			inputKeyPinned[8 * i + j + 1 * nbThreadPerGroup] = p[i + j].x.bits64[1];
			inputKeyPinned[8 * i + j + 2 * nbThreadPerGroup] = p[i + j].x.bits64[2];
			inputKeyPinned[8 * i + j + 3 * nbThreadPerGroup] = p[i + j].x.bits64[3];

			inputKeyPinned[8 * i + j + 4 * nbThreadPerGroup] = p[i + j].y.bits64[0];
			inputKeyPinned[8 * i + j + 5 * nbThreadPerGroup] = p[i + j].y.bits64[1];
			inputKeyPinned[8 * i + j + 6 * nbThreadPerGroup] = p[i + j].y.bits64[2];
			inputKeyPinned[8 * i + j + 7 * nbThreadPerGroup] = p[i + j].y.bits64[3];
		}
	}

	// Fill device memory
	CudaSafeCall(cudaMemcpy(inputKey, inputKeyPinned, nbThread * 32 * 2, cudaMemcpyHostToDevice));

	CudaSafeCall(cudaFreeHost(inputKeyPinned));
	inputKeyPinned = NULL;
	// printf("hiiu-----GPUEngine::setkey------\n");
	return callKernelSEARCH_MODE_SA();

}

// ----------------------------------------------------------------------------

bool GPUEngine::LaunchSEARCH_MODE_SA(std::vector<ITEM>& dataFound, bool spinWait)
{
	dataFound.clear();

	// Get the result
		cudaEvent_t evt;
		CudaSafeCall(cudaEventCreate(&evt));
		CudaSafeCall(cudaMemcpyAsync(outputBufferPinned, outputBuffer, 4, cudaMemcpyDeviceToHost, 0));
		CudaSafeCall(cudaEventRecord(evt, 0));
		while (cudaEventQuery(evt) == cudaErrorNotReady) {
			// Sleep 1 ms to free the CPU
			Timer::SleepMillis(1);
		}
		CudaSafeCall(cudaEventDestroy(evt));

	// Look for data found
	uint32_t nbFound = outputBufferPinned[0];

	// When can perform a standard copy, the kernel is eneded
	CudaSafeCall(cudaMemcpy(outputBufferPinned, outputBuffer, nbFound * ITEM_SIZE_A + 4, cudaMemcpyDeviceToHost));

	for (uint32_t i = 0; i < nbFound; i++) {
		uint32_t* itemPtr = outputBufferPinned + (i * ITEM_SIZE_A32 + 1);
		ITEM it;
		it.thId = itemPtr[0];
		int16_t* ptr = (int16_t*)&(itemPtr[1]);
		//it.endo = ptr[0] & 0x7FFF;
		it.mode = (ptr[0] & 0x8000) != 0;
		it.incr = ptr[1];
		it.hash = (uint8_t*)(itemPtr + 2);
		dataFound.push_back(it);
	}
	// printf("hiiu-----GPUEngine::LaunchSEARCH_MODE_SA------\n");
	return callKernelSEARCH_MODE_SA();
}


