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

#include "alu.h"
#include "vm.h"
#include "syscalls.h"
#include <stdio.h>
#include <string.h>
#include "fpu.h"

/* Variable global con los registros de la CPU,
   memoria, PC, etc.. */
cpu_t cpu;
extern fpu_registers_t fpu;


/******************************************************************************************************
 Funciones Tipo-R
******************************************************************************************************/

void add(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	/*if (IS_OVERFLOW(*rs, *rt))
		fpu.fcsr |= CAUSE_OVERFLOW;
	else
		if (IS_UNDERFLOW(*rs, *rt))
			fpu.fcsr |= CAUSE_UNDERFLOW;
		else	*/
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

void jalr(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rd = cpu.PC;
	cpu.PC = *rs;
}

void jr(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	cpu.PC = cpu.registros.ra;
}

void mfhi(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rd = cpu.registros.HI;
}

void mflo(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rd = cpu.registros.LO;
}

void mthi(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	cpu.registros.HI = *rs;
}

void mtlo(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	cpu.registros.LO = *rs;
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
		case SYS_PRINT_STRING:
			if (cpu.registros.a0 >= 0 && cpu.registros.a0 < cpu.memory_size)
				print_string(&cpu.memory[cpu.registros.a0]);
			else
				fatal_error("Syscall print_string! Violación de segmento!\n");
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

void bgezal(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	if (*rs >= 0)
	{
		cpu.registros.ra = cpu.PC;
		cpu.PC += (--offset) << 2;
	}
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

void bltzal(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	if (*rs < 0)
	{
		cpu.registros.ra = cpu.PC;
		cpu.PC += (--offset) << 2;
	}
}

void bne(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	if (*rs != *rt)
		cpu.PC +=  (--offset) << 2;
}

void lb(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	if ((*rs) + offset >= 0 && (*rs) + offset < cpu.memory_size)
		*rt = cpu.memory[(*rs) + offset];
	else
		fatal_error("Operación lb. Violación de segmento!\n");
}

void lui(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rt = (direction << 16);
}

void lw(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	if ((*rs) + (offset * sizeof(uint16_t)) >= 0 && (*rs) + (offset * sizeof(uint16_t)) < cpu.memory_size - 1)
		memcpy(rt, &cpu.memory[(*rs) + (offset * sizeof(uint16_t))], sizeof(uint16_t));
	else
		fatal_error("Operación lw. Violación de segmento!\n");
}

void ori(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	*rt = (*rs) | offset;
}

void sb(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	if ((*rs) + offset >= 0 && (*rs) + offset < cpu.memory_size)
		cpu.memory[(*rs) + offset] = (uint8_t)(0x000000FF & (*rt));
	else
		fatal_error("Operación sb. Violación de segmento!\n");
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

void sw(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	if ((*rs) + (offset * sizeof(uint16_t)) >= 0 && (*rs) + (offset * sizeof(uint16_t)) < cpu.memory_size - 1)
		memcpy(&cpu.memory[(*rs) + (offset * sizeof(uint16_t))], rt, sizeof(uint16_t));
	else
		fatal_error("Operación sb. Violación de segmento!\n");
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

void jal(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction)
{
	cpu.registros.ra = cpu.PC;
	cpu.PC = (cpu.PC & 0xF0000000) | direction;
}
