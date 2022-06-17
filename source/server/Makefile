include ./../Makefile.inc

SOURCES=$(wildcard *.c)
SOURCES_ASM=$(wildcard *.asm)

OBJECTS_ASM=$(SOURCES_ASM:%.asm=obj/%.asm.o)

OUTPUT_FILE=./../../server

all: $(OUTPUT_FILE)

$(OUTPUT_FILE): $(OBJECTS_ASM)
	mkdir -p obj
	$(GCC) $(GCCFLAGS) $(OBJECTS_ASM) $(SOURCES) -lm -o $(OUTPUT_FILE)

obj/%.asm.o : %.asm
	mkdir -p obj
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -f $(OUTPUT_FILE)
	rm -rf obj

.PHONY: all clean