COMPILER := gcc
COMPILER_FLAGS := -g -c
ALL_OBJS := main.o mem_mgr.o utils.o

all: ${ALL_OBJS}

main.o: main.c
	${COMPILER} ${COMPILER_FLAGS} main.c

mem_mgr.o: mem_mgr.c mem_mgr.h
	${COMPILER} ${COMPILER_FLAGS} mem_mgr.c

utils.o: utils.c utils.h
	${COMPILER} ${COMPILER_FLAGS} utils.c

clean:
	rm ${ALL_OBJS}
