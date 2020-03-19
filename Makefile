CC = clang
CC_FLAG = -Wall -std=c++17
CC_INC = -I include/ -I src/

default:
	$(CC) $(CC_FLAG) $(CC_INC) src/*.cpp  -o ./test

small:
	$(CC) $(CC_FLAG) $(CC_INC) src/*.cpp  -DRILL_32BIT -m32 -o ./test
