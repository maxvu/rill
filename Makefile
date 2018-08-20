CC = clang
CC_FLAGS = -Wall -std=c11 -g3
LD_FLAGS =
CC_INCLUDE = -I ./

bin/ :
	mkdir -p $@
build/ :
	mkdir -p $@
build/rval/ : build/
	mkdir -p $@

RVAL_SRC := $(wildcard rval/*.c)
RVAL_INC := $(patsubst rval/%.c, rval/%.h, $(RVAL_SRC))
RVAL_OBJ := $(patsubst rval/%.c, build/rval/%.o, $(wildcard rval/*.c))
build/rval/%.o : rval/%.c rval/%.h build/rval/
	$(CC) $(CC_FLAGS) $(CC_INCLUDE) $< -c -o $@
rval : $(RVAL_OBJ)

RILL_OBJ := $(RVAL_OBJ)

RILL_TESTS := $(shell find test/tests/ -regex .*\.c)
test/manifest.h : $(RILL_TESTS)
	test/generate.sh
bin/rill-test : $(RILL_OBJ) test/manifest.h
	$(CC) $(CC_FLAGS) $(CC_INCLUDE) \
		$(RILL_OBJ) \
		$(RILL_TESTS) \
		test/main.c \
		test/manifest.c \
		-o $@
test  : bin/rill-test
tests : bin/rill-tests
