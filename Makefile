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

.PHONY : release

$(BIN_DIR)/ :
	mkdir -p $@
$(BUILD_DIR)/ :
	mkdir -p $@

# 'release' tag, binary and objects
release : $(BIN_DIR)/rill
RELEASE_OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.release.o,$(SOURCES))
$(BIN_DIR)/rill : $(RELEASE_OBJECTS) $(SRC_DIR)/main.c | $(BIN_DIR)/
	$(CC) $(CC_FLAG) -O3 $^ -o $@
$(BUILD_DIR)/%.release.o : $(SRC_DIR)/%.c | $(BUILD_DIR)/
	$(CC) $(CC_FLAG) -c -O3 $^ -o $@

# 'debug' tag, binary and objects
debug : $(BIN_DIR)/rill.debug
DEBUG_OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.debug.o,$(SOURCES))
$(BIN_DIR)/rill.debug : $(DEBUG_OBJECTS) $(SRC_DIR)/main.c | $(BIN_DIR)/
	$(CC) $(CC_FLAG) -O0 -g $^ -o $@
$(BUILD_DIR)/%.debug.o : $(SRC_DIR)/%.c | $(BUILD_DIR)/
	$(CC) $(CC_FLAG) -c -O0 -g $^ -o $@

# 'test' tag, binary and objects
test : $(BIN_DIR)/rill.test
TEST_OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.test.o,$(SOURCES))
TEST_SOURCES = $(TEST_DIR)/main.c $(TEST_DIR)/rill_test.c
$(BIN_DIR)/rill.test : $(TEST_OBJECTS) $(TEST_SOURCES) | $(BIN_DIR)/
	$(CC) $(CC_FLAG) -O0 -g -I $(TEST_DIR)/ $^ -o $@
$(BUILD_DIR)/%.test.o : $(SRC_DIR)/%.c | $(BUILD_DIR)/
	$(CC) $(CC_FLAG) -c -O0 -g -I $(TEST_DIR)/ $^ -o $@

# 'test-coverage' tag -- test, but with profiling and coverage options
test-coverage : $(COVERAGE_DIR)/index.htm
COVERAGE_OBJECTS = \
	$(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.test-coverage.o,$(SOURCES))
$(BIN_DIR)/rill.test-coverage : $(COVERAGE_OBJECTS) $(TEST_SOURCES) | $(BIN_DIR)/
	$(CC) $(CC_FLAG) $^ -o $@ -O0 -g --coverage -fprofile-arcs
$(BUILD_DIR)/%.test-coverage.o : $(SRC_DIR)/%.c | $(BUILD_DIR)/
	$(CC) $(CC_FLAG) -c -O0 -g --coverage -fprofile-arcs -I $(TEST_DIR)/ \
	$^ -o $@
$(COVERAGE_DIR)/ :
	mkdir -p $@
COVERAGE_INFO = $(BUILD_DIR)/coverage.info
$(COVERAGE_INFO) : $(BIN_DIR)/rill.test-coverage | $(BUILD_DIR)/
	mv ./*.gcno $(BUILD_DIR)/
	bin/rill.test-coverage
	mv ./*.gcda $(BUILD_DIR)/
	llvm-cov gcov $(BUILD_DIR)/*.gcno $(BUILD_DIR)/*.gdca
	mv ./*.gcov $(BUILD_DIR)/
	lcov --directory build/ --capture -o $@ \
		--gcov-tool $(realpath ./test/llvm-gcov.sh)
$(COVERAGE_DIR)/index.htm : $(COVERAGE_INFO) | $(COVERAGE_DIR)/
	genhtml $(COVERAGE_INFO) -o $(COVERAGE_DIR)/

plan : $(SOURCES)
	$(CC) $(CC_FLAG) -M $^

clean :
	rm -rf $(BIN_DIR) $(BUILD_DIR) $(COVERAGE_DIR)
