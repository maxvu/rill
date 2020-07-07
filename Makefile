SOURCE_DIR  = src
BUILD_DIR   = build
INCLUDE_DIR = include
BIN_DIR     = bin
ENTRY_CPP   = $(SOURCE_DIR)/main.cpp

CC          = g++
CC_FLAG     = -Wall -std=c++17 -I $(INCLUDE_DIR)/
CC_FLAG_BIN = $(CC_FLAG)
CC_FLAG_OBJ = $(CC_FLAG)

HEADERS     = $(wildcard $(INCLUDE)/*.hpp)
SOURCES     = $(wildcard $(SOURCE_DIR)/*.cpp)
OBJECTS     = $(patsubst $(SOURCE_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

COMPILE_OBJECT = $(CC) $(CC_FLAG_OBJ) -c $^ -o $@
COMPILE_BINARY = $(CC) $(CC_FLAG_BIN) $(OBJECTS) -o $@

all : bin/rill

release : CC_FLAG += -s -O3
release : all

debug : CC_FLAG += -g
debug : all

coverage : CC_FLAG += -fprofile-arcs -ftest-coverage
coverage : all

bin/rill : obj | bin/
	$(COMPILE_BINARY)

obj : $(OBJECTS)

clean :
	rm -rf $(BIN_DIR)/ $(BUILD_DIR)/

debug-makefile :
	@echo compile object $(COMPILE_OBJECT)

$(BUILD_DIR)/%.o : $(SOURCE_DIR)/%.cpp | build/
	$(COMPILE_OBJECT)

$(BUILD_DIR)/ :
	mkdir -p $@

$(BIN_DIR)/ :
	mkdir -p $@
