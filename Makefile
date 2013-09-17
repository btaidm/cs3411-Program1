# Author: Tim Bradt
# Makefile for building convert
.SUFFIXES: .c .o
CC = gcc
EXEC = convert
CCFLAGS = -g -Wall -std=c99
OBJS = convert.o
INC = -I.

${EXEC}: cppcheck ${OBJS}
	${CC} ${CCFLAGS} ${INC} -lm -o ${EXEC} ${OBJS}

.c.o:
	${CC} ${CCFLAGS} ${INC} -c $<

run: ${EXEC}
	./${EXEC}
    
clean:
	rm -f ${EXEC} ${OBJS} *~ *.tgz

rebuild: clean ${EXEC}

cppcheck: 
	cppcheck .

pre: convert.c convert.h
	${CC} -E convert.c

#Makes TAR file
tar: clean ${EXEC} run
	make clean
	tar cvfz ${EXEC}.tgz *.h *.c Makefile

convert.o: convert.c convert.h
