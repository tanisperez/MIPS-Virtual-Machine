#include <alu.h>
#include <vm.h>

/* Variable global con los registros de la CPU,
   memoria, PC, etc.. */
cpu_t cpu;


/* Funciones Tipo-R */

void add(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rd = *rs + *rt;
}


/* Funciones Tipo-I */

void addi(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rt = *rs + offset;
}