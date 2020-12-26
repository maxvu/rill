CC      = clang
CC_FLAG = -Wall
CC_INC  = -I include/

bin/ :
	mkdir -p $@
build/ :
	mkdir -p $@

SOURCES = $(wildcard src/*.c)

build/%.o : src/%.c | build/
	$(CC) $(CC_FLAG) $(CC_INC) $^ -c -o $@ -O3 -s
build/%.debug.o : src/%.c | build/
	$(CC) $(CC_FLAG) $(CC_INC) $^ -c -o $@ -O3 -g
build/%.cover.o : src/%.c | build/
	$(CC) $(CC_FLAG) $(CC_INC) $^ -c -o $@ -O0 -fprofile-arcs -ftest-coverage -g

bin/rill : $(patsubst src/%.c,build/%.o,$(SOURCES)) | bin/
	$(CC) $(CC_FLAG) $(CC_INC) $^ -o $@
bin/rill.debug : $(patsubst src/%.c,build/%.debug.o,$(SOURCES)) | bin/
	$(CC) $(CC_FLAG) $(CC_INC) $^ -o $@ -g
bin/rill.test : CC_FLAG += -DRILL_RUN_TESTS
bin/rill.test : $(patsubst src/%.c,build/%.debug.o,$(SOURCES)) | bin/
	$(CC) $(CC_FLAG) $(CC_INC) $^ -o $@ -g
bin/rill.cover : CC_FLAG += -DRILL_RUN_TESTS
bin/rill.cover : $(patsubst src/%.c,build/%.cover.o,$(SOURCES)) | bin/
	$(CC) $(CC_FLAG) $(CC_INC) $^ -o $@ -O0 -fprofile-arcs -ftest-coverage -g

test/manifest.c : $(wildcard test/*.test.c)
	test/generate-manifest.sh > $@

build/test.o       : | test/manifest.c
build/test.debug.o : | test/manifest.c
build/test.test.o  : | test/manifest.c
build/test.cover.o : | test/manifest.c

release  : bin/rill
debug    : bin/rill.debug
test     : bin/rill.test
coverage : bin/rill.cover

clean:
	rm -rf bin/ build/ test/manifest.c
