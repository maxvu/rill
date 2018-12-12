CC := clang
CC_FLAGS := -Wall -lstdc++ -std=c++11
CC_FLAGS_DEBUG := -g -O0
CC_FLAGS_RELEASE := -s -O3
CC_INCLUDE := -I include/ -I lib/

COMPILE = $(CC) $(CC_FLAGS) $(CC_INCLUDE)

rill : CC_FLAGS += $(CC_FLAGS_DEBUG)
rill : bin/rval

bin/rval : $(OBJECTS_VAL) src/Rill/Main.cpp
	$(COMPILE) -$(OBJECTS_VAL) -o $@

SOURCES_VAL := $(shell find src/Val/ | grep \.cpp)
OBJECTS_VAL := $(patsubst src/Val/%.cpp, build/Val/%.o, $(SOURCES_VAL))
build/Val/%.o : src/Val/%.cpp include/Val/%.hpp
	$(COMPILE) -c $< -o $@

clean :
	rm -rf bin/*
	rm -rf $(shell find build/ | grep \.o)
