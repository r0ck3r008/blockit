COMPILER := gcc
COMPILER_FLAGS := -g -c
ALL_OBJS := transfer_utils.o uds_workings.o

all: ${ALL_OBJS}

transfer_utils.o: transfer_utils.c transfer_utils.h
	${COMPILER} ${COMPILER_FLAGS} transfer_utils.c

uds_workings.o: uds_workings.c uds_workings.h
	${COMPILER} ${COMPILER_FLAGS} uds_workings.c

clean:
	rm ${ALL_OBJS}
