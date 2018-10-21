CC := clang
CC_FLAGS := -Wall -g
CC_INCLUDE := -I ./include

bin/ :
	mkdir -p $@
build/ :
	mkdir -p $@
build/%/ :
	mkdir -p $@

RVAL = build/rval/rval.o \
       build/rval/ruxx.o \
       build/rval/rixx.o \
       build/rval/rfxx.o \
       build/rval/rstr.o
build/rval/%.o : src/rval/%.c build/rval/
	$(CC) $(CC_INCLUDE) $(CC_FLAGS) -c -o $@ $<

RILL_ALL = $(RVAL)

bin/rill : src/main.c $(RVAL)
	$(CC) $(CC_INCLUDE) $(CC_FLAGS) -o $@ src/main.c $(RILL_ALL)

TEST_ALL := $(shell find test/ -regex .*\.test.c)
tests : bin/rill-tests
test : tests
bin/rill-tests : test/main.c $(RILL_ALL) $(TEST_ALL)
	$(CC) $(CC_INCLUDE) -I ./ $(CC_FLAGS) -o $@ $< \
	$(RILL_ALL) $(TEST_ALL)
# "release" with NDEBUG

clean :
	rm -rf build/*
	rm -rf bin/*
	rm -f test/manifest.c
	rm -f test/manifest.h
