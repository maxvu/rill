CC = clang
CC_FLAGS = -Wall -std=c11 -g
LD_FLAGS = -s
CC_INCLUDE = -I include/ -I lib/

build :
	mkdir -p $@

build/val : build/
	mkdir -p $@
build/val/%.c: src/val/%.h
	@echo
build/val/%.o: src/val/%.c build/ build/val
	$(CC) $(CC_FLAGS) $(CC_INCLUDE) $^ -c -o $@

build/vm : build/
	mkdir -p $@
build/vm/%.c: src/vm/%.h
	@echo
build/vm/%.o: src/vm/%.c build/ build/vm
	$(CC) $(CC_FLAGS) $(CC_INCLUDE) $^ -c -o $@
