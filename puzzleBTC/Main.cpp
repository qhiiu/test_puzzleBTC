#include "Timer.h"
#include "KeyHunt.h"
#include "Base58.h"
#include <string>
#include <cassert>
#include <signal.h>
#include <unistd.h>
#include <iostream>
#include <cstdint>
#include <fstream>
#include <map>

using namespace std;

#define RANDOM 0
#define INPUT 1

//-----------------------------------------------------------------------
void CtrlHandler(int signum) {
	printf("\nBYE");
	printf("\nBYE\n\n");
	exit(signum);
}
//-----------------------------------------------------------------------
void check_file_exist(){
	FILE* file;
    file = fopen("$.txt", "r");
    if (file!=NULL)  {   
        printf("\n $.txt exists ======$$$$====== \n");
    	printf("\n.\n.\n.\n.\n.\n --- DONE !! check and take money !! ---- \n.\n.\n.\n.\n.\n.\n");

        exit(-1);   
    }
}
//-----------------------------------------------------------------------
uint64_t check_data(uint64_t P, std::string priv)
{
    std::string fileName;
    fileName = "x" + std::to_string(P) + ".txt";

    ifstream file(fileName);
    string line;
	uint64_t n = 0;

    if (file.is_open()) {
        while (getline(file, line)) {
            n += 1;
            if (priv == line){
              std::cout << std::endl <<"-------- Had in Database !!! exit() -------"<< std::endl << std::endl;
              exit(0);
            }
        }

        file.close();
    } else {   cout << "Err file !!!" << endl;   }
	return n;
}
//-----------------------------------------------------------------------
void init_value(int mode, uint64_t P, uint64_t xN, std::string& address,Int& priv_dec, Int& rangeStart, Int& rangeEnd)
{
	std::cout<< "===================================================\n";   

    map<int, char*> list_range_dec;
        list_range_dec[67] = "7378697629";
        list_range_dec[68] = "14757395258";
        list_range_dec[69] = "29514790517";
        list_range_dec[70] = "59029581035";
        list_range_dec[71] = "118059162071";
        list_range_dec[72] = "236118324143";
        list_range_dec[73] = "472236648286";
        list_range_dec[74] = "944473296573";
        list_range_dec[75] = "1888946593147";
        list_range_dec[76] = "3777893186295";
        list_range_dec[77] = "7555786372591";
        list_range_dec[78] = "15111572745182";
        list_range_dec[79] = "30223145490365";
        list_range_dec[80] = "60446290980731";
        list_range_dec[81] = "120892581961462";
        list_range_dec[82] = "241785163922925";
        list_range_dec[83] = "483570327845851";
        list_range_dec[84] = "967140655691703";
        list_range_dec[85] = "1934281311383406";
        list_range_dec[86] = "3868562622766813";
        list_range_dec[87] = "7737125245533626";
        list_range_dec[88] = "15474250491067253";
        list_range_dec[89] = "30948500982134506";
        list_range_dec[90] = "61897001964269013";
        list_range_dec[91] = "123794003928538027";
        list_range_dec[92] = "247588007857076054";
        list_range_dec[93] = "495176015714152109";
        list_range_dec[94] = "990352031428304219";
        list_range_dec[95] = "1980704062856608439";
        list_range_dec[96] = "3961408125713216879";
        list_range_dec[97] = "7922816251426433759";
        list_range_dec[98] = "15845632502852867518";
        list_range_dec[99] = "31691265005705735037";
        list_range_dec[100] = "63382530011411470074";
        list_range_dec[101] = "126765060022822940149";
        list_range_dec[102] = "253530120045645880299";
        list_range_dec[103] = "507060240091291760598";
        list_range_dec[104] = "1014120480182583521197";
        list_range_dec[105] = "2028240960365167042394";
        list_range_dec[106] = "4056481920730334084789";
        list_range_dec[107] = "8112963841460668169578";
        list_range_dec[108] = "16225927682921336339157";
        list_range_dec[109] = "32451855365842672678315";
        list_range_dec[110] = "64903710731685345356631";
        list_range_dec[111] = "129807421463370690713262";
        list_range_dec[112] = "259614842926741381426524";
        list_range_dec[113] = "519229685853482762853049";
        list_range_dec[114] = "1038459371706965525706099";
        list_range_dec[115] = "2076918743413931051412198";
        list_range_dec[116] = "4153837486827862102824397";
        list_range_dec[117] = "8307674973655724205648794";
        list_range_dec[118] = "16615349947311448411297588";
        list_range_dec[119] = "33230699894622896822595176";
        list_range_dec[120] = "66461399789245793645190353";
        list_range_dec[121] = "132922799578491587290380706";
        list_range_dec[122] = "265845599156983174580761412";
        list_range_dec[123] = "531691198313966349161522824";
        list_range_dec[124] = "1063382396627932698323045648";
        list_range_dec[125] = "2126764793255865396646091296";
        list_range_dec[126] = "4253529586511730793292182592";
        list_range_dec[127] = "8507059173023461586584365185";
        list_range_dec[128] = "17014118346046923173168730371";
        list_range_dec[129] = "34028236692093846346337460743";
        list_range_dec[130] = "68056473384187692692674921486";
        list_range_dec[131] = "136112946768375385385349842972";
        list_range_dec[132] = "272225893536750770770699685945";
        list_range_dec[133] = "544451787073501541541399371890";
        list_range_dec[134] = "1088903574147003083082798743781";
        list_range_dec[135] = "2177807148294006166165597487563";
        list_range_dec[136] = "4355614296588012332331194975126";
        list_range_dec[137] = "8711228593176024664662389950253";
        list_range_dec[138] = "17422457186352049329324779900506";
        list_range_dec[139] = "34844914372704098658649559801013";
        list_range_dec[140] = "69689828745408197317299119602026";
        list_range_dec[141] = "139379657490816394634598239204052";
        list_range_dec[142] = "278759314981632789269196478408104";
        list_range_dec[143] = "557518629963265578538392956816209";
        list_range_dec[144] = "1115037259926531157076785913632418";
        list_range_dec[145] = "2230074519853062314153571827264836";
        list_range_dec[146] = "4460149039706124628307143654529672";
        list_range_dec[147] = "8920298079412249256614287309059344";
        list_range_dec[148] = "17840596158824498513228574618118689";
        list_range_dec[149] = "35681192317648997026457149236237378";
        list_range_dec[150] = "71362384635297994052914298472474756";
        list_range_dec[151] = "142724769270595988105828596944949513";
        list_range_dec[152] = "285449538541191976211657193889899027";
        list_range_dec[153] = "570899077082383952423314387779798054";
        list_range_dec[154] = "1141798154164767904846628775559596109";
        list_range_dec[155] = "2283596308329535809693257551119192218";
        list_range_dec[156] = "4567192616659071619386515102238384436";
        list_range_dec[157] = "9134385233318143238773030204476768872";
        list_range_dec[158] = "18268770466636286477546060408953537745";
        list_range_dec[159] = "36537540933272572955092120817907075491";
        list_range_dec[160] = "73075081866545145910184241635814150982";

    map<int, std::string> list_addr;
        list_addr[67] = "1BY8GQbnueYofwSuFAT3USAhGjPrkxDdW9";
        list_addr[68] = "1MVDYgVaSN6iKKEsbzRUAYFrYJadLYZvvZ";
        list_addr[69] = "19vkiEajfhuZ8bs8Zu2jgmC6oqZbWqhxhG";
        list_addr[70] = "";
        list_addr[71] = "1PWo3JeB9jrGwfHDNpdGK54CRas7fsVzXU";
        list_addr[72] = "1JTK7s9YVYywfm5XUH7RNhHJH1LshCaRFR";
        list_addr[73] = "12VVRNPi4SJqUTsp6FmqDqY5sGosDtysn4";
        list_addr[74] = "1FWGcVDK3JGzCC3WtkYetULPszMaK2Jksv";
        list_addr[75] = "";
        list_addr[76] = "1DJh2eHFYQfACPmrvpyWc8MSTYKh7w9eRF";
        list_addr[77] = "1Bxk4CQdqL9p22JEtDfdXMsng1XacifUtE";
        list_addr[78] = "15qF6X51huDjqTmF9BJgxXdt1xcj46Jmhb";
        list_addr[79] = "1ARk8HWJMn8js8tQmGUJeQHjSE7KRkn2t8";
        list_addr[80] = "";
        list_addr[81] = "15qsCm78whspNQFydGJQk5rexzxTQopnHZ";
        list_addr[82] = "13zYrYhhJxp6Ui1VV7pqa5WDhNWM45ARAC";
        list_addr[83] = "14MdEb4eFcT3MVG5sPFG4jGLuHJSnt1Dk2";
        list_addr[84] = "1CMq3SvFcVEcpLMuuH8PUcNiqsK1oicG2D";
        list_addr[85] = "";
        list_addr[86] = "1K3x5L6G57Y494fDqBfrojD28UJv4s5JcK";
        list_addr[87] = "1PxH3K1Shdjb7gSEoTX7UPDZ6SH4qGPrvq";
        list_addr[88] = "16AbnZjZZipwHMkYKBSfswGWKDmXHjEpSf";
        list_addr[89] = "19QciEHbGVNY4hrhfKXmcBBCrJSBZ6TaVt";
        list_addr[90] = "";
        list_addr[91] = "1EzVHtmbN4fs4MiNk3ppEnKKhsmXYJ4s74";
        list_addr[92] = "1AE8NzzgKE7Yhz7BWtAcAAxiFMbPo82NB5";
        list_addr[93] = "17Q7tuG2JwFFU9rXVj3uZqRtioH3mx2Jad";
        list_addr[94] = "1K6xGMUbs6ZTXBnhw1pippqwK6wjBWtNpL";
        list_addr[95] = "";
        list_addr[96] = "15ANYzzCp5BFHcCnVFzXqyibpzgPLWaD8b";
        list_addr[97] = "18ywPwj39nGjqBrQJSzZVq2izR12MDpDr8";
        list_addr[98] = "1CaBVPrwUxbQYYswu32w7Mj4HR4maNoJSX";
        list_addr[99] = "1JWnE6p6UN7ZJBN7TtcbNDoRcjFtuDWoNL";
        list_addr[100] = "";
        list_addr[101] = "1CKCVdbDJasYmhswB6HKZHEAnNaDpK7W4n";
        list_addr[102] = "1PXv28YxmYMaB8zxrKeZBW8dt2HK7RkRPX";
        list_addr[103] = "1AcAmB6jmtU6AiEcXkmiNE9TNVPsj9DULf";
        list_addr[104] = "1EQJvpsmhazYCcKX5Au6AZmZKRnzarMVZu";
        list_addr[105] = "";
        list_addr[106] = "18KsfuHuzQaBTNLASyj15hy4LuqPUo1FNB";
        list_addr[107] = "15EJFC5ZTs9nhsdvSUeBXjLAuYq3SWaxTc";
        list_addr[108] = "1HB1iKUqeffnVsvQsbpC6dNi1XKbyNuqao";
        list_addr[109] = "1GvgAXVCbA8FBjXfWiAms4ytFeJcKsoyhL";
        list_addr[110] = "";
        list_addr[111] = "1824ZJQ7nKJ9QFTRBqn7z7dHV5EGpzUpH3";
        list_addr[112] = "18A7NA9FTsnJxWgkoFfPAFbQzuQxpRtCos";
        list_addr[113] = "1NeGn21dUDDeqFQ63xb2SpgUuXuBLA4WT4";
        list_addr[114] = "174SNxfqpdMGYy5YQcfLbSTK3MRNZEePoy";
        list_addr[115] = "";
        list_addr[116] = "1MnJ6hdhvK37VLmqcdEwqC3iFxyWH2PHUV";
        list_addr[117] = "1KNRfGWw7Q9Rmwsc6NT5zsdvEb9M2Wkj5Z";
        list_addr[118] = "1PJZPzvGX19a7twf5HyD2VvNiPdHLzm9F6";
        list_addr[119] = "1GuBBhf61rnvRe4K8zu8vdQB3kHzwFqSy7";
        list_addr[120] = "";
        list_addr[121] = "1GDSuiThEV64c166LUFC9uDcVdGjqkxKyh";
        list_addr[122] = "1Me3ASYt5JCTAK2XaC32RMeH34PdprrfDx";
        list_addr[123] = "1CdufMQL892A69KXgv6UNBD17ywWqYpKut";
        list_addr[124] = "1BkkGsX9ZM6iwL3zbqs7HWBV7SvosR6m8N";
        list_addr[125] = "";
        list_addr[126] = "1AWCLZAjKbV1P7AHvaPNCKiB7ZWVDMxFiz";
        list_addr[127] = "1G6EFyBRU86sThN3SSt3GrHu1sA7w7nzi4";
        list_addr[128] = "1MZ2L1gFrCtkkn6DnTT2e4PFUTHw9gNwaj";
        list_addr[129] = "1Hz3uv3nNZzBVMXLGadCucgjiCs5W9vaGz";
        list_addr[130] = "1Fo65aKq8s8iquMt6weF1rku1moWVEd5Ua";
        list_addr[131] = "16zRPnT8znwq42q7XeMkZUhb1bKqgRogyy";
        list_addr[132] = "1KrU4dHE5WrW8rhWDsTRjR21r8t3dsrS3R";
        list_addr[133] = "17uDfp5r4n441xkgLFmhNoSW1KWp6xVLD";
        list_addr[134] = "13A3JrvXmvg5w9XGvyyR4JEJqiLz8ZySY3";
        list_addr[135] = "16RGFo6hjq9ym6Pj7N5H7L1NR1rVPJyw2v";
        list_addr[136] = "1UDHPdovvR985NrWSkdWQDEQ1xuRiTALq";
        list_addr[137] = "15nf31J46iLuK1ZkTnqHo7WgN5cARFK3RA";
        list_addr[138] = "1Ab4vzG6wEQBDNQM1B2bvUz4fqXXdFk2WT";
        list_addr[139] = "1Fz63c775VV9fNyj25d9Xfw3YHE6sKCxbt";
        list_addr[140] = "1QKBaU6WAeycb3DbKbLBkX7vJiaS8r42Xo";
        list_addr[141] = "1CD91Vm97mLQvXhrnoMChhJx4TP9MaQkJo";
        list_addr[142] = "15MnK2jXPqTMURX4xC3h4mAZxyCcaWWEDD";
        list_addr[143] = "13N66gCzWWHEZBxhVxG18P8wyjEWF9Yoi1";
        list_addr[144] = "1NevxKDYuDcCh1ZMMi6ftmWwGrZKC6j7Ux";
        list_addr[145] = "19GpszRNUej5yYqxXoLnbZWKew3KdVLkXg";
        list_addr[146] = "1M7ipcdYHey2Y5RZM34MBbpugghmjaV89P";
        list_addr[147] = "18aNhurEAJsw6BAgtANpexk5ob1aGTwSeL";
        list_addr[148] = "1FwZXt6EpRT7Fkndzv6K4b4DFoT4trbMrV";
        list_addr[149] = "1CXvTzR6qv8wJ7eprzUKeWxyGcHwDYP1i2";
        list_addr[150] = "1MUJSJYtGPVGkBCTqGspnxyHahpt5Te8jy";
        list_addr[151] = "13Q84TNNvgcL3HJiqQPvyBb9m4hxjS3jkV";
        list_addr[152] = "1LuUHyrQr8PKSvbcY1v1PiuGuqFjWpDumN";
        list_addr[153] = "18192XpzzdDi2K11QVHR7td2HcPS6Qs5vg";
        list_addr[154] = "1NgVmsCCJaKLzGyKLFJfVequnFW9ZvnMLN";
        list_addr[155] = "1AoeP37TmHdFh8uN72fu9AqgtLrUwcv2wJ";
        list_addr[156] = "1FTpAbQa4h8trvhQXjXnmNhqdiGBd1oraE";
        list_addr[157] = "14JHoRAdmJg3XR4RjMDh6Wed6ft6hzbQe9";
        list_addr[158] = "19z6waranEf8CcP8FqNgdwUe1QRxvUNKBG";
        list_addr[159] = "14u4nA5sugaswb6SZgn5av2vuChdMnD9E5";
        list_addr[160] = "1NBC8uXJy1GiJ6drkiZa1WuKn51ps7EPTv";

    int solved_P[14] = {66, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120, 125, 130};

    //check P
    if (P < 67 || 160 < P) {
        printf("\n\n\n\n----- !! P = %lu invalid !! ----- try other P \n\n\n\n", P);
        exit(-1);
    }
    
    for (int i = 0; i < (sizeof(solved_P) / sizeof(solved_P[0])); ++i) {
        if (P == solved_P[i]) {
            printf("\n\n\n\n----- !! P = %lu solved !! ----- try other P \n\n\n\n", P);
            exit(-1);
        }
    }

    address = list_addr[P]; 

    // generate Priv_dec + addr + range
	Int rStart_priv_dec, rEnd_priv_dec;
    rStart_priv_dec.SetBase10(list_range_dec[P]);
    rEnd_priv_dec.SetBase10(list_range_dec[P+1]);

    switch (mode){
        case RANDOM:
            while (true)
            {
                priv_dec.Rand(&rStart_priv_dec);
                priv_dec.Add(&rStart_priv_dec);

                //--- add d_x int priv_dec
                Int d_x;
                d_x.SetBase10("9999999");
                d_x.Rand(&d_x);
                priv_dec.Add(&d_x);

                if (priv_dec.IsGreaterOrEqual(&rStart_priv_dec) && 
                    priv_dec.IsLowerOrEqual(&rEnd_priv_dec)){ 
                        break; 
                }
            }
            break;

        case INPUT:
            std::cout << "\nRANGE__INPUT : " << rStart_priv_dec.GetBase10() << " - " << rEnd_priv_dec.GetBase10();
            char* input_priv_dec = new char[100];

            while (true)
            {
                std::cout << "\ninput__priv_dec : "; 
                cin.getline(input_priv_dec, 100);

                priv_dec.SetBase10(input_priv_dec);     

                if (priv_dec.IsGreaterOrEqual(&rStart_priv_dec) && 
                    priv_dec.IsLowerOrEqual(&rEnd_priv_dec)){ 
                        break; 
                }
                break;
            }
    }
    
    Int _10B, _xNB;
    _10B.SetBase10("10000000000"); 
    _xNB = _10B;
    _xNB.Mult(xN);

    //rangeStart
    rangeStart = priv_dec; // 10 billions
    rangeStart.Mult(&_10B);
    //rangEnd
    rangeEnd = rangeStart;
    rangeEnd.Add(&_xNB);

            // // --------------------- test -----------------------------
            // address = "13zb1hQbWVsc2S7ZTZnP2G4undNNpdh5so";
            // rangeStart.SetBase16("2832ed74f00000000");
            // rangeEnd.SetBase16("2832ed74f90000000");
            // // --------------------- test=end -------------------------

    std::cout << "\nPUZZLE      : " << P;
    std::cout << "\nADDRESS     : " << address;
    std::cout << "\nRANGE START : " << list_range_dec[P];
    std::cout << "\nRANGE END   : " << list_range_dec[P+1] << "\n";

    //print priv_dec info 
    uint64_t nChecked = 0;
    Int priv_dec_copy = priv_dec;
    for (int i = 0; i < xN; i++){
        std::cout << "\nPriv_dec ======> " << priv_dec_copy.GetBase10(); //print 
        nChecked = check_data(P, priv_dec_copy.GetBase10()); // check priv
        priv_dec_copy.AddOne(); // increase priv 
    } 
    std::cout << "\n\nnChecked : " << nChecked ;
}
//-----------------------------------------------------------------------
void run(int mode, uint64_t P, uint64_t xN){
    
    check_file_exist(); // check file $.txt

	// Global Init
	Timer::Init();
	rseed(Timer::getSeed32());

	// bool gpuAutoGrid = true;
	vector<int> gpuId = { 0 };
	vector<int> gridSize;
	vector<unsigned char> hashORxpoint;
	hashORxpoint.clear();

    std::string address = "";
	Int priv_dec, rangeStart, rangeEnd;

    //set value
    init_value(mode, P, xN, address, priv_dec, rangeStart, rangeEnd);

	std::string outputFile = "$.txt";
    std::cout << "\n\nOUTPUT FILE  : " << outputFile;


	if (DecodeBase58(address, hashORxpoint)) {
        hashORxpoint.erase(hashORxpoint.begin() + 0);
        hashORxpoint.erase(hashORxpoint.begin() + 20, hashORxpoint.begin() + 24);
        assert(hashORxpoint.size() == 20);
	}

	if (gridSize.size() == 0) {
		for (int i = 0; i < gpuId.size(); i++) {
			gridSize.push_back(-1);
			gridSize.push_back(128);
		}
	}

	signal(SIGINT, CtrlHandler);

	KeyHunt* v;
    bool should_exit = false;
	v = new KeyHunt(hashORxpoint, outputFile, rangeStart, rangeEnd, priv_dec, xN, P, should_exit);
	v->Search(gpuId, gridSize, should_exit);

	delete v;
};


int main(){
    
    int mode = RANDOM;
    // int mode = INPUT;

	uint64_t P = 67;
	uint64_t xN = 1;
	int sleepTime = 5;

    // ----- input P-xN-sleepTime -------
    // std::cout <<"nhập P = "; std::cin >> P ; std::cout << std::endl;
    // std::cout <<"nhập xN = "; std::cin >> xN ; std::cout << std::endl;
    // std::cout << "sleepTime xT : "; std::cin >> sleepTime; std::cout<< endl;

	for (int i = 0; i < 9999; i++)	{
		std::cout << "\n-- sleep : "<< sleepTime << " s" << std::endl; 
		run(mode, P, xN);
		
        // coutdown sleeptime
        for (int j = sleepTime; j >= 0; j--)        {
            sleep(1);   
            printf("----->  %d s  <-----",j);
            fflush(stdout);
            printf("\r");
        }
        printf("\n");
	}
	return 0;
};
