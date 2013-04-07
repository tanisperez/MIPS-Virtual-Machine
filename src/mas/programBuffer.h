/*
 *    File: programBuffer.h
 *	  Incluye los prototipos de funciones y tipos del módulo programBuffer.c
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

#ifndef PROGRAMBUFFER_H
#define PROGRAMBUFFER_H

#include <stdint.h>

/* 512 opcodes * sizeof(uint32_t) = 2KB */
#define DEFAULT_SIZE	512

typedef struct buffer_ {
	uint32_t * buffer;

	uint32_t tamBuffer; //Tamaño del buffer en palabras de 4 bytes
	uint32_t bufferUsado; //Cantidad de palabras usadas
} buffer_t;


void buffer_init(buffer_t * b);
void buffer_addOpcode(buffer_t * b, uint32_t opcode);
void buffer_free(buffer_t * b);

#endif