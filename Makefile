CC := g++

CC_INCLUDE := $(COMMON_INC)

CC_FLAGS = -Wall -std=c++17 $(CC_INCLUDE)
CC_FLAGS_DEVELOP  := -O0 -g
CC_FLAGS_RELEASE  := -O3 -DNDEBUG -s
CC_FLAGS_COVERAGE := --coverage -fprofile-dir="coverage/" \
		-fprofile-generate="coverage/"

CC_COMPILE = $(CC) $(CC_INCLUDE) $(CC_FLAGS)
CC_COMPILE_OBJECT = $(CC) $(CC_INCLUDE) -c $(CC_FLAGS)

bin/ :
	mkdir $@
build/ :
	mkdir $@

COMMON_SRC = $(wildcard Common/src/*.cpp)
COMMON_OBJ = $(COMMON_SRC:Common/src/%.cpp=Common/build/%.o)
COMMON_INC := Common/include/
Common/build/ :
	mkdir $@
Common/build/%.o : Common/build/
Common/build/%.o : Common/src/%.cpp
	$(CC_COMPILE_OBJECT) -I $(COMMON_INC) $< -o $@
Common : $(COMMON_OBJ)

clean :
	rm -rf Common/build/
