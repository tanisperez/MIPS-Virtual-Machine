CC=gcc
PARAMS=-O2 -I./

all: mas.o ensamblador.o listaVariables.o mips.o
	$(CC) $(PARAMS) mas.o ensamblador.o listaVariables.o mips.o -o mas
	./mas prog1.asm -o prog1.bin

mas.o: mas.c
	$(CC) $(PARAMS) -c mas.c

ensamblador.o: ensamblador.c ensamblador.h
	$(CC) $(PARAMS) -c ensamblador.c

listaVariables.o: listaVariables.c listaVariables.h
	$(CC) $(PARAMS) -c listaVariables.c

mips.o: mips.c mips.h
	$(CC) $(PARAMS) -c mips.c

clean:
	rm *.o

copy: mas
	cp mas ../../bin/
