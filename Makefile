CC = clang
CC_FLAGS = -Wall -Wextra -O3 -std=c++11 -lstdc++
CC_INCLUDE = -I include/
SRC_DIR = src/
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

bin/ :
	mkdir $@
test : bin/rill-test
bin/rill-test : test/main.cpp build/vector.o | bin/
	$(CC) $(CC_INCLUDE) $(CC_FLAGS) test/main.cpp build/vector.o -o $@

build/ :
	mkdir $@
build/%.o : src/%.cpp include/%.hpp | build/
	$(CC) $(CC_INCLUDE) $(CC_FLAGS) -c -o $@ $<

clean :
	rm -rf bin/ build/
