all: libcargparse.so server_bin

libcargparse.so: cargparse/src/Makefile
	make -C cargparse/src

server_bin: server/Makefile
	make -C server

clean:
	make -C cargparse/src clean
	make -C server clean
