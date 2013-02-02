#ifndef VM_H
#define VM_H

#include <stdint.h>

typedef struct registers{
	int32_t zero, at;
	int32_t v0, v1;
	int32_t a0, a1, a2, a3;
	int32_t t0, t1, t2, t3, t4, t5, t6, t7, t8, t9;
	int32_t s0, s1, s2, s3, s4, s5, s6, s7;
	int32_t k0, k1;
	int32_t gp, sp, fp, ra;
} registers_t;

typedef struct cpu{
	uint32_t * byteCode;
	uint32_t program_size;
	uint32_t PC;

	registers_t registros;
}cpu_t;


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
	void (*funcion)(cpu_t * cpu_info, uint32_t opcode);
} opcode_t;

void interpretarArchivo(char * archivo);

#endif