INC_DIR :=  -I.. \
	-I$(ROOTSYS)/include/root -I$(AMPTOOLS) -I../../JPsi \
	-I$(ROOT_FASTMC) -I$(CLAS12PHOTONS_AMPTOOLS)/src

LIB_DIR := -L$(ROOTSYS)/lib \
	-L$(AMPTOOLS)/lib -L../../JPsi/lib -L$(FASTMC) -L$(ROOT_FASTMC) -L$(CLAS12PHOTONS_AMPTOOLS)/lib

ROOTLIBS := $(shell root-config --glibs)

CXX := g++
#CXX_FLAGS := -O3 -m32
CXX_FLAGS := -O3
LINK_FLAGS := -Wl,-u,G__cpp_setupdict
LINK_FLAGS := -Wl,-u,G__cpp_setupdict

ifdef GPU

INC_DIR += -I$(CUDA_INSTALL_PATH)/include
LIB_DIR += -L$(CUDA_INSTALL_PATH)/lib

LIBS :=  -lJPsi_GPU -lAmpTools_GPU -lCLHEP $(ROOTLIBS)  \
	-lcuda -lcudart -lstdc++ 
CXX_FLAGS += -DGPU_ACCELERATION
else

LIBS :=  -lJPsi -lClas12Photons_AmpTools -lAmpTools -lProofPlayer -lProof $(ROOTLIBS)  \
	-lstdc++ -lEG -lfastmc -lFastMC 

endif

SRCFILES := $(wildcard *.cc)
TARGET_EXE := $(subst .cc,_exe,$(SRCFILES))

.PHONY: default

default: exe

# generic build rule (requires all libraries)
exe:
	$(CXX) $(CXX_FLAGS) $(LINK_FLAGS) -o doMonteCarlo doMonteCarlo.cc $(ROOT_FASTMC)/TFastMCDict.cxx $(ROOT_FASTMC)/TFastMC.cxx $(INC_DIR) $(LIB_DIR) $(LIBS)

clean:
	rm -f *.o *.dep doMonteCarlo

