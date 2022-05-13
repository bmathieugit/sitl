CCFLAGS=-O3 -std=c++20 -save-temps
CCINCLUDES=-Ilibs

all: ares test sitl

objects:
	mkdir -p objects

objects/algorithm.test.exe: tests/algorithm.test.cpp
	g++ -o objects/algorithm.test.exe tests/algorithm.test.cpp ${CCINCLUDES} ${CCFLAGS}

objects/array.test.exe: tests/array.test.cpp
	g++ -o objects/array.test.exe tests/array.test.cpp ${CCINCLUDES} ${CCFLAGS}

objects/vector.test.exe: tests/vector.test.cpp
	g++ -o objects/vector.test.exe tests/vector.test.cpp ${CCINCLUDES} ${CCFLAGS}

objects/string.test.exe: tests/string.test.cpp
	g++ -o objects/string.test.exe tests/string.test.cpp ${CCINCLUDES} ${CCFLAGS}

objects/iostream.test.exe: tests/iostream.test.cpp
	g++ -o objects/iostream.test.exe tests/iostream.test.cpp ${CCINCLUDES} ${CCFLAGS}
	
objects/list.test.exe: tests/list.test.cpp
	g++ -o objects/list.test.exe tests/list.test.cpp ${CCINCLUDES} ${CCFLAGS}

objects/set.test.exe: tests/set.test.cpp
	g++ -o objects/set.test.exe tests/set.test.cpp ${CCINCLUDES} ${CCFLAGS}

objects/strong.test.exe: tests/strong.test.cpp
	g++ -o objects/strong.test.exe tests/strong.test.cpp ${CCINCLUDES} ${CCFLAGS}

test: objects objects/algorithm.test.exe objects/strong.test.exe objects/array.test.exe objects/vector.test.exe objects/string.test.exe objects/iostream.test.exe objects/list.test.exe objects/set.test.exe
	wc -l objects/*.test.s
	./objects/algorithm.test.exe 
	./objects/strong.test.exe
	./objects/array.test.exe
	./objects/vector.test.exe
	./objects/string.test.exe
	./objects/iostream.test.exe
	./objects/list.test.exe
	./objects/set.test.exe

objects/ares.exe: sources/ares.cpp
	g++ -o objects/ares.exe sources/ares.cpp ${CCINCLUDES} ${CCFLAGS}

ares: objects objects/ares.exe
	wc -l objects/ares.s
	./objects/ares.exe

objects/sitl.exe: sources/sitl.cpp
	g++ -o objects/sitl.exe sources/sitl.cpp ${CCINCLUDES} ${CCFLAGS}

sitl: objects objects/sitl.exe
	wc -l objects/sitl.s
	./objects/sitl.exe --file=toto.sitl

clean:
	rm -rf objects
