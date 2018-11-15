CC := g++
CC_FLAGS := -g -Wall
CC_INCLUDE := -I include/

RILL_MAIN := src/main.c
SOURCES = $(filter-out $(RILL_MAIN), $(wildcard src/*.c))
OBJECTS = $(patsubst src/%.c, build/%.o, $(SOURCES))
TESTS = $(wildcard ./test/*.test.c)

bin/rill : bin/ $(OBJECTS) $(RILL_MAIN)
	$(CC) $(CC_FLAGS) $(CC_INCLUDE) -o $@ $(SOURCES) $(RILL_MAIN)

bin/rill-tests : bin/ $(SOURCES) $(TESTS)
	$(CC) $(CC_FLAGS) $(CC_INCLUDE) -I test/ -o $@ \
	-fprofile-arcs -ftest-coverage \
	$(SOURCES) $(TESTS) test/main.c

coverage : coverage/ bin/rill-tests
	gcov *.gcno
	rm -f *.gcno
	rm -f *.gcda
	mv *.gcov coverage/

test : bin/rill-tests
tests : bin/rill-tests

bin/ :
	mkdir -p $@
build/ :
	mkdir -p $@
coverage/ :
	mkdir -p $@

build/%.o : src/%.c build/
	$(CC) $(CC_FLAGS) $(CC_INCLUDE) -c $< -o $@

clean :
	rm -rf bin/
	rm -rf build/
	rm -rf coverage/
	rm *.gcno
	rm *.gcda
