CC = clang
CC_FLAGS = -Wall -std=c++17
CC_INCLUDE = -I include/common/ -I include/
BUILD_OBJECT = $(CC) $(CC_FLAGS) -c

bin/ :
	mkdir $@
build/ :
	mkdir $@
build/common/ :
	mkdir $@

build/common/%.o : include/src/%.cpp include/common/%.hpp | build/common/
	$(BUILD_OBJECT) $^ -o $@
