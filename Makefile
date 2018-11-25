CC := gcc
CC_FLAGS := -g -Wall -std=c11 -DRILL_WORDSIZE=64
CC_INCLUDE := -I include/

RILL_MAIN := src/main.c
SOURCES = $(filter-out $(RILL_MAIN), $(wildcard src/*.c))
OBJECTS = $(patsubst src/%.c, build/%.o, $(SOURCES))
TESTS = $(wildcard ./test/*.test.c)

bin/rill : $(OBJECTS) $(RILL_MAIN)
	$(CC) $(CC_FLAGS) $(CC_INCLUDE) -o $@ $(SOURCES) $(RILL_MAIN)

bin/rill-tests : $(OBJECTS) $(TESTS)
	$(CC) $(CC_FLAGS) $(CC_INCLUDE) -I test/ -o $@ \
	$(OBJECTS) $(TESTS) test/main.c

bin/rill-tests+coverage : $(SOURCES) $(TESTS)
	$(CC) $(CC_FLAGS) $(CC_INCLUDE) -I test/ -o $@ \
	-O0 -ftest-coverage -fprofile-arcs -fprofile-dir=coverage/ \
	$(SOURCES) $(TESTS) test/main.c

COVERAGE := $(patsubst src/%.c, coverage/%.c.gcov, $(SOURCES))
$(COVERAGE) : $(SOURCES) coverage/ bin/rill-tests+coverage
	mv *.gcno coverage/
	bin/rill-tests+coverage
	gcov --object-directory coverage/ coverage/*.gcno
	mv *.gcov coverage/
	cd coverage/ ; lcov --capture --directory ./ --output-file coverage.info
	cd coverage/ ; genhtml coverage.info --output-directory html

test : bin/rill-tests
tests : bin/rill-tests
test-coverage: $(COVERAGE)

bin/ :
	mkdir -p $@
build/ :
	mkdir -p $@
coverage/ :
	mkdir -p $@

build/%.o : src/%.c
	$(CC) $(CC_FLAGS) $(CC_INCLUDE) -c $< -o $@

clean :
	rm -f bin/*
	rm -f build/*
	rm -f coverage/*
	rm -f *.gcno
	rm -f *.gcda
