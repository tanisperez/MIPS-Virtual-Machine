#include <stdio.h>
#include <ensamblador.h>
#include <definiciones.h>

int main(int argc, char * argv[])
{
	printf("Mips ASsembler version %.2f\n\n", MAS_VER);
	
	if (argc > 1)
		ensamblarArchivo(argv[1], argv[3]);
	else
		printf("Uso: mas file.asm -o file.bin\n");

	return 0;
}
