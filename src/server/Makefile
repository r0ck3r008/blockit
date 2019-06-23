COMPILER := gcc
LINKER_FLAGS := -pthread -lcurl -lcargparse -Lcargparse/src
MISC := misc/main.o misc/mem_mgr.o misc/utils.o
NET := net/transfer_utils.o net/uds_workings.o
ALL_OBJS := ${MISC} ${NET}
all: server_bin clean_objs

server_bin: misc_tgt net_tgt
	${COMPILER} ${LINKER_FLAGS} ${ALL_OBJS} -o server.bin

misc_tgt:
	make -C misc/

net_tgt:
	make -C net/

place: ./server.bin
	mv ./server.bin ../bin

clean_objs:
	make -C misc/ clean
	make -C net/ clean

clean:
	rm ../bin/server.bin
