#include <vm.h>
#include <stdio.h>
#include <stdint.h>


void interpretarArchivo(char * archivo)
{
	uint32_t opcode = 0;
	FILE * source = NULL;
	size_t bytesRead = 0;

	if ((source = fopen(archivo, "r")) != NULL)
	{
		/* Reservar memoria dinámica para todo el ejecutable y cargarlo en memoria,
		   o utilizar file mapping */
	}
	else
		printf("Error! No se pudo ejecutar el archivo \"%s\"!\n", archivo);
}