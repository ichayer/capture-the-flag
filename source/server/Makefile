include ./../Makefile.inc

SOURCES=$(wildcard *.c)
OUTPUT_FILE=./../../server

all:
	$(GCC) $(GCCFLAGS) $(SOURCES) -lm -o $(OUTPUT_FILE)

clean:
	rm -f $(OUTPUT_FILE)

.PHONY: all clean