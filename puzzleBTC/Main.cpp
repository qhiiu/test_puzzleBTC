#include "Timer.h"
#include "KeyHunt.h"
#include "Base58.h"
#include "CmdParse.h"
// #include <fstream>
#include <string>
#include <string.h>
#include <stdexcept>
#include <cassert>
#include <algorithm>
#include <signal.h>
#include <unistd.h>
#include <iostream>
#include <cstdint>

#include <sstream>


using namespace std;

bool should_exit = false;

// ----------------------------------------------------------------------------

bool parseRange(const std::string& s, Int& start, Int& end)
{
	size_t pos = s.find(':');

	if (pos == std::string::npos) {
		start.SetBase16(s.c_str());
		end.Set(&start);
		end.Add(0xFFFFFFFFFFFFULL);
	}
	else {
		std::string left = s.substr(0, pos);

		if (left.length() == 0) {
			start.SetInt32(1);
		}
		else {
			start.SetBase16(left.c_str());
		}

		std::string right = s.substr(pos + 1);

		if (right[0] == '+') {
			Int t;
			t.SetBase16(right.substr(1).c_str());
			end.Set(&start);
			end.Add(&t);
		}
		else {
			end.SetBase16(right.c_str());
		}
	}

	return true;
}

void CtrlHandler(int signum) {
	printf("\nBYE");
	printf("\nBYE");
	printf("\nBYE");
	printf("\nBYE");
	exit(signum);
}

// ============================================== hiiu code =============================================
#include <fstream>
void check_file_exist(){
	FILE* file;
    file = fopen("$.txt", "r");
    if (file!=NULL)  {   std::cout << "$.txt exists ======$$$$======" << std::endl; exit(-1);   }
}

long long hiiu_check_priv_database(string a){
    ifstream file("x67.txt");
    string line;
	long long n = 0;

    if (file.is_open()) {
        while (getline(file, line)) {
            n += 1;
            if (a == line){
              std::cout << std::endl <<"-------- Had in Database !!! exit() -------"<< std::endl << std::endl;
              exit(0);
            }
        }

        file.close();
	// std::cout << endl << "total check  : " << n ;
    }   else {   cout << "Err file !!!" << endl;   }
	return n;
}


