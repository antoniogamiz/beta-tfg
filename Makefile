all:
	g++ -Wall -Isrc/include -o bin/color.exe  src/main.cc
	chmod a+x bin/color.exe
	bin/color.exe > test.ppm