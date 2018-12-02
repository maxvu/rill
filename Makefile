CC := gcc

CC_FLAGS := -Wall -std=c11
CC_FLAGS_DEBUG := -Og -g
CC_FLAGS_RELEASE := -O3 -s
CC_INCLUDE := -I include/

CC_COMPUNIT := $(CC) $(CC_FLAGS) $(CC_INCLUDE) $(CC_FLAGS_DEBUG) -c

OBJ_ALL = $(OBJ_RVAL)

OBJ_RVAL = build/rval/rmap.o \
	build/rval/rvec.o build/rval/rbuf.o build/rval/rref.o
rval : $(OBJ_RVAL)
build/rval/rref.o : src/rval/rbuf.c include/rval/rref.h
	$(CC_COMPUNIT) $< -o $@
build/rval/rbuf.o : src/rval/rbuf.c include/rval/rbuf.h
	$(CC_COMPUNIT) $< -o $@
build/rval/rvec.o : src/rval/rvec.c include/rval/rvec.h
	$(CC_COMPUNIT) $< -o $@
build/rval/rmap.o : src/rval/rmap.c include/rval/rmap.h
	$(CC_COMPUNIT) $< -o $@

bin/rill-test : CC_FLAGS += $(CC_FLAGS_DEBUG)
bin/rill-test : $(OBJ_ALL) test/main.c
	$(CC) $(CC_FLAGS) $(OBJ_ALL) test/main.c -o $@

bin/rill-test+coverage: CC_FLAGS += --coverage -fprofile-dir="test/coverage/" \
		-fprofile-generate="test/coverage/"
bin/rill-test+coverage: $(OBJ_ALL) test/main.c
	$(CC) $(CC_FLAGS) $(OBJ_ALL) test/main.c -o $@
	mv *.gcno test/coverage/

test-coverage: test/coverage/.lcov-output
	cd test/coverage/ && genhtml coverage.info --output-directory html
test/coverage/.lcov-output : test/coverage/.gcov-output
	lcov --capture --directory ./ --output-file test/coverage/coverage.info
	touch $<

test/coverage/.gcov-output : test/coverage/.profile-output
	gcov --object-directory test/coverage/ test/coverage/*.gcno
	touch $@

test/coverage/.profile-output : bin/rill-test+coverage
	cd test/coverage && GCOV_PREFIX_STRIP=99 ../../bin/rill-test+coverage
	touch $@

clean:
	rm -f $(shell find build/ | grep "\.o")
	rm -f bin/*
	rm -rf test/coverage/*
	rm -rf test/coverage/.profile-output
	rm -rf test/coverage/.gcov-output
	rm -rf test/coverage/.lcov-output
