BASEPROGRAMS = mexplore0 mexplore1 mexplore2 mexplore3 mexplore4 \
	msurprise
BASEPROGRAMS_OPT = $(patsubst %,%.opt,$(BASEPROGRAMS))
BASEPROGRAMS_NOOPT = $(patsubst %,%.noopt,$(BASEPROGRAMS))
PROGRAMS = $(BASEPROGRAMS) $(BASEPROGRAMS_OPT)
all: $(PROGRAMS)

ALLPROGRAMS = $(BASEPROGRAMS) $(BASEPROGRAMS_OPT) \
	$(BASEPROGRAMS_NOOPT) mexplore mexplore.opt mexplore.noopt

PIE ?= 0
O ?= 0
COMPILER ?= clang
include ../common/rules.mk

%.o: %.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(O) $(DEPCFLAGS) -o $@ -c $<

$(BASEPROGRAMS): %: %.o hexdump.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^

%.opt.o: %.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -O3 $(DEPCFLAGS) -o $@ -c $<

$(patsubst %,%.opt,$(BASEPROGRAMS)): %.opt: %.opt.o hexdump.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -O3 -o $@ $^

clean:
	rm -rf $(ALLPROGRAMS) *.o $(DEPSDIR)

.PHONY: all clean
