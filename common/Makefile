CC     = clang
CFLAGS = -Wall -std=c++17 -I include/ -I ../include/
CC_BIN = $(CC) $(CFLAGS)
CC_OBJ = $(CC) $(CFLAGS) -c

common : $(patsubst src/%.cpp, build/%.o, $(wildcard src/*.cpp))

build/ :
	mkdir $@

build/%.o : src/%.cpp | build/
	$(CC_OBJ) $^ -o $@
