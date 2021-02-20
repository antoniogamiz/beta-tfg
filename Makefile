all:
	mkdir -p bin/
	rm -rf progress
	g++ -g -std=c++2a -Wall -Isrc/include -o bin/color.exe  src/main.cc -lpthread
	chmod a+x bin/color.exe
	mkdir -p progress
	bin/color.exe > test.ppm
	pnmtopng test.ppm > result.png
	rm -rf progress