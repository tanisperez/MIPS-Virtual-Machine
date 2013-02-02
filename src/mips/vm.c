#include <vm.h>
#include <stdio.h>
#include <malloc.h>

/* Variables globales */
uint8_t * byteCode = NULL;

registers_t registros; /* Todos los registros de la CPU MIPS */


/* Definición de los prototipos de las funciones privadas en vm.c */
void execute();


void execute()
{


}

void interpretarArchivo(char * archivo)
{
	uint32_t opcode = 0;
	FILE * source = NULL;
	size_t bytes2Read = 0, bytesRead = 0;

	if ((source = fopen(archivo, "r")) != NULL)
	{
		fseek(source, 0L, SEEK_END); //Nos situamos al final del archivo
		bytes2Read = ftell(source); //Obtenemos la posición del fichero, que es el tamaño del archivo

		byteCode = (uint8_t *) malloc(bytes2Read);
		if (byteCode != NULL)
		{
			rewind(source); //Nos situamos al principio del archivo
			bytesRead = fread(byteCode, bytes2Read, 1, source); //¿Aplicar un algoritmo voraz?
			if (bytesRead == bytes2Read)
			{
				execute();
				free(byteCode);
			}
			else
				printf("Error de lectura en el fichero \"%s\"\n", archivo);
		}
		else
			printf("Error! No hay memoria suficiente para ejecutar el archivo \"%s\"\n", archivo);

		fclose(source);
	}
	else
		printf("Error! No se pudo ejecutar el archivo \"%s\"!\n", archivo);
}