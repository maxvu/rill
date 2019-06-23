CC     = clang
CFLAGS = -Wall -std=c++17 -I include/common/ -I ../common/include/
CC_BIN = $(CC) $(CFLAGS)
CC_OBJ = $(CC) $(CFLAGS) -c
CC_EXT = $(CC) $(CFLAGS) -c -fPIC -shared

release : CFLAGS += -O3
release : all

all : common

rill : all
	$(CC_BIN) -o $@ $(COMMON) $(LANG) $(VM)

test : CFLAGS += -g
test : bin/test

build/ :
	mkdir $@
bin/ :
	mkdir $@

COMMON_SRC = $(wildcard src/common/*.cpp)
COMMON_OBJ = $(patsubst src/common/%.cpp,build/common/%.o,$(COMMON_SRC))
common : $(COMMON_OBJ)
build/common/ : | build/
	mkdir $@
build/common/%.o : src/common/%.cpp include/common/%.hpp | build/common/
	$(CC_OBJ) $< -o $@

VM_SRC = $(wildcard src/vm/*.cpp)
VM_OBJ = $(patsubst src/vm/%.cpp,build/vm/%.o,$(VM_SRC))
vm : $(VM_OBJ)
build/vm/ : | build/
	mkdir $@
build/vm/%.o : src/vm/%.cpp include/vm/%.hpp | build/vm/
	$(CC_OBJ) $< -o $@

LANG_SRC = $(wildcard src/lang/*.cpp)
LANG_OBJ = $(patsubst src/lang/%.cpp,build/lang/%.o,$(LANG_SRC))
lang : $(LANG_OBJ)
build/lang/ : | build/
	mkdir $@
build/lang/%.o : src/lang/%.cpp include/lang/%.hpp | build/lang/
	$(CC_OBJ) $< -o $@

bin/extensions : | bin/
	mkdir $@

EXTENSIONS = $(wildcard extensions/.)
bin/extensions/%.o : $(patsubst bin/extensions/%.o,extensions/%o/*.cpp.,$(EXTENSIONS))
	$(CC_EXT) % -I  -o $@

clean :
	rm -rf build/ bin/

.PHONY : clean release all common
