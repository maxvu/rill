CC := clang
CC_FLAGS := -Wall -g
CC_INCLUDE := -I ./include

bin/ :
	mkdir -p $@
build/ :
	mkdir -p $@

build/rval/ : build/
	mkdir -p $@
build/rval/%.o : src/rval/%.c include/rval/%.h build/rval/
	$(CC) $(CC_INCLUDE) $(CC_FLAGS) -o $@ $<
rval : build/rval/rbuf.o \
       build/rval/rctx.o \
       build/rval/rfxx.o \
       build/rval/ruxx.o \
       build/rval/rixx.o \
       build/rval/rmap.o \
       build/rval/rval.o \
       build/rval/rvec.o
