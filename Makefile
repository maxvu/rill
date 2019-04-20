CC = g++
CC_FLAGS = -Wall -std=c++11
CC_FLAGS_DEVELOP = -g -O0
CC_FLAGS_RELEASE = -s -O3
CC_INCLUDE = -I include/

develop : CC_FLAGS += CC_FLAGS_DEVELOP
release : CC_FLAGS += CC_FLAGS_RELEASE

CC_COMPILE_OBJECT = $(CC) $(CC_FLAGS) -c

bin/ :
	mkdir $@
build/ :
	mkdir $@

STRUCTURES_SRC = $(shell find ./src/Structures | grep \\.cpp)
STRUCTURES_OBJ = $(STRUCTURES_SRC:./src/Structures/%.cpp=./build/Structures/%.o)
build/Structures/ : | build/
	mkdir $@
build/Structures/%.o : src/Structures/%.cpp | build/Structures/
	$(CC_COMPILE_OBJECT) $< -o $@

VAL_SRC = $(shell find ./src/Val | grep \\.cpp)
VAL_OBJ = $(STRUCTURES_SRC:./src/Val/%.cpp=./build/Val/%.o)
build/Val/ : | build/
	mkdir $@
build/Val/%.o : src/Val/%.cpp | build/Val/
	$(CC_COMPILE_OBJECT) $< -o $@

OBJ_ALL = $(STRUCTURES_OBJ) \
	$(VAL_OBJ)

bin/rill : $(OBJ_ALL) src/Rill/Main.cpp | bin/
	$(CC) $(CC_INCLUDE) $(CC_FLAGS) $^ -o $@

debug :
	@echo "$(SRC)"
	@echo "$(OBJ)"

clean:
	rm -rf bin/
	rm -rf build/
