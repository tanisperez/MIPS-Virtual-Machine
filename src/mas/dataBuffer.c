/*
 *    File: dataBuffer.c
 *	  Este módulo incluye una serie de funciones para trabajar con buffers de
 *	  memoria en donde se almacenarán los datos de las variables del programa.
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

#include "dataBuffer.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

/* Funciones privadas */
void data_buffer_realloc(data_buffer_t * d);


/*
 * Función data_buffer_init.
 * Recibe la dirección de memoria de una estructura buffer_t y
 * la inicializa. Reserva una cantidad de memoria DEFAULT_SIZE en bytes,
 * cuya constante está definida en dataBuffer.h.
*/
void data_buffer_init(data_buffer_t * d)
{
	if (d == NULL)
		printf("Error! Puntero nulo en data_buffer_init()!\n");

	d->buffer = NULL;
	d->tamBuffer = 0;
	d->bufferUsado = 0;
	d->buffer = (uint8_t *) malloc(DEFAULT_SIZE * sizeof(uint8_t));

	if (d->buffer != NULL)
		d->tamBuffer = DEFAULT_SIZE;
	else
		printf("Error! No se pudo reservar memoria con malloc en data_buffer_init()!\n");
}


/*
 * Función data_buffer_realloc.
 * Recibe por parámetro la dirección de memoria de una estructura data_buffer_t y se
 * encarga de incrementar su tamaño según la constante DEFAULT_SIZE. Esta función
 * no se puede llamar explícitamente, depende de data_buffer_write().
*/
void data_buffer_realloc(data_buffer_t * d)
{
	uint8_t * temp = NULL;

	temp = (uint8_t *) malloc((d->tamBuffer + DEFAULT_SIZE) * sizeof(uint8_t));
	if (temp != NULL)
	{
		memcpy(temp, d->buffer, d->tamBuffer * sizeof(uint8_t));
		free(d->buffer);
		d->tamBuffer += DEFAULT_SIZE;
		d->buffer = temp;
	}
	else
		printf("Error! No se pudo reservar memoria con realloc en data_buffer_realloc()!\n");
}


/*
 * Función data_buffer_write.
 * Recibe por parámetro la dirección de memoria de una estructura data_buffer_t,
 * la dirección de memoria del dato a escribir, y el tamaño del dato.
*/
void data_buffer_write(data_buffer_t * d, void * dato, uint32_t tam)
{
	if (d != NULL)
	{
		if (d->bufferUsado == d->tamBuffer)
			buffer_realloc(d);
		
		memcpy(&d->buffer[d->bufferUsado], dato, tam);
		d->bufferUsado += tam;
	}
	else
		printf("Error! La función data_buffer_write() recibió un puntero nulo!\n");
}


/*
 * Función data_buffer_free.
 * Libera la memoria reservada de la estructura data_buffer_t.
*/
void data_buffer_free(data_buffer_t * d)
{
	if (d != NULL)
		free(d->buffer);
}

