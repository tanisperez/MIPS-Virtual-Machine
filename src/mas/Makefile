CC=gcc
PARAMS=-O2 -I./

all: mas.o ensamblador.o mips.o saltos.o programBuffer.o cadenas.o
	$(CC) $(PARAMS) mas.o ensamblador.o mips.o saltos.o programBuffer.o cadenas.o -o ../../bin/mas

mas.o: mas.c
	$(CC) $(PARAMS) -c mas.c

ensamblador.o: ensamblador.c ensamblador.h
	$(CC) $(PARAMS) -c ensamblador.c

mips.o: mips.c mips.h
	$(CC) $(PARAMS) -c mips.c

saltos.o: saltos.c saltos.h
	$(CC) $(PARAMS) -c saltos.c

programBuffer.o: programBuffer.c programBuffer.h
	$(CC) $(PARAMS) -c programBuffer.c

cadenas.o: cadenas.c cadenas.h
	$(CC) $(PARAMS) -c cadenas.c

debug:
	$(CC) $(PARAMS) -g mas.c ensamblador.c mips.c saltos.c programBuffer.c cadenas.c -o ../../bin/mas

clean:
	rm *.o
