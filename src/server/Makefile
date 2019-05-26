COMPILER := gcc
LINKER_FLAGS := -pthread -lcurl -lcargparse -Lcargparse/src
ALL_OBJS := main.o mem_mgr.o transfer_utils.o uds_workings.o utils.o

all: server_bin clean_objs

server_bin: ${ALL_OBJS}
	${COMPILER} ${LINKER_FLAGS} ${ALL_OBJS} -o server_bin

main.o: main.c
	${COMPILER} -c main.c

mem_mgr.o: mem_mgr.c mem_mgr.h
	${COMPILER} -c mem_mgr.c

transfer_utils.o: transfer_utils.c transfer_utils.h
	${COMPILER} -c transfer_utils.c

uds_workings.o: uds_workings.c uds_workings.h
	${COMPILER} -c uds_workings.c

utils.o: utils.c utils.h
	${COMPILER} -c utils.c

clean_objs:
	rm ${ALL_OBJS}

clean:
	rm ./server_bin
