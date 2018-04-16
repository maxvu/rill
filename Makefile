CC = clang
CC_FLAGS = -Wall -g -std=c11
CC_INCLUDE = -I include/ -I lib/

ENTRY   = src/main.c
SOURCES = $(filter-out $(ENTRY), $(shell find src/*.c))
OBJECTS = $(patsubst src/%.c, build/%.o, $(SOURCES))
TESTS   = $(shell find test/*.c)

bin/rill : $(OBJECTS) $(ENTRY)
	$(CC) $(CC_INCLUDE) $(ENTRY) $(CC_FLAGS) $(OBJECTS) -o $@

bin/rill-tests : $(OBJECTS) $(TESTS)
	$(CC) $(CC_INCLUDE) -I test/ $(CC_FLAGS) $(OBJECTS) $(TESTS) -o $@

build/main.o : $(ENTRY)
	$(CC) $(CC_INCLUDE) $(CC_FLAGS) -c $< -o $@

build/%.o : src/%.c include/%.h
	$(CC) $(CC_INCLUDE) $(CC_FLAGS) -c $< -o $@

tests : bin/rill-tests
test  : tests

clean :
	rm -rf bin/*
	rm -rf build/*

dbg :
	@echo SOURCES: $(SOURCES)
	@echo OBJECTS: $(OBJECTS)
