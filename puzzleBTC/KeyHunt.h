#ifndef KEYHUNTH
#define KEYHUNTH

#include <string>
#include <vector>
#include "SECP256k1.h"
#include "GPU/GPUEngine.h"
#ifdef WIN64
#include <Windows.h>
#endif

#define CPU_GRP_SIZE (2048 * 1)

class KeyHunt;

typedef struct {
	KeyHunt* obj;
	int  threadId;
	bool isRunning;
	bool hasStarted;

	int  gridSizeX;
	int  gridSizeY;
	int  gpuId;

	Int rangeStart;
	Int rangeEnd;
} TH_PARAM;


class KeyHunt
{

public:
	KeyHunt(const std::vector<unsigned char>& hashORxpoint, const std::string& outputFile, 
		const Int rangeStart, const Int rangeEnd, const Int priv_dec, uint64_t xN, uint64_t P , bool& should_exit);

	~KeyHunt();

	void Search(std::vector<int> gpuId, std::vector<int> gridSize, bool& should_exit);
	void FindKeyGPU(TH_PARAM* p);

private:

	void InitGenratorTable();

	bool checkPrivKey(std::string addr, Int& key, int32_t incr);

	void output(std::string addr, std::string pAddr, std::string pAddrHex, std::string pubKey);
	bool isAlive(TH_PARAM* p);

	bool hasStarted(TH_PARAM* p);
	uint64_t getGPUCount();

	void SetupRanges(uint32_t totalThreads);

	void getGPUStartingKeys(Int& tRangeStart, Int& tRangeEnd, int groupSize, int nbThread, Int* keys, Point* p);

	std::string formatThousands(uint64_t x);
	char* toTimeStr(int sec, char* timeStr);

	Secp256K1* secp;

	uint64_t counters[256];
	double startTime;

	bool endOfSearch;
	int nbGPUThread;
	int nbFoundKey;

	std::string outputFile;
	uint32_t hash160Keccak[5];

	Int priv_dec;
	uint64_t xN;
	uint64_t P;
	
	Int rangeStart;
	Int rangeEnd;
	Int rangeDiff;
	Int rangeDiff2;

};

#endif // KEYHUNTH
