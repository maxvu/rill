CC := gcc

CC_INCLUDE := -I include/

CC_FLAGS = -Wall -std=c11 $(CC_INCLUDE) -fno-omit-frame-pointer
CC_FLAGS_DEVELOP  := -O0 -g
CC_FLAGS_RELEASE  := -O3 -DNDEBUG -s
CC_FLAGS_COVERAGE := --coverage -fprofile-dir="coverage/" \
		-fprofile-generate="coverage/"

CC_COMPILE = $(CC) $(CC_INCLUDE) $(CC_FLAGS)
CC_COMPILE_OBJECT = $(CC) $(CC_INCLUDE) -c $(CC_FLAGS)

RVAL := $(patsubst "src/rval/%c", "build/rval/%.o", $(wildcard src/rval/*.c))
build/rval/%.o : src/rval/%.c
	$(CC_COMPILE_OBJECT) $^ -o $@

RLEX := $(patsubst "src/rlex/%c", "build/rlex/%.o", $(wildcard src/rlex/*.c))
build/rval/%.o : src/rlex/%.c
	$(CC_COMPILE_OBJECT) $^ -o $@

UTIL := $(patsubst "src/util/%c", "build/util/%.o", $(wildcard src/util/*.c))
build/util/%.o : src/util/%.c
	$(CC_COMPILE_OBJECT) $^ -o $@

TESTS := $(shell find test/ | grep \.test\.c)

RILL := $(RVAL) $(RLEX) $(UTIL)

entry:
	@echo $(RVAL)
	@echo $(UTIL)

rill : CC_FLAGS += $(CC_FLAGS_DEVELOP)
rill : bin/rill

release : CC_FLAGS += $(CC_FLAGS_RELEASE)
release : bin/rill

bin/rill : $(RILL) src/rill/main.c
	$(CC_COMPILE) $^ -o $@

# Requires gcov, lcov and genhtml.
coverage : CC_FLAGS += $(CC_FLAGS_COVERAGE)
coverage : clean coverage/.lcov-output
	cd coverage/ && genhtml coverage.info --output-directory html
coverage/.lcov-output : coverage/.gcov-output
	lcov --capture --directory ./ --output-file coverage/coverage.info
	touch $<
coverage/.gcov-output : coverage/.profile-output
	gcov --object-directory coverage/ coverage/*.gcno
	touch $@
coverage/.profile-output : bin/rill-test
	cd coverage && GCOV_PREFIX_STRIP=99 ../bin/rill-test
	mv $(shell find . -name "*.gcno" -not -path coverage) -t coverage/
	touch $@

test : CC_FLAGS += $(CC_FLAGS_DEVELOP)
test : bin/rill-test

bin/rill-test : CC_INCLUDE += -I test/
bin/rill-test : $(RILL) $(TESTS) src/test/main.c src/test/test.c src/test/manifest.c
	$(CC_COMPILE) $^ -o $@

clean :
	rm -f bin/*
	rm -f $(shell find build/ | grep \\.o$)
	rm -rf coverage/*
	rm -rf coverage/.profile-output
	rm -rf coverage/.gcov-output
	rm -rf coverage/.lcov-output
