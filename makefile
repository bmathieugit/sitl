CC=g++
FLAGS=-Wall -Werror -pedantic -O3 -save-temps -std=c++20
FLAGS+=-DNDEBUG
LIBS=-I.

SRCS=$(wildcard *.cpp)
EXECS=$(SRCS:.cpp=.exe)
RUNS=$(SRCS:.cpp=.run)
ASMS=$(SRCS:.cpp=.s)

TEMPS=*.s *.i *.ii *.o *.tks *.report *.ast *.exe *.run

all: $(EXECS) $(RUNS) measure

remake: clean all

%.o: %.cpp 
	${CC} -o $@ -c $< ${FLAGS} ${LIBS}

%.exe: %.o
	${CC} -o $@ $< ${FLAGS} ${LIBS}

%.run: %.exe
	./$< > $@ --file ldla qlkd  qzd  lqk zd: lqkz d
	cat $@

measure: $(ASMS)
	wc -l $^


clean: 
	rm -f  ${TEMPS}

.PHONY: remake clean all measure
