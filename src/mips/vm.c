/*
 *    File: vm.c
 *	  Este módulo contiene todas las instrucciones del procesador MIPS.
 *	  Procesa instrucción a instrucción un programa y ejecuta la función
 *	  correspondiente de la alu.
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

#include <vm.h>
#include <alu.h>
#include <stdio.h>
#include <signal.h>
#include <malloc.h>
#include <string.h>
#include <elf.h>

extern cpu_t cpu; //En alu.c

/* Definición de los prototipos de las funciones privadas en vm.c */
void visualizarCPUInfo();
void execute();
void interpretarInstruccion(uint32_t opcode);

/*
 * Revisar los desplazamientos lógicos y aritméticos.
 * When shifting an unsigned value, the >> operator 
 * in C is a logical shift. When shifting a signed value, the >> operator is an arithmetic shift.

 * Pseudoinstrucciones:
 * http://en.wikibooks.org/wiki/MIPS_Assembly/Pseudoinstructions
*/

/* Lista de códigos de operación, separados por su nombre,
   código de operación, tipo de instrucción, código de función y
   el puntero a una función en C que realizará la operación deseada. */
opcode_t listaInstrucciones[] = {
	/* Instrucciones Tipo-R */
	{"add",		0x00, 'R', 0x20, add}, //add $d, $s, $t
	{"addu",	0x00, 'R', 0x21, addu}, //addu $d, $s, $t
	{"and",		0x00, 'R', 0x24, and}, //and $d, $s, $t
	{"div",		0x00, 'R', 0x1A, div}, //div $s, $t
	{"divu",	0x00, 'R', 0x1B, divu}, //divu $s, $t
	{"jalr",	0x00, 'R', 0x09, NULL}, //jalr $d, $s
	{"jr",		0x00, 'R', 0x08, NULL}, //jr $s
	{"mfhi",	0x00, 'R', 0x10, mfhi}, //mfhi $d
	{"mflo",	0x00, 'R', 0x12, mflo}, //mflo $d
	{"mthi",	0x00, 'R', 0x11, NULL}, //mthi $d
	{"mtlo",	0x00, 'R', 0x13, NULL}, //mtlo $d
	{"mult",	0x00, 'R', 0x18, mult}, //mult $s, $t
	{"multu",	0x00, 'R', 0x19, multu}, //multu $s, $t
	{"nor",		0x00, 'R', 0x27, nor}, //nor $d, $s, $t
	{"or",		0x00, 'R', 0x25, or}, //or $d, $s, $t
	{"sll",		0x00, 'R', 0x00, sll}, //sll $d, $t, h
	{"sllv",	0x00, 'R', 0x04, sllv}, //sllv $d, $t, $s
	{"slt",		0x00, 'R', 0x2A, slt}, //slt $d, $s, $t
	{"sltu",	0x00, 'R', 0x2B, sltu}, //sltu $d, $s, $t
	{"sra",		0x00, 'R', 0x03, sra}, //sra $d, $t, h
	{"srav",	0x00, 'R', 0x07, srav}, //sra $d, $t, $s
	{"srl",		0x00, 'R', 0x02, srl}, //srl $d, $t, h
	{"srlv",	0x00, 'R', 0x06, srlv}, //srlv $d, $t, $s
	{"sub",		0x00, 'R', 0x22, sub}, //sub $d, $s, $t
	{"subu",	0x00, 'R', 0x23, subu}, //subu $d, $s, $t
	{"xor",		0x00, 'R', 0x26, xor}, //xor $d, $s, $t
	{"syscall",	0x00, 'R', 0x0C, syscall}, //syscall
	/* Instrucciones Tipo-I */
	{"addi", 	0x08, 'I', 0x00, addi}, //addi $t, $s, imm
	{"addiu", 	0x09, 'I', 0x00, addiu}, //addiu $t, $s, imm
	{"andi",	0x0C, 'I', 0x00, andi}, //andi $t, $s, imm
	{"beq",		0x04, 'I', 0x00, beq}, //beq $s, $t, offset
	{"bgez",	0x01, 'I', 0x01, bgez}, //bgez $s, offset
	{"bgezal",	0x01, 'I', 0x11, NULL}, //bgezal $s, offset
	{"bgtz",	0x07, 'I', 0x00, bgtz}, //bgtz $s, offset
	{"blez",	0x06, 'I', 0x00, blez}, //blez $s, offset
	{"bltz",	0x01, 'I', 0x00, bltz}, //bltz $s, offset
	{"bltzal",	0x01, 'I', 0x10, NULL}, //bltzal $s, offset
	{"bne",		0x05, 'I', 0x00, bne}, //bne $s, $t, offset
	{"lb",		0x20, 'I', 0x00, NULL}, //lb $t, offset($s)
	{"lui",		0x0F, 'I', 0x00, NULL}, //lui $t, imm
	{"lw",		0x23, 'I', 0x00, NULL}, //lw $t, offset($s)
	{"ori",		0x0D, 'I', 0x00, ori}, //ori $t, $s, imm
	{"sb",		0x28, 'I', 0x00, NULL}, //sb $t, offset($s)
	{"slti",	0x0A, 'I', 0x00, slti}, //slti $t, $s, imm
	{"sltiu",	0x0B, 'I', 0x00, sltiu}, //sltiu $t, $s, imm
	{"sw",		0x2B, 'I', 0x00, NULL}, //sw $t, offset($s)
	{"xori",	0x0E, 'I', 0x00, xori}, //xori $t, $s, imm
	/* Instrucciones Tipo-J */
	{"j",		0x02, 'J', 0x00, j}, //j target
	{"jal",		0x03, 'J', 0x00, NULL}, //jal target
	{NULL, 		0x3F, '\0', 0x00, NULL},
	};

