CC     = clang
CFLAGS = -Wall -std=c11 -I include/ -I ../common/include/
CC_BIN = $(CC) $(CFLAGS)
CC_OBJ = $(CC) $(CFLAGS) -c

SOURCES = $(wildcard src/*.c)
OBJECTS = $(patsubst src/%.c,build/%.o,$(SOURCES))

release : CFLAGS += -O3
release : all
all : $(OBJECTS)
test : bin/test

build/ :
	mkdir $@
bin/ :
	mkdir $@

bin/test : $(OBJECTS) test/main.c | bin/
	$(CC_BIN) -o $@ $^

build/%.o : src/%.c include/%.h | build/
	$(CC_OBJ) $< -o $@

clean :
	rm -rf build/ bin/

.PHONY : clean release
