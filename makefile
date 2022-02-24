CC=g++
FLAGS=-Wall -Werror -pedantic -O3  -std=c++20
FLAGS+= -save-temps
LIBS=-I.

EXEC=sitl.exe
RUN=$(EXEC).run

SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
ASMS=$(SRCS:.cpp=.s)

TEMPS=*.s *.i *.ii *.o *.tks *.report *.ast *.exe

all: $(EXEC)  measure run

remake: clean all

%.o: %.cpp 
	${CC} -o $@ -c $< ${FLAGS} ${LIBS}

$(EXEC): $(OBJS)
	${CC} -o $@ $^ ${FLAGS} ${LIBS}

run: $(EXEC)
	./$< --file=toto.sitl ldla qlkd  qzd  lqk zd: lqkz d

measure: $(ASMS)
	wc -l $^

clean: 
	rm -f  ${TEMPS}

.PHONY: remake clean all measure