/* Lista de registros con su nombre, su número de registro(son 32)
   y el puntero al registro de la CPU al que hacen referencia. */
register_t listaRegistros[REG_COUNT] = {
	{"$zero", 	0,	&cpu.registros.zero},
	{"$at", 	1,	&cpu.registros.at},
	{"$v0", 	2,	&cpu.registros.v0},
	{"$v1", 	3,	&cpu.registros.v1},
	{"$a0", 	4,	&cpu.registros.a0},
	{"$a1", 	5,	&cpu.registros.a1},
	{"$a2", 	6,	&cpu.registros.a2},
	{"$a3", 	7,	&cpu.registros.a3},
	{"$t0", 	8,	&cpu.registros.t0},
	{"$t1", 	9,	&cpu.registros.t1},
	{"$t2", 	10,	&cpu.registros.t2},
	{"$t3", 	11,	&cpu.registros.t3},
	{"$t4", 	12,	&cpu.registros.t4},
	{"$t5", 	13,	&cpu.registros.t5},
	{"$t6", 	14,	&cpu.registros.t6},
	{"$t7", 	15,	&cpu.registros.t7},
	{"$s0", 	16,	&cpu.registros.s0},
	{"$s1", 	17,	&cpu.registros.s1},
	{"$s2", 	18,	&cpu.registros.s2},
	{"$s3", 	19,	&cpu.registros.s3},
	{"$s4", 	20, &cpu.registros.s4},
	{"$s5", 	21,	&cpu.registros.s5},
	{"$s6", 	22,	&cpu.registros.s6},
	{"$s7", 	23,	&cpu.registros.s7},
	{"$t8", 	24,	&cpu.registros.t8},
	{"$t9", 	25,	&cpu.registros.t9},
	{"$k0", 	26,	&cpu.registros.k0},
	{"$k1", 	27,	&cpu.registros.k1},
	{"$gp", 	28,	&cpu.registros.gp},
	{"$sp", 	29,	&cpu.registros.sp},
	{"$fp", 	30,	&cpu.registros.fp},
	{"$ra", 	31,	&cpu.registros.ra}
	};


/*
 * Función sigintEvent.
 * Ejecuta esta función cuando el sistema detecta la pulsación de
 * Control + C. Establece el flag syscallTermination a 1 que detendrá
 * el bucle de la función execute().
*/
void sigintEvent()
{
	cpu.syscallTermination = 1;
}


