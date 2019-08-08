CC = clang
CC_FLAGS = -Wall -std=c++17 -lgmp

bin/ :
	mkdir $@
build :
	mkdir $@

test : bin/rill-test
bin/rill-test : test/main.cpp $(wildcard test/units/*.cpp) | bin/
