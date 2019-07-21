COMPILER := gcc
COMPILER_FLAGS := -g -c
ALL_OBJS := main.o utils.o

all: ${ALL_OBJS}

main.o: main.c
	${COMPILER} ${COMPILER_FLAGS} main.c

utils.o: utils.c utils.h
	${COMPILER} ${COMPILER_FLAGS} utils.c

clean:
	rm ${ALL_OBJS}
