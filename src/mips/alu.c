#include <alu.h>
#include <vm.h>

/* Variable global con los registros de la CPU,
   memoria, PC, etc.. */
cpu_t cpu;


/******************************************************************************************************
 Funciones Tipo-R
******************************************************************************************************/

// ¿Overflow?
void add(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rd = *rs + *rt;
}

void addu(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rd = abs(*rs) + abs(*rt);
}

void and(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rd = (*rs) & (*rt);
}

void div(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	cpu.registros.LO = (*rs) / (*rt);
	cpu.registros.HI = (*rs) % (*rt);
}

void divu(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	cpu.registros.LO = abs(*rs) / abs(*rt);
	cpu.registros.HI = abs(*rs) % abs(*rt);
}

void mfhi(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rd = cpu.registros.HI;
}

void mflo(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rd = cpu.registros.LO;
}

void mult(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	cpu.registros.LO = (*rs) * (*rt);
}

void multu(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	cpu.registros.LO = abs(*rs) * abs(*rt);
}

void nop(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{

}

void or(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rd = (*rs) | (*rt);
}

void sll(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rd = (*rt) << shamt;
}

void sllv(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rd = (*rt) << (*rs);
}

void slt(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	if (*rs < *rt)
		*rd = 1;
	else
		*rd = 0;
}

void sltu(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	if (abs(*rs) < abs(*rt))
		*rd = 1;
	else
		*rd = 0;
}


/******************************************************************************************************
 Funciones Tipo-I
******************************************************************************************************/

void addi(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rt = *rs + offset;
}

void addiu(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rt = abs(*rs) + abs(offset);
}

void andi(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rt = (*rs) & offset;
}

void ori(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rt = (*rs) | offset;
}

void slti(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	if (*rs < offset)
		*rt = 1;
	else
		*rt = 0;
}

void sltiu(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	if (abs(*rs) < abs(offset))
		*rt = 1;
	else
		*rt = 0;
}


/******************************************************************************************************
 Funciones Tipo-J
******************************************************************************************************/