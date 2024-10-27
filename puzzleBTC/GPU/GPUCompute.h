
#include <device_atomic_functions.h>
// #include <device_functions.h>
#include <cuda_runtime.h>
__device__ uint64_t* _2Gnx = NULL;
__device__ uint64_t* _2Gny = NULL;

__device__ uint64_t* Gx = NULL;
__device__ uint64_t* Gy = NULL;

// ---------------------------------------------------------------------------------------

__device__ __noinline__ bool MatchHash(uint32_t* _h, uint32_t* hash)
{
	if (_h[0] == hash[0] &&
		_h[1] == hash[1] &&
		_h[2] == hash[2] &&
		_h[3] == hash[3] &&
		_h[4] == hash[4]) {
		return true;
	}
	else {	return false;	}
}

// ---------------------------------------------------------------------------------------

__device__ __noinline__ void CheckPointSEARCH_MODE_SA(uint32_t* _h, int32_t incr, int32_t mode,
	uint32_t* hash160, uint32_t maxFound, uint32_t* out)
{
	uint32_t tid = (blockIdx.x * blockDim.x) + threadIdx.x;
	// printf("---tid 71 gpucompute.h--: %d \n", tid);

	if (MatchHash(_h, hash160)) {
		uint32_t pos = atomicAdd(out, 1);
		if (pos < maxFound) {
			out[pos * ITEM_SIZE_A32 + 1] = tid;
			out[pos * ITEM_SIZE_A32 + 2] = (uint32_t)(incr << 16) | (uint32_t)(mode << 15);// | (uint32_t)(endo);
			out[pos * ITEM_SIZE_A32 + 3] = _h[0];
			out[pos * ITEM_SIZE_A32 + 4] = _h[1];
			out[pos * ITEM_SIZE_A32 + 5] = _h[2];
			out[pos * ITEM_SIZE_A32 + 6] = _h[3];
			out[pos * ITEM_SIZE_A32 + 7] = _h[4];
		}
	}
}

// -----------------------------------------------------------------------------------------

#define CHECK_POINT_SEARCH_MODE_SA(_h,incr,mode)  CheckPointSEARCH_MODE_SA(_h,incr,mode,hash160,maxFound,out)

__device__ __noinline__ void CheckHashCompSEARCH_MODE_SA(uint64_t* px, uint8_t isOdd, int32_t incr,
	uint32_t* hash160, uint32_t maxFound, uint32_t* out)
{
	uint32_t h[5];
	_GetHash160Comp(px, isOdd, (uint8_t*)h);
	CHECK_POINT_SEARCH_MODE_SA(h, incr, true);
}
// -----------------------------------------------------------------------------------------

__device__ __noinline__ void CheckHashSEARCH_MODE_SA(uint32_t mode, uint64_t* px, uint64_t* py, int32_t incr,
	uint32_t* hash160, uint32_t maxFound, uint32_t* out)
{	
	CheckHashCompSEARCH_MODE_SA(px, (uint8_t)(py[0] & 1), incr, hash160, maxFound, out); 
}

// -----------------------------------------------------------------------------------------

#define CHECK_HASH_SEARCH_MODE_SA(incr) CheckHashSEARCH_MODE_SA(mode, px, py, incr, hash160, maxFound, out)

