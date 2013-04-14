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
#include "definiciones.h"

/* Añadir parámetro opcional de Debugging */
int main(int argc, char * argv[])
{
	printf("MIPS Virtual Machine - version %.2f\n\n", MIPS_VER);

	if (argc > 1)
		interpretarArchivo(argv[1]);
	else
		printf("Uso: mips file.bin\n");

	return 0;
}