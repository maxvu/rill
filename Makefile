CC := gcc

CC_INCLUDE := -I include/

CC_FLAGS = -Wall -std=c11 $(CC_INCLUDE)
CC_FLAGS_DEVELOP := -O0 -g
CC_FLAGS_RELEASE := -O3 -DNDEBUG -s

CC_COMPILE = $(CC) $(CC_INCLUDE) $(CC_FLAGS)
CC_COMPILE_OBJECT = $(CC) $(CC_INCLUDE) -c $(CC_FLAGS)

build/rval/%.o : src/rval/%.c include/rval/%.h
	$(CC_COMPILE_OBJECT) $< -o $@
RVAL := $(patsubst src/rval/%.c, \
	build/rval/%.o, \
	$(shell find src/rval/ | grep \\.c))

RILL := $(RVAL)

TESTS := $(shell find test/ | grep \\.test\\.c$)

test : CC_FLAGS += $(CC_FLAGS_DEVELOP)
test : bin/rill-test

bin/rill-test : CC_INCLUDE += -I test/include/
bin/rill-test : $(RILL) $(TESTS) test/main.c test/rill_test.c
	$(CC_COMPILE) $^ -o $@

clean :
	rm -f bin/*
	rm -f $(shell find build/ | grep \\.o$)
