#include <stdio.h>
#include <string.h>
#include <ensamblador.h>
#include <listaVariables.h>
#include <stdint.h>

int main(int argc, char * argv[])
{
	uint32_t dato;
	printf("Mips ASsembler version 0.01\n\n");
	
	if (argc > 1)
	{

		ensamblarArchivo(argv[1], argv[3]);

	}
	else
		printf("Uso: mas file.asm -o file.bin\n");

	return 0;
}
