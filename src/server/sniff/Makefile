COMPILER := gcc
COMPILER_FLAGS := -g -c
ALL_OBJS := sniff.o

all: ${ALL_OBJS}

sniff.o: sniff.c sniff.h
	${COMPILER} ${COMPILER_FLAGS} sniff.c

clean:
	rm ${ALL_OBJS}
