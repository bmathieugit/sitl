# $@ : nom de la cible
# $< : nom de la première dépendance
# $ˆ : liste des dépendances
# $? : liste des dépendances plus récentes que la cible
# $* : nom d’un fichier sans son suffixe

CCFLAGS=-O3 -std=c++2a -save-temps  -fconcepts-diagnostics-depth=10
CCINCLUDES=-Isources

all: test sitl base16 dist

objects:
	mkdir -p objects

objects/algorithm.test.exe: tests/algorithm.test.cpp
	g++ -o $@ tests/algorithm.test.cpp ${CCINCLUDES} ${CCFLAGS}
	./$@

objects/array.test.exe: tests/array.test.cpp
	g++ -o $@ $^ ${CCINCLUDES} ${CCFLAGS}
	./$@

objects/vector.test.exe: tests/vector.test.cpp
	g++ -o $@ $^ ${CCINCLUDES} ${CCFLAGS}
	./$@

objects/string.test.exe: tests/string.test.cpp
	g++ -o $@ $^ ${CCINCLUDES} ${CCFLAGS}
	./$@

objects/iostream.test.exe: tests/iostream.test.cpp
	g++ -o $@ $^ ${CCINCLUDES} ${CCFLAGS}
	./$@
	
objects/list.test.exe: tests/list.test.cpp
	g++ -o $@ $^ ${CCINCLUDES} ${CCFLAGS}
	./$@

objects/set.test.exe: tests/set.test.cpp
	g++ -o $@ $^ ${CCINCLUDES} ${CCFLAGS}
	./$@

objects/strong.test.exe: tests/strong.test.cpp
	g++ -o $@ $^ ${CCINCLUDES} ${CCFLAGS}
	./$@

objects/args.test.exe: tests/args.test.cpp sources/lib/args.cpp
	g++ -o $@ $^ ${CCINCLUDES} ${CCFLAGS}
	./$@

test: objects objects/algorithm.test.exe objects/strong.test.exe \
			objects/array.test.exe objects/vector.test.exe objects/string.test.exe \
			objects/iostream.test.exe objects/list.test.exe objects/set.test.exe \
			objects/args.test.exe
	wc -l objects/*test*.s

objects/sitl.exe: sources/sitl.cpp \
									sources/lib/args.cpp
	g++ -o $@ $^ ${CCINCLUDES} ${CCFLAGS}

sitl: objects objects/sitl.exe
	wc -l objects/sitl*.s
	./objects/sitl.exe --file=toto.sitl

objects/base16.exe: sources/base16.cpp sources/lib/args.cpp
	g++ -o $@ $^ ${CCINCLUDES} ${CCFLAGS}

base16: objects objects/base16.exe
	wc -l objects/base16*.s
	./objects/base16.exe prout


dist: test objects/sitl.exe objects/base16.exe
	mkdir -p dist
	cp objects/sitl.exe dist/sitl.exe
	cp objects/base16.exe dist/base16.exe

clean:
	rm -rf objects dist

.PHONY: clean sitl all test base16