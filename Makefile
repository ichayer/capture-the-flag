all:
	cd source; make all

client:
	cd source; make client

server:
	cd source; make server

clean:
	cd source; make clean

.PHONY: all client server clean