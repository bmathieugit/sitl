CCFLAGS=-O3 -std=c++20 -save-temps
CCINCLUDES=-Ilibs

all: test

objects:
	mkdir -p objects

objects/algorithm.test.exe: tests/algorithm.test.cpp
	g++ -o objects/algorithm.test.exe tests/algorithm.test.cpp ${CCINCLUDES} ${CCFLAGS}

objects/buffer.test.exe: tests/buffer.test.cpp
	g++ -o objects/buffer.test.exe tests/buffer.test.cpp ${CCINCLUDES} ${CCFLAGS}

objects/array_view.test.exe: tests/array_view.test.cpp
	g++ -o objects/array_view.test.exe tests/array_view.test.cpp ${CCINCLUDES} ${CCFLAGS}

objects/string_view.test.exe: tests/string_view.test.cpp
	g++ -o objects/string_view.test.exe tests/string_view.test.cpp ${CCINCLUDES} ${CCFLAGS}

objects/vector.test.exe: tests/vector.test.cpp
	g++ -o objects/vector.test.exe tests/vector.test.cpp ${CCINCLUDES} ${CCFLAGS}

objects/string.test.exe: tests/string.test.cpp
	g++ -o objects/string.test.exe tests/string.test.cpp ${CCINCLUDES} ${CCFLAGS}

objects/format.test.exe: tests/format.test.cpp
	g++ -o objects/format.test.exe tests/format.test.cpp ${CCINCLUDES} ${CCFLAGS}

test: objects objects/algorithm.test.exe objects/buffer.test.exe objects/array_view.test.exe objects/string_view.test.exe objects/vector.test.exe objects/string.test.exe objects/format.test.exe
	wc -l objects/*.s
	./objects/algorithm.test.exe
	./objects/buffer.test.exe
	./objects/array_view.test.exe
	./objects/string_view.test.exe
	./objects/vector.test.exe
	./objects/string.test.exe
	./objects/format.test.exe

clean:
	rm -rf objects
