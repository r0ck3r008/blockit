COMPILER := gcc
LINKER_FLAGS := -pthread -lpcap -lcurl -lcargparse -Lcargparse/src
MEM := mem/mem_mgr.o mem/h_map.o mem/node.o
MISC := misc/main.o  misc/utils.o
NET := net/transfer_utils.o net/uds_workings.o net/parse.o
SNIFF := sniff/sniff.o
ALL_OBJS := ${MEM} ${MISC} ${NET} ${SNIFF}
all: server_bin clean_objs

server_bin: mem_tgt misc_tgt net_tgt sniff_tgt
	${COMPILER} ${LINKER_FLAGS} ${ALL_OBJS} -o server.bin

mem_tgt:
	make -C mem/

misc_tgt:
	make -C misc/

net_tgt:
	make -C net/

sniff_tgt:
	make -C sniff/

place: ./server.bin
	mv ./server.bin ../bin

clean_objs:
	make -C mem/ clean
	make -C misc/ clean
	make -C net/ clean
	make -C sniff/ clean

clean:
	rm ../bin/server.bin
