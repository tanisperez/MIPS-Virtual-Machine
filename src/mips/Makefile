#Makefile for MIPS Virtual Machine
CC=gcc
PARAMS=-O2 -fno-builtin
OBJECTS=main.o vm.o alu.o syscalls.o fpu.o
SOURCES=main.c vm.c alu.c syscalls.c fpu.c

all: $(OBJECTS) 
	$(CC) $(PARAMS) $(OBJECTS) -o ../../bin/mips

main.o: main.c
	$(CC) $(PARAMS) -c main.c

vm.o: vm.c vm.h
	$(CC) $(PARAMS) -c vm.c

alu.o: alu.c alu.h
	$(CC) $(PARAMS) -c alu.c

syscalls.o: syscalls.c syscalls.h
	$(CC) $(PARAMS) -c syscalls.c

fpu.o: fpu.c fpu.h
	$(CC) $(PARAMS) -c fpu.c

debug:
	$(CC) $(PARAMS) -g -DDEBUG $(SOURCES) -o ../../bin/mips

valgrind:
	$(CC) $(PARAMS) -g $(SOURCES) -o ../../bin/mips

clean:
	rm -f *.o