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

bin/rill : src/main.c $(RVAL)
	$(CC) $(CC_INCLUDE) $(CC_FLAGS) -o $@ src/main.c $(RVAL)

# "release" with NDEBUG

clean :
	rm -rf build/*
	rm -rf bin/*
