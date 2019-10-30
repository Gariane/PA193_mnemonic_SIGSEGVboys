SRCDIR=../build
UTILSDIR=utils

FUZZCOUNT=100
RADAMSA = /bin/radamsa

ifeq (, $(shell which /bin/valgrind))
	$(error "No valgrind in $PATH")
endif

.PHONY: dict_run dict_fuzz

entropy_run: entropy_fuzz
	$(MAKE) $(patsubst %.txt,%.out,$(wildcard fuzzed_inputs/fuzz_*.txt))

entropy_fuzz: $(SRCDIR)/cli
	[ -d fuzzed_inputs ] || mkdir fuzzed_inputs; \
	rm fuzzed_inputs/*; \
	$(RADAMSA) -o fuzzed_inputs/fuzz_%n.txt -n $(FUZZCOUNT) data/entropy_fuzz.txt
	
fuzzed_inputs/%.out: $(SRCDIR)/cli fuzzed_inputs/%.txt 
	valgrind ./$< -d ../wordlists/english.txt -g $(patsubst %.out,%.txt,$@) > $@ 2>&1; \
	[ $$? -eq 0 ] || echo $@ >> fuzzed_inputs/failures.txt
