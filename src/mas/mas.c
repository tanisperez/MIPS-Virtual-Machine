#include <stdio.h>
#include <getopt.h>
#include <ensamblador.h>
#include <definiciones.h>

/*
 * Función imprimirUso.
 * Muestra las opciones que tiene el ensamblador en
 * línea de comandos.
*/
void imprimirUso()
{
	printf("Uso: mas fichero [opciones]\n");
	printf("\t-h --help\tMuestra la ayuda\n");
	printf("\t-o --output\tEspecifica el nombre del fichero de salida\n");
}

/*
 * Entrada del programa.
*/
int main(int argc, char * argv[])
{
	int accion = 0;
	char * entrada = NULL;
	char * salida = "a.out";

	printf("Mips ASsembler version %.2f\n\n", MAS_VER);

	
	while ((accion = getopt (argc, argv, "ho:")) != -1)
	{
		switch (accion)
		{
			case 'h':
				imprimirUso();
				break;
			case 'o':
				salida = optarg;
				break;
			case '?':
				imprimirUso();
				return 1;
			default:
				abort();
				break;
		}
	}

	if (optind < argc)
		entrada = argv[optind];

	if (entrada != NULL)
		ensamblarArchivo(entrada, salida);
	else
		imprimirUso();

	return 0;
}
