#ifndef KEYHUNTH
#define KEYHUNTH

#include <string>
#include <vector>
#include "SECP256k1.h"
#include "GPU/GPUEngine.h"
#ifdef WIN64
#include <Windows.h>
#endif

#define CPU_GRP_SIZE (1024*2)

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
	KeyHunt(const std::vector<unsigned char>& hashORxpoint, int compMode, int searchMode, int coinType, 
		bool useGpu, const std::string& outputFile, uint32_t maxFound, 
		const std::string& rangeStart, const std::string& rangeEnd, bool& should_exit, std::string priv_dec, long xN, long P);

	~KeyHunt();

	void Search(std::vector<int> gpuId, std::vector<int> gridSize, bool& should_exit);
	void FindKeyGPU(TH_PARAM* p);

private:

	void InitGenratorTable();

	// std::string GetHex(std::vector<unsigned char>& buffer);
	bool checkPrivKey(std::string addr, Int& key, int32_t incr, bool mode);

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

	int compMode;
	int searchMode;
	int coinType;

	bool useGpu;
	bool endOfSearch;
	int nbGPUThread;
	int nbFoundKey;
	uint64_t targetCounter;

	std::string outputFile;
	std::string inputFile;
	uint32_t hash160Keccak[5];
	uint32_t xpoint[8];
	bool useSSE;

	Int rangeStart;
	Int rangeEnd;
	Int rangeDiff;
	Int rangeDiff2;

	std::string priv_dec;
	long xN;
	long P;

	uint32_t maxFound;



	pthread_mutex_t  ghMutex;
};

#endif // KEYHUNTH
