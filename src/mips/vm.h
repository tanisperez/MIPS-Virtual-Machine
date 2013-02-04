#ifndef VM_H
#define VM_H

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

typedef struct opcode{
	char * operacion;
	uint8_t codopt;
	char tipo;
	uint8_t codfunc;
	void (*funcion)(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction);
} opcode_t;

typedef struct reg{
	char * nombre;
	uint8_t codigo;
	int32_t * reg_pointer;
} register_t;

void interpretarArchivo(char * archivo);

#endif