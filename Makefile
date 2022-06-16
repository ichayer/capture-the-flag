all:
	cd source; make all

client:
	cd source; make client

server:
	cd source; make server

clean:
	cd source; make clean

check:
	mkdir -p check
	cppcheck --quiet --enable=all --force --inconclusive . 2> ./check/cppout.txt

	pvs-studio-analyzer trace -- make
	pvs-studio-analyzer analyze
	plog-converter -a '64:1,2,3;GA:1,2,3;OP:1,2,3' -t tasklist -o ./check/report.tasks ./PVS-Studio.log
	
	rm PVS-Studio.log
	mv strace_out check

.PHONY: all client server clean check