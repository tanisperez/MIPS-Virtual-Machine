/*
 *    File: programBuffer.c
 *	  Este módulo incluye una serie de funciones para trabajar con buffers de memoria
 *	  que pueden ser modificados de tamaño.
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

#include "programBuffer.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

/* Funciones privadas */
void buffer_realloc(buffer_t * b);

/*
 * Función buffer_init.
 * Recibe la dirección de memoria de una estructura buffer_t y
 * la inicializa. Reserva una cantidad de memoria DEFAULT_SIZE * sizeof(uint32_t),
 * cuya constante está definida en programBuffer.h.
*/
void buffer_init(buffer_t * b)
{
	if (b == NULL)
		printf("Error! Puntero nulo en buffer_init()!\n");

	b->buffer = NULL;
	b->tamBuffer = 0;
	b->bufferUsado = 0;
	b->buffer = (uint32_t *) malloc(DEFAULT_SIZE * sizeof(uint32_t));

	if (b->buffer != NULL)
		b->tamBuffer = DEFAULT_SIZE;
	else
		printf("Error! No se pudo reservar memoria con malloc en buffer_init()!\n");
}


/*
 * Función buffer_realloc.
 * Recibe por parámetro la dirección de memoria de una estructura buffer_t y se
 * encarga de incrementar su tamaño según la constante DEFAULT_SIZE. Esta función
 * no se puede llamar explícitamente, depende de buffer_addOpcode().
*/
void buffer_realloc(buffer_t * b)
{
	uint32_t * temp = NULL;

	temp = (uint32_t *) malloc((b->tamBuffer + DEFAULT_SIZE) * sizeof(uint32_t));
	if (temp != NULL)
	{
		memcpy(temp, b->buffer, b->tamBuffer * sizeof(uint32_t));
		free(b->buffer);
		b->tamBuffer += DEFAULT_SIZE;
		b->buffer = temp;
	}
	else
		printf("Error! No se pudo reservar memoria con realloc en buffer_realloc()!\n");
}


/*
 * Función buffer_addOpcode.
 * Recibe por parámetro la dirección de memoria de una estructura buffer_t y
 * un número sin signo de 4 bytes, que es la operación a guardar.
 * La escribe en memoria y si necesita más memoria llama a buffer_realloc().
*/
void buffer_addOpcode(buffer_t * b, uint32_t opcode)
{
	if (b != NULL)
	{
		if (b->bufferUsado == b->tamBuffer)
			buffer_realloc(b);
		
		b->buffer[b->bufferUsado] = opcode;
		b->bufferUsado++;
	}
	else
		printf("Error! La función buffer_addOpcode recibió un puntero nulo!\n");
}


/*
 * Función buffer_free.
 * Libera la memoria reservada de la estructura buffer_t.
*/
void buffer_free(buffer_t * b)
{
	if (b != NULL)
		free(b->buffer);
}