/*
 * Función visualizarCPUInfo.
 * Muestra el estado de los registros de la CPU en formato hexadecimal.
*/
void visualizarCPUInfo()
{
	printf("\nMIPS Virtual Machine\n");
	printf("v0: %.8x v1: %.8x\n", cpu.registros.v0, cpu.registros.v1);
	printf("a0: %.8x a1: %.8x a2: %.8x a3: %.8x\n", cpu.registros.a0, 
		cpu.registros.a1, cpu.registros.a2, cpu.registros.a3);
	printf("t0: %.8x t1: %.8x t2: %.8x t3: %.8x\nt4: %.8x t5: %.8x t6: %.8x t7: %.8x\nt8: %.8x t9: %.8x\n",
		cpu.registros.t0, cpu.registros.t1, cpu.registros.t2, cpu.registros.t3,
		cpu.registros.t4, cpu.registros.t5, cpu.registros.t6, cpu.registros.t7,
		cpu.registros.t8, cpu.registros.t9);
	printf("s0: %.8x s1: %.8x s2: %.8x s3: %.8x\ns4: %.8x s5: %.8x s6: %.8x s7: %.8x\n",
		cpu.registros.s0, cpu.registros.s1, cpu.registros.s2, cpu.registros.s3,
		cpu.registros.s4, cpu.registros.s5, cpu.registros.s6, cpu.registros.s7);
	printf("k0: %.8x k1: %.8x\n", cpu.registros.k0, cpu.registros.k1);
	printf("gp: %.8x sp: %.8x fp: %.8x ra: %.8x\n", cpu.registros.gp, cpu.registros.sp,
		cpu.registros.fp, cpu.registros.ra);
	printf("L0: %.8x HI: %.8x\n", cpu.registros.LO, cpu.registros.HI);
}


/*
 * Función execute.
 * Ejecuta el código del programa ya cargado en memoria interpretando cada instrucción. El programa
 * termina cuando se llama explícitamente la syscall número 10 o el PC (Program Counter) llega al
 * final del programa.
*/
void execute()
{
	uint32_t opcode = 0;

	while (cpu.PC < cpu.program_size && cpu.syscallTermination == 0)
	{
		opcode = cpu.byteCode[cpu.PC >> 2]; //Dividimos entre 4
		printf("PC: %.8x Opcode: %.8x\n", cpu.PC, opcode);

		cpu.PC += 4;

		interpretarInstruccion(opcode);
	}

	visualizarCPUInfo(cpu);
}


/*
 * Función liberarPrograma.
 * Libera la memoria del programa y se encarga de salir del bucle de la
 * función execute. Esta función sólo debe ser exportada para usarse en la
 * syscall número 10.
*/
void liberarPrograma()
{
	free(cpu.byteCode);
}


