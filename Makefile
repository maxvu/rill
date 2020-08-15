CC := clang
CC_FLAG = -Wall -std=c99 -I include/ -I src/

INCLUDE_DIR  := include
SRC_DIR      := src
BUILD_DIR    := build
BIN_DIR      := bin
TEST_DIR     := test
COVERAGE_DIR := coverage

ENTRYPOINTS     := $(SRC_DIR)/main.c $(SRC_DIR)/test_main.c
SOURCES         := $(filter-out $(ENTRYPOINTS), $(wildcard $(SRC_DIR)/*.c))

RELEASE_OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.release.o,$(SOURCES))
RELEASE_COMPILE_BINARY = $(CC) $(CC_FLAG) -O3
RELEASE_COMPILE_OBJECT = $(CC) $(CC_FLAG) -c -O3

DEBUG_OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.debug.o,$(SOURCES))
DEBUG_COMPILE_BINARY = $(CC) $(CC_FLAG) -O0 -g
DEBUG_COMPILE_OBJECT = $(CC) $(CC_FLAG) -c -O0 -g

TEST_OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.test.o,$(SOURCES))
TEST_SOURCES = $(TEST_DIR)/main.c $(TEST_DIR)/rill_test.c
TEST_COMPILE_BINARY = $(CC) $(CC_FLAG) -O0 -g --coverage -fprofile-arcs \
	-I $(TEST_DIR)/

.PHONY : release

$(BIN_DIR)/ :
	mkdir -p $@
$(BUILD_DIR)/ :
	mkdir -p $@

# 'release' tag, binary and objects
release : $(BIN_DIR)/rill
$(BIN_DIR)/rill : $(RELEASE_OBJECTS) $(SRC_DIR)/main.c | $(BIN_DIR)/
	$(RELEASE_COMPILE_BINARY) $^ -o $@
$(BUILD_DIR)/%.release.o : $(SRC_DIR)/%.c | $(BUILD_DIR)/
	$(RELEASE_COMPILE_OBJECT) $^ -o $@

# 'debug' tag, binary and objects
debug : $(BIN_DIR)/rill.debug
$(BIN_DIR)/rill.debug : $(DEBUG_OBJECTS) $(SRC_DIR)/main.c | $(BIN_DIR)/
	$(DEBUG_COMPILE_BINARY) $^ -o $@
$(BUILD_DIR)/%.debug.o : $(SRC_DIR)/%.c | $(BUILD_DIR)/
	$(DEBUG_COMPILE_OBJECT) $^ -o $@

# 'test' tag, binary and objects
test : $(BIN_DIR)/rill.test
$(BIN_DIR)/rill.test : $(TEST_OBJECTS) $(TEST_SOURCES) | $(BIN_DIR)/
	$(TEST_COMPILE_BINARY) $^ -o $@
$(BUILD_DIR)/%.test.o : $(SRC_DIR)/%.c | $(BUILD_DIR)/
	$(CC) $(CC_FLAG) -c -O0 -g --coverage -fprofile-arcs \
	-I $(TEST_DIR)/ \
	$^ -o $@

# Aggregate the coverage output into a single file.
$(COVERAGE_DIR)/ :
	mkdir -p $@
COVERAGE_INFO = $(BUILD_DIR)/coverage.info
$(COVERAGE_INFO) : test | $(BUILD_DIR)/
	mv ./*.gcno $(BUILD_DIR)/
	# mv ./build/*.gcno $(BUILD_DIR)/
	bin/rill.test
	mv ./*.gcda $(BUILD_DIR)/
	# mv ./build/*.gcda $(BUILD_DIR)/
	llvm-cov gcov $(BUILD_DIR)/*.gcno $(BUILD_DIR)/*.gdca
	mv ./*.gcov $(BUILD_DIR)/
	lcov --directory build/ --capture -o $@ \
		--gcov-tool $(realpath ./test/llvm-gcov.sh)

coverage-info : $(COVERAGE_INFO)

# Turn the coverage file into a browsable, HTML index.
coverage-html : $(COVERAGE_INFO) | $(COVERAGE_DIR)
	genhtml $(COVERAGE_INFO) -o $(COVERAGE_DIR)/

# Open that browsable index in a graphical environment.
coverage-launch : coverage-html
	xdg-open $(COVERAGE_DIR)/html/index.htm

debug-makefile :
	@echo INCLUDE_DIR $(INCLUDE_DIR)
	@echo SRC_DIR $(SRC_DIR)
	@echo BUILD_DIR $(BUILD_DIR)
	@echo BIN_DIR $(BIN_DIR)
	@echo ENTRYPOINTS $(ENTRYPOINTS)
	@echo SOURCES $(SOURCES)
	@echo RELEASE_OBJECTS $(RELEASE_OBJECTS)
	@echo RELEASE_COMPILE_BINARY $(RELEASE_COMPILE_BINARY)
	@echo RELEASE_COMPILE_OBJECT $(RELEASE_COMPILE_OBJECT)
	@echo DEBUG_OBJECTS $(DEBUG_OBJECTS)
	@echo DEBUG_COMPILE_BINARY $(DEBUG_COMPILE_BINARY)
	@echo DEBUG_COMPILE_OBJECT $(DEBUG_COMPILE_OBJECT)
	@echo TEST_OBJECTS $(TEST_OBJECTS)
	@echo TEST_COMPILE_BINARY $(TEST_COMPILE_BINARY)
	@echo TEST_COMPILE_OBJECT $(TEST_COMPILE_OBJECT)

plan : $(SOURCES)
	$(CC) $(CC_FLAG) -M $^

clean :
	rm -rf $(BIN_DIR) $(BUILD_DIR) $(COVERAGE_DIR)
