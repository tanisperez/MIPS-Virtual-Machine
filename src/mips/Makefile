CC=gcc
PARAMS=-O2 -I./

all: main.o vm.o alu.o syscalls.o
	$(CC) $(PARAMS) main.o vm.o alu.o syscalls.o -o ../../bin/mips

main.o: main.c
	$(CC) $(PARAMS) -c main.c

vm.o: vm.c vm.h
	$(CC) $(PARAMS) -c vm.c

alu.o: alu.c alu.h
	$(CC) $(PARAMS) -c alu.c

syscalls.o: syscalls.c syscalls.h
	$(CC) $(PARAMS) -c syscalls.c

debug:
	$(CC) $(PARAMS) -g main.c vm.c alu.c syscalls.c -o ../../bin/mips

clean:
	rm -f *.o