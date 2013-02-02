CC=gcc
PARAMS=-O2 -I./

all: main.o vm.o alu.o
	$(CC) $(PARAMS) main.o vm.o alu.o -o ../../bin/mips

main.o: main.c
	$(CC) $(PARAMS) -c main.c

vm.o: vm.c vm.h
	$(CC) $(PARAMS) -c vm.c

alu.o: alu.c alu.h
	$(CC) $(PARAMS) -c alu.c

clean:
	rm -f *.o