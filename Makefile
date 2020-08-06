all:
	g++ -std=c++11 -Wall -Isrc/include -o bin/color.exe  src/main.cc -lpthread
	chmod a+x bin/color.exe
	bin/color.exe > test.ppm