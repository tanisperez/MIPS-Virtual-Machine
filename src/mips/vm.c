#include <vm.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

/* Definición de los prototipos de las funciones privadas en vm.c */
void visualizarCPUInfo(cpu_t * cpu_info);
void execute(cpu_t * cpu_info);
void interpretarInstruccion(cpu_t * cpu_info, uint32_t opcode);

opcode_t listaInstrucciones[] = {
	/* Instrucciones Tipo-R */
	{"add",		0x00, 'R', 0x20, NULL}, //add $d, $s, $t
	{"addu",	0x00, 'R', 0x21, NULL}, //addu $d, $s, $t
	{"and",		0x00, 'R', 0x24, NULL}, //and $d, $s, $t
	{"div",		0x00, 'R', 0x1A, NULL}, //div $s, $t
	{"divu",	0x00, 'R', 0x1B, NULL}, //divu $s, $t
	{"jr",		0x00, 'R', 0x08, NULL}, //jr $s
	{"mfhi",	0x00, 'R', 0x10, NULL}, //mfhi $d
	{"mflo",	0x00, 'R', 0x12, NULL}, //mflo $d
	{"mult",	0x00, 'R', 0x18, NULL}, //mult $s, $t
	{"multu",	0x00, 'R', 0x19, NULL}, //multu $s, $t
	{"nop",		0x00, 'R', 0x00, NULL}, //nop
	{"or",		0x00, 'R', 0x25, NULL}, //or $d, $s, $t
	{"sll",		0x00, 'R', 0x00, NULL}, //sll $d, $t, h
	{"sllv",	0x00, 'R', 0x04, NULL}, //sllv $d, $t, $s
	{"slt",		0x00, 'R', 0x2A, NULL}, //slt $d, $s, $t
	{"sltu",	0x00, 'R', 0x2B, NULL}, //sltu $d, $s, $t
	{"sra",		0x00, 'R', 0x03, NULL}, //sra $d, $t, h
	{"srl",		0x00, 'R', 0x02, NULL}, //srl $d, $t, h
	{"srlv",	0x00, 'R', 0x06, NULL}, //srlv $d, $t, $s
	{"sub",		0x00, 'R', 0x22, NULL}, //sub $d, $s, $t
	{"subu",	0x00, 'R', 0x23, NULL}, //subu $d, $s, $t
	{"xor",		0x00, 'R', 0x26, NULL}, //xor $d, $s, $t
	{"syscall",	0x00, 'R', 0x0C, NULL}, //syscall
	/* Instrucciones Tipo-I */
	{"addi", 	0x08, 'I', 0x00, NULL}, //addi $t, $s, imm
	{"addiu", 	0x09, 'I', 0x00, NULL}, //addiu $t, $s, imm
	{"andi",	0x0C, 'I', 0x00, NULL}, //andi $t, $s, imm
	{"beq",		0x04, 'I', 0x00, NULL}, //beq $s, $t, offset
	{"bgez",	0x01, 'I', 0x01, NULL}, //bgez $s, offset
	{"bgezal",	0x01, 'I', 0x11, NULL}, //bgezal $s, offset
	{"bgtz",	0x07, 'I', 0x00, NULL}, //bgtz $s, offset
	{"blez",	0x06, 'I', 0x00, NULL}, //blez $s, offset
	{"bltz",	0x01, 'I', 0x00, NULL}, //bltz $s, offset
	{"bltzal",	0x01, 'I', 0x10, NULL}, //bltzal $s, offset
	{"bne",		0x05, 'I', 0x00, NULL}, //bne $s, $t, offset
	{"lb",		0x20, 'I', 0x00, NULL}, //lb $t, offset($s)
	{"lui",		0x0F, 'I', 0x00, NULL}, //lui $t, imm
	{"lw",		0x23, 'I', 0x00, NULL}, //lw $t, offset($s)
	{"ori",		0x0D, 'I', 0x00, NULL}, //ori $t, $s, imm
	{"sb",		0x28, 'I', 0x00, NULL}, //sb $t, offset($s)
	{"slti",	0x0A, 'I', 0x00, NULL}, //slti $t, $s, imm
	{"sltiu",	0x0B, 'I', 0x00, NULL}, //sltiu $t, $s, imm
	{"sw",		0x2B, 'I', 0x00, NULL}, //sw $t, offset($s)
	{"xori",	0x0E, 'I', 0x00, NULL}, //xori $t, $s, imm
	/* Instrucciones Tipo-J */
	{"j",		0x02, 'J', 0x00, NULL}, //j target
	{"jal",		0x03, 'J', 0x00, NULL}, //jal target
	{NULL, 		0x3F, '\0', 0x00, NULL},
	};