#include <Python.h>
std::string hiiu_random_priv_dec(long P, long xN){
    // Khởi tạo Python
    Py_Initialize();

    // Định nghĩa mã Python
    const char* pythonCode = R"(
# ========= Check file $.txt ======================== 

import random
import os.path



# === check_data ============================================================= 
flag_print_addr_checked = True

def check_data(path__data, priv_dec,h_s,h_e):
    nCheck = 0
    with open(path__data) as file:
        for line in file:
            nCheck += 1
            line = line.strip()
            if str(priv_dec) == line : 
                print(str(priv_dec), '- HAD IN DATABASE !!!')
                exit('TRY AGAIN : ------- !!! HAD IN DATABASE !!! -------\n\n')
    file.close()

    global flag_print_addr_checked
    if flag_print_addr_checked == True :
        addr__checked = nCheck
        print('\rchecked     :',f'{addr__checked:,}')

        remain_addr = (h_e - h_s) - nCheck
        print('remain addr :', f'{remain_addr:,}')
        print()
        
        flag_print_addr_checked = False



# ====== run main ==========================================================
# def run(P, xN, rangee, address):
def run_python(P, xN):

# def run_python():
    FILE_PATH = '$.txt'
    CHECK = os.path.isfile(FILE_PATH) 
    if CHECK == True :
        print('\n==== $$$$$ =====\n')
        exit()

    # DATA ============================================================
    list_addr = { # puzzle address list
        66:'13zb1hQbWVsc2S7ZTZnP2G4undNNpdh5so-------2832ed74f2b5e35ee'
        ,67:'1BY8GQbnueYofwSuFAT3USAhGjPrkxDdW9'
        ,68:'1MVDYgVaSN6iKKEsbzRUAYFrYJadLYZvvZ'
        ,69:'19vkiEajfhuZ8bs8Zu2jgmC6oqZbWqhxhG'
        ,70:'19YZECXj3SxEZMoUeJ1yiPsw8xANe7M7QR'
        ,71:'1PWo3JeB9jrGwfHDNpdGK54CRas7fsVzXU'
        ,72:'1JTK7s9YVYywfm5XUH7RNhHJH1LshCaRFR'
        ,73:'12VVRNPi4SJqUTsp6FmqDqY5sGosDtysn4'
        ,74:'1FWGcVDK3JGzCC3WtkYetULPszMaK2Jksv'
        ,75:'1J36UjUByGroXcCvmj13U6uwaVv9caEeAt'
        ,76:'1DJh2eHFYQfACPmrvpyWc8MSTYKh7w9eRF'
        ,77:'1Bxk4CQdqL9p22JEtDfdXMsng1XacifUtE'
        ,78:'15qF6X51huDjqTmF9BJgxXdt1xcj46Jmhb'
        ,79:'1ARk8HWJMn8js8tQmGUJeQHjSE7KRkn2t8'
        ,80:'1BCf6rHUW6m3iH2ptsvnjgLruAiPQQepLe'
        ,81:'15qsCm78whspNQFydGJQk5rexzxTQopnHZ'
        ,82:'13zYrYhhJxp6Ui1VV7pqa5WDhNWM45ARAC'
        ,83:'14MdEb4eFcT3MVG5sPFG4jGLuHJSnt1Dk2'
        ,84:'1CMq3SvFcVEcpLMuuH8PUcNiqsK1oicG2D'
        ,85:'1Kh22PvXERd2xpTQk3ur6pPEqFeckCJfAr'
        ,86:'1K3x5L6G57Y494fDqBfrojD28UJv4s5JcK'
        ,87:'1PxH3K1Shdjb7gSEoTX7UPDZ6SH4qGPrvq'
        ,88:'16AbnZjZZipwHMkYKBSfswGWKDmXHjEpSf'
        ,89:'19QciEHbGVNY4hrhfKXmcBBCrJSBZ6TaVt'
        ,90:'1L12FHH2FHjvTviyanuiFVfmzCy46RRATU'
        ,91:'1EzVHtmbN4fs4MiNk3ppEnKKhsmXYJ4s74'
        ,92:'1AE8NzzgKE7Yhz7BWtAcAAxiFMbPo82NB5'
        ,93:'17Q7tuG2JwFFU9rXVj3uZqRtioH3mx2Jad'
        ,94:'1K6xGMUbs6ZTXBnhw1pippqwK6wjBWtNpL'
        ,95:'19eVSDuizydXxhohGh8Ki9WY9KsHdSwoQC'
        ,96:'15ANYzzCp5BFHcCnVFzXqyibpzgPLWaD8b'
        ,97:'18ywPwj39nGjqBrQJSzZVq2izR12MDpDr8'
        ,98:'1CaBVPrwUxbQYYswu32w7Mj4HR4maNoJSX'
        ,99:'1JWnE6p6UN7ZJBN7TtcbNDoRcjFtuDWoNL'
        ,100:'1KCgMv8fo2TPBpddVi9jqmMmcne9uSNJ5F'
        ,101:'1CKCVdbDJasYmhswB6HKZHEAnNaDpK7W4n'
        ,102:'1PXv28YxmYMaB8zxrKeZBW8dt2HK7RkRPX'
        ,103:'1AcAmB6jmtU6AiEcXkmiNE9TNVPsj9DULf'
        ,104:'1EQJvpsmhazYCcKX5Au6AZmZKRnzarMVZu'
        ,105:'1CMjscKB3QW7SDyQ4c3C3DEUHiHRhiZVib'
        ,106:'18KsfuHuzQaBTNLASyj15hy4LuqPUo1FNB'
        ,107:'15EJFC5ZTs9nhsdvSUeBXjLAuYq3SWaxTc'
        ,108:'1HB1iKUqeffnVsvQsbpC6dNi1XKbyNuqao'
        ,109:'1GvgAXVCbA8FBjXfWiAms4ytFeJcKsoyhL'
        ,110:'12JzYkkN76xkwvcPT6AWKZtGX6w2LAgsJg'
        ,111:'1824ZJQ7nKJ9QFTRBqn7z7dHV5EGpzUpH3'
        ,112:'18A7NA9FTsnJxWgkoFfPAFbQzuQxpRtCos'
        ,113:'1NeGn21dUDDeqFQ63xb2SpgUuXuBLA4WT4'
        ,114:'174SNxfqpdMGYy5YQcfLbSTK3MRNZEePoy'
        ,115:'1NLbHuJebVwUZ1XqDjsAyfTRUPwDQbemfv'
        ,116:'1MnJ6hdhvK37VLmqcdEwqC3iFxyWH2PHUV'
        ,117:'1KNRfGWw7Q9Rmwsc6NT5zsdvEb9M2Wkj5Z'
        ,118:'1PJZPzvGX19a7twf5HyD2VvNiPdHLzm9F6'
        ,119:'1GuBBhf61rnvRe4K8zu8vdQB3kHzwFqSy7'
        ,120:'17s2b9ksz5y7abUm92cHwG8jEPCzK3dLnT'
        ,121:'1GDSuiThEV64c166LUFC9uDcVdGjqkxKyh'
        ,122:'1Me3ASYt5JCTAK2XaC32RMeH34PdprrfDx'
        ,123:'1CdufMQL892A69KXgv6UNBD17ywWqYpKut'
        ,124:'1BkkGsX9ZM6iwL3zbqs7HWBV7SvosR6m8N'
        ,125:'1PXAyUB8ZoH3WD8n5zoAthYjN15yN5CVq5'
        ,126:'1AWCLZAjKbV1P7AHvaPNCKiB7ZWVDMxFiz'
        ,127:'1G6EFyBRU86sThN3SSt3GrHu1sA7w7nzi4'
        ,128:'1MZ2L1gFrCtkkn6DnTT2e4PFUTHw9gNwaj'
        ,129:'1Hz3uv3nNZzBVMXLGadCucgjiCs5W9vaGz'
        ,130:'1Fo65aKq8s8iquMt6weF1rku1moWVEd5Ua'
        ,131:'16zRPnT8znwq42q7XeMkZUhb1bKqgRogyy'
        ,132:'1KrU4dHE5WrW8rhWDsTRjR21r8t3dsrS3R'
        ,133:'17uDfp5r4n441xkgLFmhNoSW1KWp6xVLD'
        ,134:'13A3JrvXmvg5w9XGvyyR4JEJqiLz8ZySY3'
        ,135:'16RGFo6hjq9ym6Pj7N5H7L1NR1rVPJyw2v'
        ,136:'1UDHPdovvR985NrWSkdWQDEQ1xuRiTALq'
        ,137:'15nf31J46iLuK1ZkTnqHo7WgN5cARFK3RA'
        ,138:'1Ab4vzG6wEQBDNQM1B2bvUz4fqXXdFk2WT'
        ,139:'1Fz63c775VV9fNyj25d9Xfw3YHE6sKCxbt'
        ,140:'1QKBaU6WAeycb3DbKbLBkX7vJiaS8r42Xo'
        ,141:'1CD91Vm97mLQvXhrnoMChhJx4TP9MaQkJo'
        ,142:'15MnK2jXPqTMURX4xC3h4mAZxyCcaWWEDD'
        ,143:'13N66gCzWWHEZBxhVxG18P8wyjEWF9Yoi1'
        ,144:'1NevxKDYuDcCh1ZMMi6ftmWwGrZKC6j7Ux'
        ,145:'19GpszRNUej5yYqxXoLnbZWKew3KdVLkXg'
        ,146:'1M7ipcdYHey2Y5RZM34MBbpugghmjaV89P'
        ,147:'18aNhurEAJsw6BAgtANpexk5ob1aGTwSeL'
        ,148:'1FwZXt6EpRT7Fkndzv6K4b4DFoT4trbMrV'
        ,149:'1CXvTzR6qv8wJ7eprzUKeWxyGcHwDYP1i2'
        ,150:'1MUJSJYtGPVGkBCTqGspnxyHahpt5Te8jy'
        ,151:'13Q84TNNvgcL3HJiqQPvyBb9m4hxjS3jkV'
        ,152:'1LuUHyrQr8PKSvbcY1v1PiuGuqFjWpDumN'
        ,153:'18192XpzzdDi2K11QVHR7td2HcPS6Qs5vg'
        ,154:'1NgVmsCCJaKLzGyKLFJfVequnFW9ZvnMLN'
        ,155:'1AoeP37TmHdFh8uN72fu9AqgtLrUwcv2wJ'
        ,156:'1FTpAbQa4h8trvhQXjXnmNhqdiGBd1oraE'
        ,157:'14JHoRAdmJg3XR4RjMDh6Wed6ft6hzbQe9'
        ,158:'19z6waranEf8CcP8FqNgdwUe1QRxvUNKBG'
        ,159:'14u4nA5sugaswb6SZgn5av2vuChdMnD9E5'
        ,160:'1NBC8uXJy1GiJ6drkiZa1WuKn51ps7EPTv'
    }

    list_dec = {   # range of key_dec list
        67:73786976294838206464 
        ,68:147573952589676412927
        ,69:295147905179352825855
        ,70:590295810358705651711
        ,71:1180591620717411303423
        ,72:2361183241434822606847
        ,73:4722366482869645213695
        ,74:9444732965739290427391
        ,75:18889465931478580854783
        ,76:37778931862957161709567
        ,77:75557863725914323419135
        ,78:151115727451828646838271
        ,79:302231454903657293676543
        ,80:604462909807314587353087
        ,81:1208925819614629174706175
        ,82:2417851639229258349412351
        ,83:4835703278458516698824703
        ,84:9671406556917033397649407
        ,85:19342813113834066795298815
        ,86:38685626227668133590597631
        ,87:77371252455336267181195263
        ,88:154742504910672534362390527
        ,89:309485009821345068724781055
        ,90:618970019642690137449562111
        ,91:1237940039285380274899124223
        ,92:2475880078570760549798248447
        ,93:4951760157141521099596496895
        ,94:9903520314283042199192993791
        ,95:19807040628566084398385987583
        ,96:39614081257132168796771975167
        ,97:79228162514264337593543950335
        ,98:158456325028528675187087900671
        ,99:316912650057057350374175801343
        ,100:633825300114114700748351602687
        ,101:1267650600228229401496703205375
        ,102:2535301200456458802993406410751
        ,103:5070602400912917605986812821503
        ,104:10141204801825835211973625643007
        ,105:20282409603651670423947251286015
        ,106:40564819207303340847894502572031
        ,107:81129638414606681695789005144063
        ,108:162259276829213363391578010288127
        ,109:324518553658426726783156020576255
        ,110:649037107316853453566312041152511
        ,111:1298074214633706907132624082305023
        ,112:2596148429267413814265248164610047
        ,113:5192296858534827628530496329220095
        ,114:10384593717069655257060992658440191
        ,115:20769187434139310514121985316880383
        ,116:41538374868278621028243970633760767
        ,117:83076749736557242056487941267521535
        ,118:166153499473114484112975882535043071
        ,119:332306998946228968225951765070086143
        ,120:664613997892457936451903530140172287
        ,121:1329227995784915872903807060280344575
        ,122:2658455991569831745807614120560689151
        ,123:5316911983139663491615228241121378303
        ,124:10633823966279326983230456482242756607
        ,125:21267647932558653966460912964485513215
        ,126:42535295865117307932921825928971026431
        ,127:85070591730234615865843651857942052863
        ,128:170141183460469231731687303715884105727
        ,129:340282366920938463463374607431768211455
        ,130:680564733841876926926749214863536422911
        ,131:1361129467683753853853498429727072845823
        ,132:2722258935367507707706996859454145691647
        ,133:5444517870735015415413993718908291383295
        ,134:10889035741470030830827987437816582766591
        ,135:21778071482940061661655974875633165533183
        ,136:43556142965880123323311949751266331066367
        ,137:87112285931760246646623899502532662132735
        ,138:174224571863520493293247799005065324265471
        ,139:348449143727040986586495598010130648530943
        ,140:696898287454081973172991196020261297061887
        ,141:1393796574908163946345982392040522594123775
        ,142:2787593149816327892691964784081045188247551
        ,143:5575186299632655785383929568162090376495103
        ,144:11150372599265311570767859136324180752990207
        ,145:22300745198530623141535718272648361505980415
        ,146:44601490397061246283071436545296723011960831
        ,147:89202980794122492566142873090593446023921663
        ,148:178405961588244985132285746181186892047843327
        ,149:356811923176489970264571492362373784095686655
        ,150:713623846352979940529142984724747568191373311
        ,151:1427247692705959881058285969449495136382746623
        ,152:2854495385411919762116571938898990272765493247
        ,153:5708990770823839524233143877797980545530986494
        ,154:11417981541647679048466287755595961091061972988
        ,155:22835963083295358096932575511191922182123945976
        ,156:45671926166590716193865151022383844364247891952
        ,157:91343852333181432387730302044767688728495783904
        ,158:182687704666362864775460604089535377456991567808
        ,159:365375409332725729550921208179070754913983135616
        ,160:730750818665451459101842416358141509827966271232
        ,161:1461501637330902918203684832716283019655932542464
    }

    SOLVED = [66,70,75,80,85,90,95,100,105,110,115,120,125]
    # ================================================================ 

    # print p_addr
    p_addr = list_addr[P]      # ================================================================ address here

    # nkeys scan
    n= 10**10 # 10 B
    if n!= 10**10 : exit('nmust = 10 B -- fix it')

    len_n = len(str(n))
    if len_n != 11 : exit('len_n must = 11 <=> 10 B -- fix it')

    len_tail = len_n -1 
    if len_tail != 10 : exit('len_tail must = 10 -- fix it')

    len__h_s = len(str(list_dec[P])) - len_tail
    len__h_e = len(str(list_dec[P+1])) - len_tail

    save_file_name = "x" + str(P) + ".txt"
    path__data = save_file_name

    h_s = int(str(list_dec[P])[0:len__h_s])
    h_e = int(str(list_dec[P+1])[0:len__h_e])
    r__tail_e__10b= 10**len_tail

    # generate PRIV
    priv_dec = random.randint(h_s, h_e)        # priv_dec here ==================================================================

    priv_dec_full = priv_dec * r__tail_e__10b
    priv__h__e = priv_dec_full + r__tail_e__10b * xN
    priv_hex_start = hex(priv_dec_full)[2:]
    priv_hex_end = hex(priv__h__e)[2:]

    rangee = str(priv_hex_start) + ":" + str(priv_hex_end) # range here ================================================================


    print()
    print('address : ',p_addr) 
    print('h_s     ::',h_s,'(',len(str(h_s)),')')
    print('h_e     ::',h_e,'(',len(str(h_e)),')')
    print()
    print("priv_dec    :", priv_dec ,"---------->", (priv_dec - h_s) / (h_e - h_s) * 100 ,' %' )
    #print("rangee : ", rangee)
    #print()


    # check DATA + create list priv_dec into array
    priv_dec__copy = priv_dec
    for i in range(xN):
        check_data(path__data, priv_dec__copy,h_s,h_e)
        print("priv_dec : ==> ",priv_dec__copy)
        priv_dec__copy += 1

    txt = p_addr +"_"+ str(priv_dec) +"_"+rangee
    return txt
)";

    // Thực thi mã Python
    PyRun_SimpleString(pythonCode);

    // Lấy hàm run_python từ Python
    PyObject* mainModule = PyImport_AddModule("__main__");
    PyObject* mainDict = PyModule_GetDict(mainModule);
    PyObject* convertFunc = PyDict_GetItemString(mainDict, "run_python");
    
    // Kiểm tra hàm có tồn tại không
    if (convertFunc && PyCallable_Check(convertFunc)) {
        // Gọi hàm
        // PyObject* args = PyTuple_Pack(2, PyLong_FromLong(P), PyLong_FromLong(xN));
		PyObject* args = Py_BuildValue("(ll)", P, xN);
        PyObject* result = PyObject_CallObject(convertFunc, args);
        Py_DECREF(args);

		// Xử lý kết quả
		if (result) {
            const char* resultStr = PyUnicode_AsUTF8(result);
            std::string txt = resultStr;

            Py_DECREF(result);
            Py_Finalize(); // Kết thúc Python		

			return txt;

        } else {
            PyErr_Print();
            std::cerr << "Error calling Python function." << std::endl;
        }

    } else {   std::cerr << "Function not found or not callable." << std::endl;   }


    // Kết thúc Python 
    Py_Finalize();
    return "error";
}

