
SRCFILES := $(wildcard *.cc)
FORTRAMPS := $(wildcard *.f)

ifdef GPU
CUDAFILES := $(wildcard *cu)
endif

.PHONY: default

default: $(LIB)

%.a: $(SRCFILES:.cc=.o) $(FORTRAMPS:.f=.o) $(CUDAFILES:.cu=.o)
	ar -rv $@ $^

%.o : %.f
	gfortran -c -O3 -o $@ $<

%.o : %.cc
	$(CXX) $(CXX_FLAGS) -M -o $*.d $< $(INC_DIR) ; \
	cp $*.d $*.dep; \
	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.dep; \
	rm -f $*.d $*.d.bak
	$(CXX) $(CXX_FLAGS) -c -o $@ $< $(INC_DIR)

%.o : %.cu
	$(NVCC) $(CUDA_FLAGS) -M -o $*.d $< $(INC_DIR) ; \
	cp $*.d $*.dep; \
	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.dep; \
	rm -f $*.d $*.d.bak
	$(NVCC) $(CUDA_FLAGS) -c -o $@ $< $(INC_DIR)

clean:
	rm *.o *.dep *.a

-include $(SRCFILES:.cc=.dep)