void visualizarCPUInfo(cpu_t * cpu_info)
{
	printf("\nMIPS Virtual Machine\n");
	printf("v0: %.8x v1: %.8x\n", cpu_info->registros.v0, cpu_info->registros.v1);
	printf("a0: %.8x a1: %.8x a2: %.8x a3: %.8x\n", cpu_info->registros.a0, 
		cpu_info->registros.a1, cpu_info->registros.a2, cpu_info->registros.a3);
	printf("t0: %.8x t1: %.8x t2: %.8x t3: %.8x\nt4: %.8x t5: %.8x t6: %.8x t7: %.8x\nt8: %.8x t9: %.8x\n",
		cpu_info->registros.t0, cpu_info->registros.t1, cpu_info->registros.t2, cpu_info->registros.t3,
		cpu_info->registros.t4, cpu_info->registros.t5, cpu_info->registros.t6, cpu_info->registros.t7,
		cpu_info->registros.t8, cpu_info->registros.t9);
	printf("s0: %.8x s1: %.8x s2: %.8x s3: %.8x\ns4: %.8x s5: %.8x s6: %.8x s7: %.8x\n",
		cpu_info->registros.s0, cpu_info->registros.s1, cpu_info->registros.s2, cpu_info->registros.s3,
		cpu_info->registros.s4, cpu_info->registros.s5, cpu_info->registros.s6, cpu_info->registros.s7);
	printf("k0: %.8x k1: %.8x\n", cpu_info->registros.k0, cpu_info->registros.k1);
	printf("gp: %.8x sp: %.8x fp: %.8x ra: %.8x\n", cpu_info->registros.gp, cpu_info->registros.sp,
		cpu_info->registros.fp, cpu_info->registros.ra);
}


void execute(cpu_t * cpu_info)
{
	uint32_t opcode = 0;

	while (cpu_info->PC < cpu_info->program_size)
	{
		opcode = cpu_info->byteCode[cpu_info->PC >> 2]; //Dividimos entre 4
		printf("Opcode: %.8x\n", (int)opcode);
		interpretarInstruccion(cpu_info, opcode);

		cpu_info->PC += 4;
	}

	visualizarCPUInfo(cpu_info);
}

void interpretarInstruccion(cpu_t * cpu_info, uint32_t opcode)
{
	unsigned int i = 0;
	uint8_t codopt = (uint8_t)(opcode >> 26);
	uint8_t codfunc = (uint8_t)(opcode && 0x0000003F);

	for (; listaInstrucciones[i].operacion != NULL; i++)
	{
		if ((codopt == 0x00 && listaInstrucciones[i].codfunc == codfunc)
			|| (listaInstrucciones[i].codopt == codopt && listaInstrucciones[i].codfunc == 0x00)
			|| (listaInstrucciones[i].codopt = 0x01 && listaInstrucciones[i].codfunc == codfunc))
		{
			if (listaInstrucciones[i].funcion == NULL)
				printf("Función %s sin implementar!\n", listaInstrucciones[i].operacion);
			else
				listaInstrucciones[i].funcion(cpu_info, opcode);
			break;
		}
	}

}

void interpretarArchivo(char * archivo)
{
	FILE * source = NULL;
	size_t itemsRead = 0;
	cpu_t cpu_info;

	if ((source = fopen(archivo, "r")) != NULL)
	{
		fseek(source, 0L, SEEK_END); //Nos situamos al final del archivo
		cpu_info.program_size = ftell(source); //Obtenemos la posición del fichero, que es el tamaño del archivo

		cpu_info.byteCode = (uint32_t *) malloc(cpu_info.program_size / 4);
		if (cpu_info.byteCode != NULL)
		{
			rewind(source); //Nos situamos al principio del archivo
			itemsRead = fread(cpu_info.byteCode, 4, cpu_info.program_size / 4, source); //¿Aplicar un algoritmo voraz?
			if (itemsRead == (cpu_info.program_size / 4))
			{
				cpu_info.PC = 0;
				memset(&cpu_info.registros, 0, sizeof(registers_t));

				execute(&cpu_info);

				free(cpu_info.byteCode);
			}
			else
				printf("Error de lectura en el fichero \"%s\"\n", archivo);
		}
		else
			printf("Error! No hay memoria suficiente para ejecutar el archivo \"%s\"\n", archivo);

		fclose(source);
	}
	else
		printf("Error! No se pudo ejecutar el archivo \"%s\"!\n", archivo);
}