CC=g++
FLAGS=-Wall -Werror -pedantic -O3 -save-temps -std=c++20
FLAGS+=-DNDEBUG
LIBS=-I.

EXEC=sitl.exe

SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
ASMS=$(SRCS:.cpp=.s)

TEMPS=*.s *.i *.ii *.o *.tks *.report *.ast *.exe *.run

all: $(EXEC) $(RUN) measure

remake: clean all

%.o: %.cpp 
	${CC} -o $@ -c $< ${FLAGS} ${LIBS}

$(EXEC): $(OBJS)
	${CC} -o $@ $^ ${FLAGS} ${LIBS}

$(EXEC).run: $(EXEC)
	./$< > $@ --file ldla qlkd  qzd  lqk zd: lqkz d
	cat $@

measure: $(ASMS)
	wc -l $^

clean: 
	rm -f  ${TEMPS}

.PHONY: remake clean all measure
