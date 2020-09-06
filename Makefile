all:
	mkdir -p bin/
	rm -rf progress
	g++ -std=c++11 -Wall -Isrc/include -o bin/color.exe  src/main.cc -lpthread
	chmod a+x bin/color.exe
	mkdir -p progress
	bin/color.exe > test.ppm
	rm -rf progress