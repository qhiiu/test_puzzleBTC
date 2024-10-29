#---------------------------------------------------------------------

OBJDIR = obj

OBJET = $(addprefix $(OBJDIR)/, \
        Base58.o IntGroup.o Main.o Random.o Timer.o Int.o \
        IntMod.o Point.o SECP256K1.o KeyHunt.o \
        hash/ripemd160.o hash/sha256.o hash/sha512.o \
        hash/ripemd160_sse.o hash/sha256_sse.o hash/keccak160.o \
        GPU/GPUEngine.o GmpUtil.o )

CXX        = g++
CUDA       = /usr/local/cuda-12.6
CXXCUDA    = /usr/bin/g++
NVCC       = $(CUDA)/bin/nvcc
# nvcc requires joint notation w/o dot, i.e. "5.2" -> "52"
CCAP = 61 #https://developer.nvidia.com/cuda-gpus
ccap       = $(shell echo $(CCAP) | tr -d '.')

CXXFLAGS   =  -DWITHGPU -m64 -mssse3 -Wno-write-strings -O2 -I. -I$(CUDA)/include

LFLAGS     = -lgmp -lpthread -L$(CUDA)/lib64 -lcudart 

#--------------------------------------------------------------------

$(OBJDIR)/GPU/GPUEngine.o: GPU/GPUEngine.cu
	$(NVCC) -maxrregcount=0 --ptxas-options=-v --compile --compiler-options -fPIC -ccbin $(CXXCUDA) -m64 -O2 -I$(CUDA)/include -gencode=arch=compute_$(ccap),code=sm_$(ccap) -o $(OBJDIR)/GPU/GPUEngine.o -c GPU/GPUEngine.cu

$(OBJDIR)/%.o : %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

all: KeyHunt

KeyHunt: $(OBJET)
	@echo Making puzzleBTC ...
	$(CXX) $(OBJET) $(LFLAGS) -o puzzleBTC

$(OBJET): | $(OBJDIR) $(OBJDIR)/GPU $(OBJDIR)/hash

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/GPU: $(OBJDIR)
	cd $(OBJDIR) &&	mkdir -p GPU

$(OBJDIR)/hash: $(OBJDIR)
	cd $(OBJDIR) &&	mkdir -p hash

clean:
	@echo Cleaning...
	@rm -f obj/*.o
	@rm -f obj/GPU/*.o
	@rm -f obj/hash/*.o
	@rm -d obj/GPU 
	@rm -d obj/hash 
	@rm -d obj
	@rm -f puzzleBTC
<<<<<<< HEAD
	@echo Cleaning done
=======
	@echo Cleaning done
>>>>>>> ba35168e905b1ab3b389766f458ea04ad34b4f12
