CC     = clang
CFLAGS = -Wall -std=c11 -I include/ -I ../common/include/
CC_BIN = $(CC) $(CFLAGS)
CC_OBJ = $(CC) $(CFLAGS) -c

SOURCES = $(wildcard src/*.c)
OBJECTS = $(patsubst src/%.c,build/%.o,$(SOURCES))

release : CFLAGS += -O3
release : all

all : $(OBJECTS)

test : CFLAGS += -g
test : bin/test

build/ :
	mkdir $@
bin/ :
	mkdir $@

bin/test : $(OBJECTS) test/main.c ../rtest/rtest.h $(wildcard test/*.test.inc)| bin/
	$(CC_BIN) -o $@ $(OBJECTS) -I ../ test/main.c

build/%.o : src/%.c include/%.h | build/
	$(CC_OBJ) $< -o $@

clean :
	rm -rf build/ bin/

.PHONY : clean release
