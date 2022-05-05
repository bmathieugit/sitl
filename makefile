CCFLAGS=-O3 -std=c++20 -save-temps
CCINCLUDES=-Ilibs

all: test

objects:
	mkdir -p objects

objects/algorithm.test.exe: tests/algorithm.test.cpp
	g++ -o objects/algorithm.test.exe tests/algorithm.test.cpp ${CCINCLUDES} ${CCFLAGS}

objects/array.test.exe: tests/array.test.cpp
	g++ -o objects/array.test.exe tests/array.test.cpp ${CCINCLUDES} ${CCFLAGS}

objects/vector.test.exe: tests/vector.test.cpp
	g++ -o objects/vector.test.exe tests/vector.test.cpp ${CCINCLUDES} ${CCFLAGS}

objects/fixed_vector.test.exe: tests/fixed_vector.test.cpp
	g++ -o objects/fixed_vector.test.exe tests/fixed_vector.test.cpp ${CCINCLUDES} ${CCFLAGS}

objects/string.test.exe: tests/string.test.cpp
	g++ -o objects/string.test.exe tests/string.test.cpp ${CCINCLUDES} ${CCFLAGS}

objects/format.test.exe: tests/format.test.cpp
	g++ -o objects/format.test.exe tests/format.test.cpp ${CCINCLUDES} ${CCFLAGS}
	
objects/list.test.exe: tests/list.test.cpp
	g++ -o objects/list.test.exe tests/list.test.cpp ${CCINCLUDES} ${CCFLAGS}

objects/set.test.exe: tests/set.test.cpp
	g++ -o objects/set.test.exe tests/set.test.cpp ${CCINCLUDES} ${CCFLAGS}

objects/strong.test.exe: tests/strong.test.cpp
	g++ -o objects/strong.test.exe tests/strong.test.cpp ${CCINCLUDES} ${CCFLAGS}

test: objects objects/algorithm.test.exe objects/strong.test.exe objects/array.test.exe objects/vector.test.exe objects/fixed_vector.test.exe objects/string.test.exe objects/format.test.exe objects/list.test.exe objects/set.test.exe
	wc -l objects/*.s
	./objects/algorithm.test.exe 
	./objects/strong.test.exe
	./objects/array.test.exe
	./objects/vector.test.exe
	./objects/fixed_vector.test.exe
	./objects/string.test.exe
	./objects/format.test.exe
	./objects/list.test.exe
	./objects/set.test.exe

clean:
	rm -rf objects
