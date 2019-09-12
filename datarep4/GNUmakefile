BASEPROGRAMS = mexplore4 msurprise ubpointer
BASEPROGRAMS_NOOPT = $(patsubst %,%.noopt,$(BASEPROGRAMS))

MEMBENCH_PROGRAMS = mb-malloc
ifneq ($(findstring /,$(shell whereis libjemalloc 2>/dev/null)),)
MEMBENCH_PROGRAMS += mb-jemalloc
endif
ifneq ($(findstring /,$(shell whereis libtcmalloc 2>/dev/null)),)
MEMBENCH_PROGRAMS += mb-tcmalloc
endif
MEMBENCH_PROGRAMS += $(patsubst mb-%.cc,mb-%,$(sort $(wildcard mb-*.cc)))

PROGRAMS = $(BASEPROGRAMS) $(BASEPROGRAMS_NOOPT) $(MEMBENCH_PROGRAMS)
all: $(PROGRAMS)

ALLPROGRAMS = $(PROGRAMS)

PIE ?= 0
O ?= 3
COMPILER ?= clang
include ../common/rules.mk

%.o: %.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(O) $(DEPCFLAGS) -o $@ -c $<

%.opt.o: %.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -O3 $(DEPCFLAGS) -o $@ -c $<

%.noopt.o: %.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -O0 $(DEPCFLAGS) -o $@ -c $<

$(BASEPROGRAMS): %: %.o hexdump.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^

$(patsubst %,%.opt,$(BASEPROGRAMS)): %.opt: %.opt.o hexdump.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -O3 -o $@ $^

$(patsubst %,%.noopt,$(BASEPROGRAMS)): %.noopt: %.noopt.o hexdump.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -O0 -o $@ $^


mb-%: membench.o mb-%.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^ -lpthread

mb-tcmalloc: membench.o mb-malloc.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^ -lpthread -ltcmalloc

mb-jemalloc: membench.o mb-malloc.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^ -lpthread -ljemalloc


clean:
	rm -rf $(ALLPROGRAMS) *.o $(DEPSDIR)

.PHONY: all clean
