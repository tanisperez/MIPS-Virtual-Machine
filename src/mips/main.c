#include <stdio.h>
#include <definiciones.h>


int main(int argc, char * argv[])
{
	printf("MIPS Virtual Machine - version %.2f\n\n", MIPS_VER);

	if (argc > 1)
		interpretarArchivo(argv[1]);
	else
		printf("Uso: mips file.bin\n");

	return 0;
}