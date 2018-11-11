CC := clang
CC_FLAGS := -g -Wall
CC_INCLUDE := -I include/

RILL_MAIN := src/main.c
SOURCES = $(filter-out $(RILL_MAIN), $(wildcard src/*.c))
OBJECTS = $(patsubst src/%.c, build/%.o, $(SOURCES))

bin/rill : bin/ $(OBJECTS) $(RILL_MAIN)
	$(CC) $(CC_FLAGS) $(CC_INCLUDE) -o $@ $(SOURCES) $(RILL_MAIN)

bin/ :
	mkdir -p $@
build/ :
	mkdir -p $@

build/%.o : src/%.c build/
	$(CC) $(CC_FLAGS) $(CC_INCLUDE) -c $< -o $@

clean :
	rm -rf bin/
	rm -rf build/