// ============================================== hiiu code =============================================

void run(){
	// check file $.txt exist or not
	// check_file_exist(); //$.txt
	
	// Global Init
	Timer::Init();
	rseed(Timer::getSeed32());

	bool gpuEnable = true;
	bool gpuAutoGrid = true;
	int compMode = SEARCH_COMPRESSED;
	vector<int> gpuId = { 0 };
	// vector<int> gpuId;
	vector<int> gridSize;

	string outputFile = "$.txt";
	string inputFile = "";	// for both multiple hash160s and x points
	string address = "";	
	string rangee = "";
	string priv_dec = "";
	// string address = "13zb1hQbWVsc2S7ZTZnP2G4undNNpdh5so";	

	std::vector<unsigned char> hashORxpoint;
	int nbCPUThread = Timer::getCoreNumber();

	uint32_t maxFound = 1024 * 64;

	Int rangeStart;
	Int rangeEnd;
	rangeStart.SetInt32(0);
	rangeEnd.SetInt32(0);

	int searchMode = SEARCH_MODE_SA;
	int coinType = COIN_BTC;

	hashORxpoint.clear();

	std::cout<< "===================================================" << std::endl;   

	long P = 67;
	// std::cout <<"nhập P = "; std::cin >> P ; std::cout << std::endl;
	long xN = 1;
	// std::cout <<"nhập xN = "; std::cin >> xN ; std::cout << std::endl;


	std::string gett = hiiu_random_priv_dec(P,xN); //p_addr +"__"+ str(priv_dec) +"__"+rangee
	// std::cout<<"------gett : "<<gett<<std::endl;

    string arr[3];
	stringstream ss(gett);
	string word;
	int i = 0;
	while(getline(ss, word, '_')){ 
		// cout << i << " : " << word << endl;
        arr[i] = word;
		++i;
	}

	address = arr[0];
	priv_dec = arr[1];
	rangee = arr[2];

    //--------------------- test 
    // priv_dec = "2222222";

    // address = "18XrHzZqJeDpVHmEbssY4bv2ahk8kYjSc8";
    // rangee ="1ef0a26a7297f088f8e6dd4f86f84fd0ffed2644d7bf6bf266c5c6fc32911fb0:1ef0a26a7297f088f8e6dd4f86f84fd0ffed2644d7bf6bf266c5c6fc43911fb0";

    // address = "13zb1hQbWVsc2S7ZTZnP2G4undNNpdh5so";
    // rangee ="2832ed74f00000000:2832ed74f90000000";

    // address = "1PfGv571usg6bFKM1Nkaj5gkXjVJfky2LG";
    // rangee ="08e05472b8a000b51cbcb9144f03792070c79819973b53daaf9f73fb00000000:08e05472b8a000b51cbcb9144f03792070c79819973b53daaf9f73fbff000000";

	parseRange(rangee, rangeStart, rangeEnd);

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

	printf("\n");
	printf("\n");
	printf("GPU IDS      : ");
	for (int i = 0; i < gpuId.size(); i++) {
		printf("%d", gpuId.at(i));
		if (i + 1 < gpuId.size()){	printf(", "); }
	}
	printf("\n");
	printf("GPU GRIDSIZE : ");
	for (int i = 0; i < gridSize.size(); i++) {
		printf("%d", gridSize.at(i));
		if (i + 1 < gridSize.size()) {
			if ((i + 1) % 2 != 0) {		printf("x");	}
		}
	}
	if (gpuAutoGrid) { 
		printf(" (Auto grid size)\n");
	} 
	
	printf("MAX FOUND    : %d\n", maxFound);
	printf("BTC ADDRESS  : %s\n", address.c_str());
	printf("OUTPUT FILE  : %s\n", outputFile.c_str());

	signal(SIGINT, CtrlHandler);
	KeyHunt* v;
	v = new KeyHunt(hashORxpoint, compMode, searchMode, coinType, gpuEnable, outputFile,
		maxFound, rangeStart.GetBase16(), rangeEnd.GetBase16(), should_exit, priv_dec, xN, P);
	v->Search(gpuId, gridSize, should_exit);

	delete v;
};

int main(){
	int xTime = 9999; 
	int sleepTime = 10; //fixx
    std::cout << "sleepTime xT : "; std::cin >> sleepTime; std::cout<< endl;  //----------- fix


	for (int i = 0; i < xTime; i++)
	{
		std::cout<< std::endl << std::endl << "xN =! -- sleep : "<< sleepTime << " s" << std::endl; 
		run();
		
        // sleep time --- print coutdown
        for (int j = sleepTime; j >= 0; j--)
        {
            sleep(1);      // Timer::SleepMillis(1000);
            printf("----->  %d s  <-----",j);
            fflush(stdout);
            printf("\r");
        }
        printf("\n");
	}
	return 0;
};