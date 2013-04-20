/*
 *    File: main.c
 *	  Contiene el punto de entrada del programa mips. Procesa
 *	  el programa que recibe por parámetro.
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

#include <stdio.h>
#include <getopt.h>
#include "definiciones.h"

extern int clean_mode; // En vm.c

/*
 * Función imprimirUso.
 * Muestra las opciones que tiene el ensamblador en
 * línea de comandos.
*/
void imprimirUso()
{
	printf("Uso: mips fichero [opciones]\n");
	printf("\t-h --help\tMuestra la ayuda\n");
	printf("\t-c --clean\tEjecuta el programa sin mostrar información de estado\n");
	printf("\t-v --version\tMuestra la versión\n");
}


int main(int argc, char * argv[])
{
	int accion = 0;
	char * entrada = NULL;

	while ((accion = getopt (argc, argv, "hcv")) != -1)
	{
		switch (accion)
		{
			case 'h':
				imprimirUso();
				return 1;
			case 'v':
				printf("MIPS Virtual Machine - version %.2f\n", MIPS_VER);
				return 1;
			case 'c':
				clean_mode = 1;
				break;
			case '?':
				imprimirUso();
				return 1;
		}
	}
	
	if (optind < argc)
		entrada = argv[optind];

	if (entrada != NULL)
		interpretarArchivo(entrada);
	else
		imprimirUso();

	return 0;
}