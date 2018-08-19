CC = clang
CC_FLAGS = -Wall -std=c11 -g3
LD_FLAGS =
CC_INCLUDE = -I ./

bin/ :
	mkdir -p $@

RILL_VM := $(patsubst vm/include/%.h, vm/build/%.o, $(wildcard vm/include/*.h))
vm/build/ :
	mkdir -p $@
vm/build/%.o: vm/src/%.c
	$(CC) $(CC_FLAGS) -I vm/include/ $(CC_INCLUDE) $< -c -o $@
vm : RILL_VM

RILL_LANG := $(patsubst lang/include/%.h, lang/build/%.o, $(wildcard lang/include/*.h))
lang/build/ :
	mkdir -p $@
lang/build/%.o: lang/src/%.c
	$(CC) $(CC_FLAGS) $(CC_INCLUDE) $< -c -o $@
lang : RILL_LANG

RILL_ALL = $(RILL_VM) $(RILL_LANG)

TEST_FILES = $(shell find ./ -maxdepth 3 -regex .*/tests/.*_test\.c | sort)
bin/rill-test : bin/ test/include/manifest.h test/src/main.c $(RILL_ALL)
	echo "TEST FILES: $(TEST_FILES)"
	$(CC) $(CC_FLAGS) -I test/include/ $(CC_INCLUDE) \
	$(RILL_ALL) \
	$(TEST_FILES) \
	test/src/main.c \
	test/src/test.c \
	test/src/manifest.c -o $@
tests : bin/rill-test
test  : bin/rill-test

test/include/manifest.h : $(TEST_FILES) test/generate-manifest.sh
	test/generate-manifest.sh

clean :
	rm -rf bin/* vm/build/* lang/build/*
	rm -f test/include/manifest.h
	rm -f test/src/manifest.c
