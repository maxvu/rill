CC := clang

CC_INCLUDE := -I include/

CC_FLAGS = -Wall -std=c11 $(CC_INCLUDE) -fno-omit-frame-pointer
CC_FLAGS_DEVELOP  := -O0 -g
CC_FLAGS_RELEASE  := -O3 -DNDEBUG -s
CC_FLAGS_COVERAGE := --coverage -fprofile-dir="coverage/" \
		-fprofile-generate="coverage/"

CC_COMPILE = $(CC) $(CC_INCLUDE) $(CC_FLAGS)
CC_COMPILE_OBJECT = $(CC) $(CC_INCLUDE) -c $(CC_FLAGS)

bin/ :
	mkdir $@
build/ :
	mkdir $@

CONFIG_SRC = $(wildcard src/config/*.c)
CONFIG_OBJ = $(CONFIG_SRC:src/%.c=build/%.o)
build/config/ : | build/
	mkdir $@
build/config/%.o : src/config/%.c | build/config/
	$(CC_COMPILE_OBJECT) $^ -o $@

RVAL_SRC = $(wildcard src/rval/*.c)
RVAL_OBJ = $(RVAL_SRC:src/%.c=build/%.o)
build/rval/ : | build/
	mkdir $@
build/rval/%.o : src/rval/%.c | build/rval/
	$(CC_COMPILE_OBJECT) $^ -o $@

RLEX_SRC = $(wildcard src/rlex/*.c)
RLEX_OBJ = $(RLEX_SRC:src/%.c=build/%.o)
build/rlex/ : | build/
	mkdir $@
build/rlex/%.o : src/rlex/%.c | build/rlex/
	$(CC_COMPILE_OBJECT) $^ -o $@

UTIL_SRC = $(wildcard src/util/*.c)
UTIL_OBJ = $(UTIL_SRC:src/%.c=build/%.o)
build/util/ : | build/
	mkdir $@
build/util/%.o : src/util/%.c | build/util/
	$(CC_COMPILE_OBJECT) $^ -o $@

TESTS := $(shell find test/ | grep \.test\.c)

OBJ := $(CONFIG_OBJ) $(RVAL_OBJ) $(RLEX_OBJ) $(UTIL_OBJ)

entry:
	@echo $(RVAL)
	@echo $(UTIL)

rill : CC_FLAGS += $(CC_FLAGS_DEVELOP)
rill : bin/rill

release : CC_FLAGS += $(CC_FLAGS_RELEASE)
release : bin/rill

bin/rill : $(OBJ) src/rill/main.c | bin/
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
bin/rill-test : $(OBJ) $(TESTS) src/test/main.c src/test/test.c src/test/manifest.c | bin/
	$(CC_COMPILE) $^ -o $@

clean :
	rm -rf bin/
	rm -rf build/
	rm -f $(shell find build/ | grep \\.o$)
	rm -rf coverage/*
	rm -rf coverage/.profile-output
	rm -rf coverage/.gcov-output
	rm -rf coverage/.lcov-output
