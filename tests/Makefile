BINDIR=../build
REF=python3 /home/sabi1k98/Documents/python-mnemonic/build/lib/mnemonic/mnemonic.py
UTILSDIR=utils
COMP=./comp.sh

FUZZCOUNT=100
RADAMSA=/bin/radamsa

ifeq (, $(shell which /bin/valgrind))
	$(error "No valgrind in $PATH")
endif

.PHONY: mnemonic_fuzz mnemonic_run entropy_run entropy_fuzz

entropy_run: entropy_fuzz
	$(MAKE) $(patsubst %.txt,%.out,$(wildcard fuzzed_inputs/entropy/fuzz_*.txt))

mnemonic_run: mnemonic_fuzz
	$(MAKE) $(patsubst %.txt,%.out,$(wildcard fuzzed_inputs/mnemonic/fuzz_*.txt))

entropy_fuzz: $(BINDIR)/cli
	[ -d fuzzed_inputs/entropy ] || mkdir -p fuzzed_inputs/entropy; \
	$(RM) fuzzed_inputs/entropy/*; \
	$(RADAMSA) -o fuzzed_inputs/entropy/fuzz_%n.txt -n $(FUZZCOUNT) data/entropy_fuzz.txt

mnemonic_fuzz: $(BINDIR)/cli
	[ -d fuzzed_inputs/mnemonic ] || mkdir -p fuzzed_inputs/mnemonic; \
	$(RM) fuzzed_inputs/mnemonic/*; \
	$(RADAMSA) -o fuzzed_inputs/mnemonic/fuzz_%n.txt -n $(FUZZCOUNT) data/mnemonic_fuzz.txt
	
fuzzed_inputs/entropy/%.out: $(BINDIR)/cli fuzzed_inputs/entropy/%.txt 
	-$(COMP) "$< -d ../wordlists/english.txt -g $(patsubst %.out,%.txt,$@) > $@ 2>&1" \
	"$(REF) < $(patsubst %.out,%.txt,$@)" $@ $@.ref;
	[ $$? -eq 0 ] || echo $@ >> fuzzed_inputs/entropy/failures.txt;


fuzzed_inputs/mnemonic/%.out: $(BINDIR)/cli fuzzed_inputs/mnemonic/%.txt 
	-$(COMP) "$< -d ../wordlists/english.txt -g $(patsubst %.out,%.txt,$@) > $@ 2>&1" \
	"$(REF) -a < $(patsubst %.out,%.txt,$@)" $@ $@.ref;
	[ $$? -eq 0 ] || echo $@ >> fuzzed_inputs/mnemonic/failures.txt;
