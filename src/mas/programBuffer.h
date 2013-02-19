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