#ifndef GPUENGINEH
#define GPUENGINEH

#include <vector>
#include "../SECP256k1.h"

// Number of key per thread (must be a multiple of GRP_SIZE) per kernel call
#define STEP_SIZE (2048 * 1)

// Number of thread per block
#define ITEM_SIZE_A 28
#define ITEM_SIZE_A32 (ITEM_SIZE_A/4)

typedef struct {
	uint32_t thId;
	int16_t  incr;
	uint8_t* hash;
} ITEM;

class GPUEngine
{

public:

	GPUEngine(Secp256K1* secp, int nbThreadGroup, int nbThreadPerGroup, int gpuId, 
		const uint32_t* hashORxpoint);

	~GPUEngine();

	bool SetKeys(Point* p);

	bool LaunchSEARCH_MODE_SA(std::vector<ITEM>& dataFound);

	int GetNbThread();
	int GetGroupSize();

	std::string deviceName;

	static void PrintCudaInfo();

private:
	void InitGenratorTable(Secp256K1* secp);

	bool callKernelSEARCH_MODE_SA();

	int nbThread;
	int nbThreadPerGroup;

	uint32_t* inputHashORxpoint;
	uint32_t* inputHashORxpointPinned;

	uint64_t* inputKey;
	uint64_t* inputKeyPinned;

	uint32_t* outputBuffer;
	uint32_t* outputBufferPinned;

	uint64_t* __2Gnx;
	uint64_t* __2Gny;

	uint64_t* _Gx;
	uint64_t* _Gy;

	bool initialised;

	uint32_t outputSize;

};

#endif // GPUENGINEH
