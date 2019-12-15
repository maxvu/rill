bin/oneoff : src/main.c | bin/
	gcc -std=c11 -Wall -O0 -O -I include/ src/main.c -o bin/oneoff

bin/ :
	mkdir $@

clean :
	rm -rf bin/
