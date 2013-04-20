#Makefile for Mips ASsembler
CC=gcc
PARAMS=-O2 -fno-builtin
OBJECTS=mas.o ensamblador.o mips.o saltos.o programBuffer.o cadenas.o dataBuffer.o variables.o
SOURCES=mas.c ensamblador.c mips.c saltos.c programBuffer.c cadenas.c dataBuffer.c variables.c

all: $(OBJECTS)
	$(CC) $(PARAMS) $(OBJECTS) -o ../../bin/mas

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

dataBuffer.o: dataBuffer.c dataBuffer.h
	$(CC) $(PARAMS) -c dataBuffer.c

variables.o: variables.c variables.h
	$(CC) $(PARAMS) -c variables.c

debug:
	$(CC) $(PARAMS) -g -DDEBUG $(SOURCES) -o ../../bin/mas

clean:
	rm *.o
