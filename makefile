CC=gcc
FLAGS=-Wall -Werror -pedantic -O3 -save-temps
FLAGS+=-DNDEBUG
LIBS=-I.

SRCS=$(wildcard *.c)
OBJECTS=$(SRCS:.c=.o)
ASMS=$(SRCS:.c=.s)
TEMPS= *.s *.i *.ii *.o *.tks *.report *.ast

EXEC=sitl.exe

all: exec asms run
remake: clean all

%.o: %.c
	${CC} -o $@ -c $< ${FLAGS} ${LIBS}

${EXEC}: ${OBJECTS}
	${CC} -o $@ $^ ${FLAGS} ${LIBS} 

exec: ${EXEC}

asms: ${EXEC} 
	wc -l ${ASMS}

run: exec
	./${EXEC} --file=toto.sitl

clean: 
	rm -f  ${TEMPS} ${EXEC} 

.PHONY: remake clean exec asms run
