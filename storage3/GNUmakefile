PROGRAMS = $(sort $(patsubst %.cc,%,$(wildcard [rw][0-9]*.cc))) \
	coherence cache

-include conf.mk
ifndef DATAFILE
DATAFILE = data
endif

all: $(PROGRAMS) $(DATAFILE)

ALLPROGRAMS = $(PROGRAMS)

O = 2
include ../common/rules.mk
ifneq ($(DATAFILE),data)
CPPFLAGS += -DDATAFILE='"$(DATAFILE)"'
endif

%.o: %.cc $(BUILDSTAMP)
	@$(call xrun,$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPCFLAGS) $(O) -o $@ -c,COMPILE,$<)

r%: r%.o
	@$(call xrun,$(CXX) $(CXXFLAGS) $(O) $(LDFLAGS) -o $@ $^ $(LIBS),LINK $@)

w%: w%.o
	@$(call xrun,$(CXX) $(CXXFLAGS) $(O) $(LDFLAGS) -o $@ $^ $(LIBS),LINK $@)

coherence cache: %: %.o
	@$(call xrun,$(CXX) $(CXXFLAGS) $(O) $(LDFLAGS) -o $@ $^ $(LIBS),LINK $@)

matrixmultiply: matrixmultiply.o
	$(CXX) $(CXXFLAGS) $(O) -o $@ $(LDFLAGS) $(LIBS) $^

base-matrixmultiply: base-matrixmultiply.o
	$(CXX) $(CXXFLAGS) $(O) -o $@ $(LDFLAGS) $(LIBS) $^

DATASIZE := $(shell wc -c $(DATAFILE) 2>/dev/null | awk '{ print $$1 }')
DATADEP := $(shell if test "$(DATASIZE)" -lt 51200000 2>/dev/null; then echo always; fi)
DATADEP_LARGE := $(shell if test "$(DATASIZE)" -lt 5120000000 2>/dev/null; then echo always; fi)

$(DATAFILE): $(DATADEP)
	yes 77777777777777777777777777777777777777777 | tr -d '\n' | head -c 51200000 > $@

$(DATAFILE)-large: $(DATADEP_LARGE)
	yes 77777777777777777777777777777777777777777 | tr -d '\n' | head -c 5120000000 > $@

ifneq ($(DATAFILE),data)
data: $(DATAFILE)
data-large: $(DATAFILE)-large
.PHONY: data data-large
endif


clean:
	rm -f $(ALLPROGRAMS) *.o data
	rm -rf $(DEPSDIR) *.dSYM
	for i in r[0-9][0-9]* w[0-9][0-9]*; do if file $$i | grep executable >/dev/null 2>&1; then rm -f $$i; fi; done

cold:
	sync
	echo 3 | sudo tee /proc/sys/vm/drop_caches > /dev/null
	sudo blockdev --flushbufs `df $(DATAFILE) | grep /dev | awk '{ print $$1 }'`

.PHONY: all always clean cold
.PRECIOUS: $(DATAFILE) $(DATAFILE)-large
