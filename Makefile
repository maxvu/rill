CC = g++
CC_FLAGS = -Wall -std=c++11
CC_FLAGS_DEVELOP = -g -O0
CC_FLAGS_RELEASE = -s -O3
CC_INCLUDE = -I include/

bin/ :
	mkdir $@
build/ :
	mkdir $@
build/%.o : src/%.cpp | build/
	$(CC) $(CC_FLAGS) $(CC_INCLUDE) -c $< -o $@

SRC = $(shell find ./src/ | grep \\.cpp)
OBJ = $(SRC:./src/%.cpp=./build/%.o)

bin/rill : $(OBJ) Main.cpp | bin/
	$(CC) $(CC_INCLUDE) $(CC_FLAGS) $^ -o $@

debug :
	@echo "$(SRC)"
	@echo "$(OBJ)"

clean:
	rm -rf bin/
	rm -rf build/
