/*
 *    File: syscalls.c
 *	  Módulo que incluye las funciones para operar con los dispositivos de
 *	  Entrada/Salida y otras funciones del sistema.
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

#include "syscalls.h"
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

/*
 * Función: fatal_error.
 * Esta función sirve de interfaz para terminar la ejecución
 * de la máquina virtual ante un fallo mostrando un mensaje.
*/
void fatal_error(const char * error)
{
	puts(error);
	exit(EXIT_FAILURE);
}

/* Syscall 1 */
void print_integer(uint32_t i)
{
	printf("%d", i);
}

/* Syscall 4 */
void print_string(char * string)
{
	puts(string);
}

/* Syscall 5 */
void read_integer(uint32_t * i)
{
	char buff[100];

	if (fgets(buff, 100, stdin) != NULL && i != NULL)
	{
		buff[strlen(buff) - 1] = '\0';
		if (sscanf(buff, "%d", i) != 1)
			printf("Error! \"%s\" no es un número entero!\n", buff); //¿Exception?
	}
	else
		printf("syscall read_integer error! Error en la entrada de datos!\n");
}

/* Syscall 11 */
void print_char(uint32_t c)
{
	putchar(c);
}

/* Syscall 12 */
void read_char(uint32_t * c)
{
	*c = getchar();
}