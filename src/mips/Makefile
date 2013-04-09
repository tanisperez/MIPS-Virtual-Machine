#Makefile for MIPS Virtual Machine
CC=gcc
PARAMS=-O2
OBJECTS=main.o vm.o alu.o syscalls.o
SOURCES=main.c vm.c alu.c syscalls.c

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

debug:
	$(CC) $(PARAMS) -g -DDEBUG $(SOURCES) -o ../../bin/mips

valgrind:
	$(CC) $(PARAMS) -g $(SOURCES) -o ../../bin/mips

clean:
	rm -f *.o