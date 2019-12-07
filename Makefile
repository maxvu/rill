bin/ :
	mkdir $@

bin/oneoff : src/main.cpp | bin/
	g++ --std=c++11 -o $@ -I include/ $<
