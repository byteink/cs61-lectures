PROGRAMS = manyfork myecho runmyecho forkmyecho spawnmyecho \
	waitdemo

all: $(PROGRAMS)

ALLPROGRAMS = fork1 fork2 fork2b fork3 \
	forkmix-file forkmix-stdio forkmix-syscall \
	manyfork myecho runmyecho forkmyecho spawnmyecho \
	waitdemo \
	selfpipe childpipe pipesizer filtermultiples primesieve \
	timedwait01-poll timedwait02-block timedwait03-blockvar \
	timedwait04-alarm timedwait05-selfpipe timedwait06-signalfd

O = 2
include ../common/rules.mk

%.o: %.cc $(BUILDSTAMP)
	@$(call xrun,$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPCFLAGS) $(O) -o $@ -c,COMPILE,$<)

$(PROGRAMS): %: %.o
	@$(call xrun,$(CXX) $(CXXFLAGS) $(O) $(LDFLAGS) -o $@ $^ $(LIBS),LINK $@)


clean:
	rm -f $(ALLPROGRAMS) *.o data
	rm -rf $(DEPSDIR) *.dSYM

.PHONY: all clean
