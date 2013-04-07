/*
 *    File: programBuffer.h
 *	  Incluye los prototipos de funciones y tipos del módulo dataBuffer.c
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

#ifndef DATABUFFER_H
#define DATABUFFER_H

#include <stdint.h>

/* 1024 bytes */
#define DEFAULT_SIZE	1024

typedef struct data_buffer_ {
	uint8_t * buffer;

	uint32_t tamBuffer; //Tamaño del buffer en bytes
	uint32_t bufferUsado; //Número de bytes consumidoss
} data_buffer_t;


void data_buffer_init(data_buffer_t * d);
void data_buffer_write(data_buffer_t * d, void * dato, uint32_t tam);
void data_buffer_free(data_buffer_t * d);

#endif