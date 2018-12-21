CC := gcc

CC_INCLUDE := -I include/

CC_FLAGS = -Wall -std=c11 $(CC_INCLUDE)
CC_FLAGS_DEVELOP  := -O0 -g
CC_FLAGS_RELEASE  := -O3 -DNDEBUG -s
CC_FLAGS_COVERAGE := --coverage -fprofile-dir="test/coverage/" \
		-fprofile-generate="test/coverage/"

CC_COMPILE = $(CC) $(CC_INCLUDE) $(CC_FLAGS)
CC_COMPILE_OBJECT = $(CC) $(CC_INCLUDE) -c $(CC_FLAGS)

build/rval/%.o : src/rval/%.c include/rval/%.h
	$(CC_COMPILE_OBJECT) $< -o $@
RVAL := $(patsubst src/rval/%.c, \
	build/rval/%.o, \
	$(shell find src/rval/ | grep \\.c))

RILL := $(RVAL)

TESTS = $(shell find test/ | grep \\.test\\.c$)

test-coverage : CC_FLAGS += $(CC_FLAGS_COVERAGE)
test-coverage : test/coverage/.lcov-output
	cd test/coverage/ && genhtml coverage.info --output-directory html
test/coverage/.lcov-output : test/coverage/.gcov-output
	lcov --capture --directory ./ --output-file test/coverage/coverage.info
	touch $<
test/coverage/.gcov-output : test/coverage/.profile-output
	gcov --object-directory test/coverage/ test/coverage/*.gcno
	touch $@
test/coverage/.profile-output : bin/rill-test
	cd test/coverage && GCOV_PREFIX_STRIP=99 ../../bin/rill-test
	mv $(shell find . -name "*.gcno" -not -path test/coverage) -t test/coverage/
	touch $@

test : CC_FLAGS += $(CC_FLAGS_DEVELOP)
test : bin/rill-test

bin/rill-test : CC_INCLUDE += -I test/include/
bin/rill-test : $(RILL) $(TESTS) test/main.c test/rill_test.c
	$(CC_COMPILE) $^ -o $@

clean :
	rm -f bin/*
	rm -f $(shell find build/ | grep \\.o$)
	rm -rf test/coverage/*
	rm -rf test/coverage/.profile-output
	rm -rf test/coverage/.gcov-output
	rm -rf test/coverage/.lcov-output
