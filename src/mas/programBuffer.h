#ifndef PROGRAMBUFFER_H
#define PROGRAMBUFFER_H

#include <stdint.h>

#define DEFAULT_SIZE	512

typedef struct buffer_ {
	uint32_t * buffer;

	uint32_t tamBuffer;
	uint32_t bufferUsado;
} buffer_t;


#endif