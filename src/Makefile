all: libcargparse.so server_bin client_bin mv_bins

libcargparse.so: cargparse/src/Makefile
	make -C cargparse

server_bin: server/Makefile
	make -C server

client_bin: client/Makefile
	make -C client

mv_bins:
	make -C server place
	make -C client place

clean:
	make -C cargparse clean
	make -C server clean
	make -C client clean
	rm `find . -type s`