__device__ void ComputeKeysSEARCH_MODE_SA(uint32_t mode, uint64_t* startx, uint64_t* starty,
	uint32_t* hash160, uint32_t maxFound, uint32_t* out)
{
 
	uint64_t dx[GRP_SIZE / 2 + 1][4];
	uint64_t px[4];
	uint64_t py[4];
	uint64_t pyn[4];
	uint64_t sx[4];
	uint64_t sy[4];
	uint64_t dy[4];
	uint64_t _s[4];
	uint64_t _p2[4];

	// Load starting key
	__syncthreads();
	Load256A(sx, startx);
	Load256A(sy, starty);
	Load256(px, sx);
	Load256(py, sy);

	// Fill group with delta x
	uint32_t i;
	for (i = 0; i < HSIZE; i++)
		ModSub256(dx[i], Gx + 4 * i, sx);
	ModSub256(dx[i], Gx + 4 * i, sx);   // For the first point
	ModSub256(dx[i + 1], _2Gnx, sx); // For the next center point

	// Compute modular inverse
	_ModInvGrouped(dx);

	// We use the fact that P + i*G and P - i*G has the same deltax, so the same inverse
	// We compute key in the positive and negative way from the center of the group

	// Check starting point
	CHECK_HASH_SEARCH_MODE_SA(GRP_SIZE / 2);

	ModNeg256(pyn, py);

	for (i = 0; i < HSIZE; i++) {

		// P = StartPoint + i*G
		Load256(px, sx);
		Load256(py, sy);
		ModSub256(dy, Gy + 4 * i, py);

		_ModMult(_s, dy, dx[i]);             //  s = (p2.y-p1.y)*inverse(p2.x-p1.x)
		_ModSqr(_p2, _s);                    // _p2 = pow2(s)

		ModSub256(px, _p2, px);
		ModSub256(px, Gx + 4 * i);           // px = pow2(s) - p1.x - p2.x;

		ModSub256(py, Gx + 4 * i, px);
		_ModMult(py, _s);                    // py = - s*(ret.x-p2.x)
		ModSub256(py, Gy + 4 * i);           // py = - p2.y - s*(ret.x-p2.x);

		CHECK_HASH_SEARCH_MODE_SA(GRP_SIZE / 2 + (i + 1));

		// P = StartPoint - i*G, if (x,y) = i*G then (x,-y) = -i*G
		Load256(px, sx);
		ModSub256(dy, pyn, Gy + 4 * i);

		_ModMult(_s, dy, dx[i]);            //  s = (p2.y-p1.y)*inverse(p2.x-p1.x)
		_ModSqr(_p2, _s);                   // _p = pow2(s)

		ModSub256(px, _p2, px);
		ModSub256(px, Gx + 4 * i);          // px = pow2(s) - p1.x - p2.x;

		ModSub256(py, px, Gx + 4 * i);
		_ModMult(py, _s);                   // py = s*(ret.x-p2.x)
		ModSub256(py, Gy + 4 * i, py);      // py = - p2.y - s*(ret.x-p2.x);

		CHECK_HASH_SEARCH_MODE_SA(GRP_SIZE / 2 - (i + 1));

	}

	// First point (startP - (GRP_SZIE/2)*G)
	Load256(px, sx);
	Load256(py, sy);
	ModNeg256(dy, Gy + 4 * i);
	ModSub256(dy, py);

	_ModMult(_s, dy, dx[i]);              //  s = (p2.y-p1.y)*inverse(p2.x-p1.x)
	_ModSqr(_p2, _s);                     // _p = pow2(s)

	ModSub256(px, _p2, px);
	ModSub256(px, Gx + 4 * i);            // px = pow2(s) - p1.x - p2.x;

	ModSub256(py, px, Gx + 4 * i);
	_ModMult(py, _s);                     // py = s*(ret.x-p2.x)
	ModSub256(py, Gy + 4 * i, py);        // py = - p2.y - s*(ret.x-p2.x);

	CHECK_HASH_SEARCH_MODE_SA(0);

	i++;

	// Next start point (startP + GRP_SIZE*G)
	Load256(px, sx);
	Load256(py, sy);
	ModSub256(dy, _2Gny, py);

	_ModMult(_s, dy, dx[i]);             //  s = (p2.y-p1.y)*inverse(p2.x-p1.x)
	_ModSqr(_p2, _s);                    // _p2 = pow2(s)

	ModSub256(px, _p2, px);
	ModSub256(px, _2Gnx);                // px = pow2(s) - p1.x - p2.x;

	ModSub256(py, _2Gnx, px);
	_ModMult(py, _s);                    // py = - s*(ret.x-p2.x)
	ModSub256(py, _2Gny);                // py = - p2.y - s*(ret.x-p2.x);

	// Update starting point
	__syncthreads();
	Store256A(startx, px);
	Store256A(starty, py);

}



