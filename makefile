CC=g++
FLAGS=-Wall -Werror -pedantic -O3 -save-temps -std=c++20
FLAGS+=-DNDEBUG
LIBS=-I.

SRCS=$(wildcard *.cpp)
EXECS=$(SRCS:.cpp=.exe)
RUNS=$(SRCS:.cpp=.run)

TEMPS= *.s *.i *.ii *.o *.tks *.report *.ast *.exe

all: $(EXECS) $(RUNS)

remake: clean all

%.o: %.cpp 
	${CC} -o $@ -c $< ${FLAGS} ${LIBS}

%.exe: %.o
	${CC} -o $@ $< ${FLAGS} ${LIBS}

%.run: %.exe
	./$< > $@ 
	cat $@

clean: 
	rm -f  ${TEMPS}

.PHONY: remake clean all
