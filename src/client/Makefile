COMPILER=gcc
LINKER_FLAGS= -lcargparse -Lcargparse/src
ALL_OBJS= main.o mem_mgr.o uds_workings.o utils.o

all: client_bin clean_objs

client_bin: ${ALL_OBJS}
	${COMPILER} ${LINKER_FLAGS} ${ALL_OBJS} -o client_bin
main.o: main.c
	${COMPILER} -c main.c

mem_mgr.o: mem_mgr.c mem_mgr.h
	${COMPILER} -c mem_mgr.c

uds_workings.o: uds_workings.c uds_workings.h
	${COMPILER} -c uds_workings.c

utils.o: utils.c utils.h
	${COMPILER} -c utils.c

clean_objs:
	rm ${ALL_OBJS}

clean:
	rm ./client_bin
