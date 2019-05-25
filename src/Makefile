all: libcargparse.so server_bin client_bin

libcargparse.so: cargparse/src/Makefile
	make -C cargparse/src

server_bin: server/Makefile
	make -C server

client_bin: client/Makefile
	make -C client

clean:
	make -C cargparse/src clean
	make -C server clean
	make -C client clean
