/*
 *    File: mas.c
 *	  Contiene el punto de entrada del programa, se encarga de procesar
 *	  los parámetros que recibe y ensamblar un archivo a partir del código fuente.
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; version 2 of the License.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *    General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *    02111-1307, USA.
 *
 */

#include "definiciones.h"
#include "ensamblador.h"
#include <stdio.h>
#include <getopt.h>

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
				return 1;
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
