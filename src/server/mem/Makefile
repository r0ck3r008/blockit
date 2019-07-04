COMPILER := gcc
COMPILER_FLAGS := -g -c
ALL_OBJS := mem_mgr.o h_map.o

all: ${ALL_OBJS}

mem_mgr.o: mem_mgr.c mem_mgr.h
	${COMPILER} ${COMPILER_FLAGS} mem_mgr.c

h_map.o: h_map.c h_map.h
	${COMPILER} ${COMPILER_FLAGS} h_map.c

clean:
	rm ${ALL_OBJS}
