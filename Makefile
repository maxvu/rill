CC = clang
CC_FLAGS = -Wall -std=c11 -g
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

bin/rill-test : bin/ $(RILL_VM) $(RILL_LANG)
	$(CC) $(CC_FLAGS) -I tests/include/ $(CC_INCLUDE)  $(wildcard tests/src/*.c) -o $@
tests : bin/rill-test

clean :
	rm -rf bin/* vm/build/* lang/build/*