/*
 * Fúnción interpretarInstruccion.
 * Recibe un código de operación de 32 bits, comprueba en la lista de instrucciones
 * si es una instrucción conocida e implementada, a continuación averigua que
 * registros de la CPU están afectados por la operación y decide que función realizar.
*/
void interpretarInstruccion(uint32_t opcode)
{
	unsigned int i = 0;
	uint8_t codopt = (uint8_t)(opcode >> 26);
	uint8_t codopt2 = (uint8_t)((opcode & 0x001F0000) >> 16);
	uint8_t codfunc = (uint8_t)(opcode & 0x0000003F);
	int32_t * rs = NULL;
	int32_t * rt = NULL;
	int32_t * rd = NULL;
	uint8_t shamt = 0, temp = 0;
	int16_t offset = 0;
	uint32_t direction = 0;

	for (; listaInstrucciones[i].operacion != NULL; i++)
	{
		if ((listaInstrucciones[i].codopt == codopt && listaInstrucciones[i].tipo == 'J') //Tipo-J
			|| (codopt == 0x00 && listaInstrucciones[i].codfunc == codfunc
				&& listaInstrucciones[i].tipo == 'R') //Tipo-R
			|| (listaInstrucciones[i].codopt == codopt && listaInstrucciones[i].codfunc == 0x00 &&
				listaInstrucciones[i].tipo == 'I') //Tipo-I
			|| (listaInstrucciones[i].codopt == codopt == 0x01 && listaInstrucciones[i].codfunc == codopt2 &&
				listaInstrucciones[i].tipo == 'I'))
		{
			if (listaInstrucciones[i].funcion == NULL)
				printf("Función %s sin implementar o desconocida!\n", listaInstrucciones[i].operacion);
			else
			{
				printf("Instrucción: %s\n", listaInstrucciones[i].operacion);
				switch (listaInstrucciones[i].tipo)
				{
					case 'R':
						temp = (uint8_t)((opcode & 0x03E00000) >> 21);
						rs = listaRegistros[temp].reg_pointer;
						temp = (uint8_t)((opcode & 0x001F0000) >> 16);
						rt = listaRegistros[temp].reg_pointer;
						temp = (uint8_t)((opcode & 0x0000F800) >> 11);
						rd = listaRegistros[temp].reg_pointer;
						shamt = (uint8_t)((opcode & 0x000007C0) >> 6);
						listaInstrucciones[i].funcion(rs, rt, rd, shamt, offset, direction);
						break;
					case 'I':
						temp = (uint8_t)((opcode & 0x03E00000) >> 21);
						rs = listaRegistros[temp].reg_pointer;
						temp = (uint8_t)((opcode & 0x001F0000) >> 16);
						rt = listaRegistros[temp].reg_pointer;
						offset = (int16_t)(opcode & 0x0000FFFF);
						listaInstrucciones[i].funcion(rs, rt, rd, shamt, offset, direction);
						break;
					case 'J':
						direction = (uint32_t)(opcode & 0x03FFFFFF);
						listaInstrucciones[i].funcion(rs, rt, rd, shamt, offset, direction);
						break;
				}
			}
			break;
		}
	}

}


/*
 * Función interpretarArchivo.
 * Se encarga de leer un archivo, cargarlo en memoria e intentar ejecutarlo.
*/
void interpretarArchivo(char * archivo)
{
	Elf32_Ehdr elf_header;
	Elf32_Phdr prog_header;
	FILE * source = NULL;
	size_t itemsRead = 0;

	if ((source = fopen(archivo, "r")) != NULL)
	{
		fread(&elf_header, sizeof(Elf32_Ehdr), 1, source);

		if (elf_header.e_ident[EI_MAG0] == ELFMAG0 && elf_header.e_ident[EI_MAG1] == ELFMAG1 &&
			elf_header.e_ident[EI_MAG2] == ELFMAG2 && elf_header.e_ident[EI_MAG3] == ELFMAG3)
		{
			if (elf_header.e_type == ET_EXEC)
			{
				if (elf_header.e_machine == EM_MIPS_RS3_LE)
				{
					fread(&prog_header, sizeof(Elf32_Phdr), 1, source);
					if (prog_header.p_type == PT_LOAD && prog_header.p_flags == (PF_X | PF_R))
					{
						cpu.program_size = prog_header.p_filesz;

						cpu.byteCode = (uint32_t *) malloc((cpu.program_size / 4) * sizeof(uint32_t));
						if (cpu.byteCode != NULL)
						{
							itemsRead = fread(cpu.byteCode, 4, cpu.program_size / 4, source); //¿Aplicar un algoritmo voraz?
							if (itemsRead == (cpu.program_size / 4))
							{
								cpu.PC = 0;
								cpu.syscallTermination = 0;
								memset(&cpu.registros, 0, sizeof(registers_t));

								signal(SIGINT, sigintEvent);

								execute();

								liberarPrograma();
							}
							else
								printf("Error de lectura en el fichero \"%s\"\n", archivo);
						}
						else
							printf("Error! No hay memoria suficiente para ejecutar el archivo \"%s\"\n", archivo);
					}
					else
						printf("El segmento no contiene código ejecutable!\n");
				}
				else
					printf("El código máquina de esta arquitectura no está soportado!\n");
			}
			else
				printf("El fichero \"%s\" no es un fichero ejecutable!\n", archivo);
		}
		else
			printf("El fichero \"%s\" no es un fichero elf válido!\n", archivo);
		
		fclose(source);
	}
	else
		printf("Error! No se pudo ejecutar el archivo \"%s\"!\n", archivo);
}