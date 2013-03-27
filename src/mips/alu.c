/*
 *    File: alu.c
 *	  Este módulo contiene todas las operaciones que puede realizar un procesador
 *	  MIPS.
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

#include <alu.h>
#include <vm.h>
#include <stdio.h>
#include <syscalls.h>

/* Variable global con los registros de la CPU,
   memoria, PC, etc.. */
cpu_t cpu;


/******************************************************************************************************
 Funciones Tipo-R
******************************************************************************************************/

// ¿Overflow?
void add(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rd = (*rs) + (*rt);
}

void addu(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rd = (*rs) + (*rt);
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
	cpu.registros.LO = (*rs) / (*rt);
	cpu.registros.HI = (*rs) % (*rt);
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
	cpu.registros.LO = (*rs) * (*rt);
}

void nor(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rd = ~((*rs) | (*rt));
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
	if ((*rs) < (*rt))
		*rd = 1;
	else
		*rd = 0;
}

void sltu(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	if ((*rs) < (*rt))
		*rd = 1;
	else
		*rd = 0;
}

void sra(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	int i = 0;
	int32_t signo = (*rt) & 0x80000000;
	
	for (; i < shamt; i++)
	{
		*rd = (*rt) >> 1;
		*rd |= signo;
	}
}

void srav(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	int i = 0;
	int32_t signo = (*rt) & 0x80000000;
	
	for (; i < (*rs); i++)
	{
		*rd = (*rt) >> 1;
		*rd |= signo;
	}
}

void srl(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rd = (*rt) >> shamt;
}

void srlv(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rd = (*rt) >> (*rs);
}

void sub(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rd = (*rs) - (*rt);
}

void subu(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rd = (*rs) - (*rt);
}

void xor(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rd = (*rs) ^ (*rt);
}

//Syscalls http://courses.missouristate.edu/kenvollmar/mars/help/syscallhelp.html
void syscall(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	switch (cpu.registros.v0)
	{
		case SYS_PRINT_INTEGER:
			print_integer(cpu.registros.a0);
			break;
		case SYS_READ_INTEGER:
			read_integer(&cpu.registros.v0);
			break;
		case SYS_EXIT:
			cpu.syscallTermination = 1;
			break;
		case SYS_PRINT_CHAR:
			print_char(cpu.registros.a0);
			break;
		case SYS_READ_CHAR:
			read_char(&cpu.registros.v0);
			break;
		default:
			printf("syscall %d no implementada!\n", cpu.registros.v0);
			break;
	}
}


/******************************************************************************************************
 Funciones Tipo-I
******************************************************************************************************/

void addi(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rt = (*rs) + offset;
}

void addiu(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rt = (*rs) + (offset);
}

void andi(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rt = (*rs) & offset;
}

void beq(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	if (*rs == *rt)
		cpu.PC += (--offset) << 2;
}

void bgez(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	if ((*rs) >= 0)
		cpu.PC += (--offset) << 2;
}

void bgtz(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	if ((*rs) > 0)
		cpu.PC += (--offset) << 2;
}

void blez(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	if ((*rs) <= 0)
		cpu.PC += (--offset) << 2;
}

void bltz(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	if ((*rs) < 0)
		cpu.PC += (--offset) << 2;
}

void bne(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	if (*rs != *rt)
		cpu.PC +=  (--offset) << 2;
}

void ori(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rt = (*rs) | offset;
}

void slti(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	if ((*rs) < offset)
		*rt = 1;
	else
		*rt = 0;
}

void sltiu(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	if ((*rs) < (offset))
		*rt = 1;
	else
		*rt = 0;
}

void xori(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rt = (*rs) ^ offset;
}


/******************************************************************************************************
 Funciones Tipo-J
******************************************************************************************************/


void j(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	cpu.PC = (cpu.PC & 0xF0000000) | direction;
}
