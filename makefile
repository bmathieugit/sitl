CC=g++
FLAGS=-Wall -Werror -pedantic -O3  -std=c++20
FLAGS+= -save-temps
LIBS=-I.

EXEC=sitl.exe
RUN=$(EXEC).run

SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
ASMS=$(SRCS:.cpp=.s)

TEMPS=*.s *.i *.ii *.o *.tks *.report *.ast *.exe *.run

all: $(EXEC)  measure $(RUN)

remake: clean all

%.o: %.cpp 
	${CC} -o $@ -c $< ${FLAGS} ${LIBS}

$(EXEC): $(OBJS)
	${CC} -o $@ $^ ${FLAGS} ${LIBS}

$(EXEC).run: $(EXEC)
	./$< > $@ --file=toto.sitl ldla qlkd  qzd  lqk zd: lqkz d
	cat $@

measure: $(ASMS)
	wc -l $^

clean: 
	rm -f  ${TEMPS}

.PHONY: remake clean all measure
