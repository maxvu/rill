CC = clang
CC_FLAGS = -Wall -std=c11 -g
LD_FLAGS =
CC_INCLUDE = -I include/ -I lib/

build :
	mkdir -p $@

build/val/ : build/
	mkdir -p $@
build/val/rstr.o : src/val/rstr.c include/val/rstr.h build/val/
	$(CC) $(CC_FLAGS) $(CC_INCLUDE) $< -c -o $@
build/val/rvec.o : src/val/rvec.c include/val/rvec.h build/val/
	$(CC) $(CC_FLAGS) $(CC_INCLUDE) $< -c -o $@
build/val/rval.o : src/val/rval.c include/val/rval.h build/val/
	$(CC) $(CC_FLAGS) $(CC_INCLUDE) $< -c -o $@
build/val/rmap.o : src/val/rmap.c include/val/rmap.h build/val/
	$(CC) $(CC_FLAGS) $(CC_INCLUDE) $< -c -o $@
OBJ_VAL =  build/val/rstr.o
OBJ_VAL += build/val/rvec.o
OBJ_VAL += build/val/rval.o
OBJ_VAL += build/val/rmap.o

OBJECTS = $(OBJ_VAL)

# Tests
bin/rill-test : $(OBJECTS) test/*.c
	$(CC) $(LD_FLAGS) $(CC_INCLUDE) $(OBJ_ALL) $^ -o $@
test : bin/rill-test
