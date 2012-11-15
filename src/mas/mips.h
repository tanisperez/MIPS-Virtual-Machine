#ifndef MIPS_H
#define MIPS_H

#include <stdint.h>

/*
 * http://www.mrc.uidaho.edu/mrc/people/jff/digital/MIPSir.html
 *
 * Tipo de instrucciones
 *
 *  __________________________________________________________________
 * | Tipo | 31					Formato (bits)						0 |
 * |------------------------------------------------------------------|
 * |   R  | codopt(6) | rs(5) | rt(5) | rd(5) | shamt(5) | codfunc(6) |
 * |------------------------------------------------------------------|
 * |   I  | codopt(6) | rs(5) | rt(5) | inmediato/desplazamiento(16)  |
 * |------------------------------------------------------------------|
 * |   J  | codopt(6) | 			direccion(26)					  |
 * |__________________________________________________________________|
 * 
*/

#define MIPS_OPCODE 0x3F000000

typedef struct opcode{
	char * operacion;
	uint8_t codopt;
	char tipo;
	uint8_t codfunc;
} opcode_t;

typedef struct reg{
	char * nombre;
	char * numero;
	uint8_t codigo;
} register_t;

int obtenerInstruccion(char * instruccion[], int numeroParametros, uint32_t * opcode);


#endif
