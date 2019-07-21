COMPILER := gcc
LINKER_FLAGS := -lcargparse -Lcargparse/src
COMPILER_FLAGS := -g -c
ALL_OBJS := main.o mem_mgr.o uds_workings.o utils.o

all: client_bin clean_objs

client_bin: ${ALL_OBJS}
	${COMPILER} ${LINKER_FLAGS} ${ALL_OBJS} -o client.bin
main.o: main.c
	${COMPILER} ${COMPILER_FLAGS} main.c

mem_mgr.o: mem_mgr.c mem_mgr.h
	${COMPILER} ${COMPILER_FLAGS} mem_mgr.c

uds_workings.o: uds_workings.c uds_workings.h
	${COMPILER} ${COMPILER_FLAGS} uds_workings.c

utils.o: utils.c utils.h
	${COMPILER} ${COMPILER_FLAGS} utils.c

clean_objs:
	rm ${ALL_OBJS}

place: ./client.bin
	mv ./client.bin ../bin

clean:
	rm ../bin/client.bin
