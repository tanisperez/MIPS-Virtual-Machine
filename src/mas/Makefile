CC=gcc
PARAMS=-O2 -I./

all: mas.o ensamblador.o listaVariables.o mips.o saltos.o
	$(CC) $(PARAMS) mas.o ensamblador.o listaVariables.o mips.o saltos.o -o ../../bin/mas

mas.o: mas.c
	$(CC) $(PARAMS) -c mas.c

ensamblador.o: ensamblador.c ensamblador.h
	$(CC) $(PARAMS) -c ensamblador.c

listaVariables.o: listaVariables.c listaVariables.h
	$(CC) $(PARAMS) -c listaVariables.c

mips.o: mips.c mips.h
	$(CC) $(PARAMS) -c mips.c

saltos.o: saltos.c saltos.h
	$(CC) $(PARAMS) -c saltos.c

clean:
	rm *.o

copy: mas
	cp mas ../../bin/
