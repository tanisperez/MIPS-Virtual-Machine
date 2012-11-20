#include <mips.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

opcode_t listaInstrucciones[] = {
	/* Instrucciones Tipo-R */
	{"add",		0x00, 'R', 0x20, 3}, //add $d, $s, $t
	{"addu",	0x00, 'R', 0x21, 3}, //addu $d, $s, $t
	{"and",		0x00, 'R', 0x24, 3}, //and $d, $s, $t
	{"div",		0x00, 'R', 0x1A, 2}, //div $s, $t
	{"divu",	0x00, 'R', 0x1B, 2}, //divu $s, $t
	{"jr",		0x00, 'R', 0x08, 1}, //jr $s
	{"mfhi",	0x00, 'R', 0x10, 1}, //mfhi $d
	{"mflo",	0x00, 'R', 0x12, 1}, //mflo $d
	{"mult",	0x00, 'R', 0x18, 2}, //mult $s, $t
	{"multu",	0x00, 'R', 0x19, 2}, //multu $s, $t
	{"nop",		0x00, 'R', 0x00, 0}, //nop
	{"or",		0x00, 'R', 0x25, 3}, //or $d, $s, $t
	{"sll",		0x00, 'R', 0x00, 3}, //sll $d, $t, h
	{"sllv",	0x00, 'R', 0x04, 3}, //sllv $d, $t, $s
	{"slt",		0x00, 'R', 0x2A, 3}, //slt $d, $s, $t
	{"sltu",	0x00, 'R', 0x2B, 3}, //sltu $d, $s, $t
	{"sra",		0x00, 'R', 0x03, 3}, //sra $d, $t, h
	{"srl",		0x00, 'R', 0x02, 3}, //srl $d, $t, h
	{"srlv",	0x00, 'R', 0x06, 3}, //srlv $d, $t, $s
	{"sub",		0x00, 'R', 0x22, 3}, //sub $d, $s, $t
	{"subu",	0x00, 'R', 0x23, 3}, //subu $d, $s, $t
	{"xor",		0x00, 'R', 0x26, 3}, //xor $d, $s, $t
	{"syscall",	0x00, 'R', 0x0C, 0}, //syscall
	/* Instrucciones Tipo-I */
	{"addi", 	0x08, 'I', 0x00, 3}, //addi $t, $s, imm ----->
	{"addiu", 	0x09, 'I', 0x00, 3}, //addiu $t, $s, imm ----->
	{"andi",	0x0C, 'I', 0x00, 3}, //andi $t, $s, imm ----->
	{"beq",		0x04, 'I', 0x00, 3}, //beq $s, $t, offset ----->
	{"bgez",	0x01, 'I', 0x01, 2}, //bgez $s, offset
	{"bgezal",	0x01, 'I', 0x11, 2}, //bgezal $s, offset
	{"bgtz",	0x07, 'I', 0x00, 2}, //bgtz $s, offset
	{"blez",	0x06, 'I', 0x00, 2}, //blez $s, offset
	{"bltz",	0x01, 'I', 0x00, 2}, //bltz $s, offset
	{"bltzal",	0x01, 'I', 0x10, 2}, //bltzal $s, offset
	{"bne",		0x05, 'I', 0x00, 3}, //bne $s, $t, offset ----->
	{"lb",		0x20, 'I', 0x00, 2}, //lb $t, offset($s)
	{"lui",		0x0F, 'I', 0x00, 2}, //lui $t, imm
	{"lw",		0x23, 'I', 0x00, 2}, //lw $t, offset($s)
	{"ori",		0x0D, 'I', 0x00, 3}, //ori $t, $s, imm ----->
	{"sb",		0x28, 'I', 0x00, 2}, //sb $t, offset($s)
	{"slti",	0x0A, 'I', 0x00, 3}, //slti $t, $s, imm ----->
	{"sltiu",	0x0B, 'I', 0x00, 3}, //sltiu $t, $s, imm ----->
	{"sw",		0x2B, 'I', 0x00, 2}, //sw $t, offset($s)
	{"xori",	0x0E, 'I', 0x00, 3}, //xori $t, $s, imm ----->
	/* Instrucciones Tipo-J */
	{"j",		0x02, 'J', 0x00, 1}, //j target
	{"jal",		0x03, 'J', 0x00, 1}, //jal target
	{NULL, 		0x3F, '\0', 0x00, 0},
	};

register_t listaRegistros[] = {
	{"$zero", 	"$0", 	0},
	{"$at", 	"$1", 	1},
	{"$v0", 	"$2", 	2},
	{"$v1", 	"$3", 	3},
	{"$a0", 	"$4", 	4},
	{"$a1", 	"$5", 	5},
	{"$a2", 	"$6", 	6},
	{"$a3", 	"$7", 	7},
	{"$t0", 	"$8", 	8},
	{"$t1", 	"$9", 	9},
	{"$t2", 	"$10", 	10},
	{"$t3", 	"$11", 	11},
	{"$t4", 	"$12", 	12},
	{"$t5", 	"$13", 	13},
	{"$t6", 	"$14", 	14},
	{"$t7", 	"$15", 	15},
	{"$s0", 	"$16", 	16},
	{"$s1", 	"$17", 	17},
	{"$s2", 	"$18", 	18},
	{"$s3", 	"$19", 	19},
	{"$s4", 	"$20", 	20},
	{"$s5", 	"$21", 	21},
	{"$s6", 	"$22", 	22},
	{"$s7", 	"$23", 	23},
	{"$t8", 	"$24", 	24},
	{"$t9", 	"$25", 	25},
	{"$k0", 	"$26", 	26},
	{"$k1", 	"$27", 	27},
	{"$gp", 	"$28", 	28},
	{"$sp", 	"$29", 	29},
	{"$fp", 	"$30", 	30},
	{"$ra", 	"$31", 	31},
	{NULL, 		NULL, 	0}
	};

int strToUINT16(char * cadena, uint16_t * inmediato);
opcode_t obtenerOpcode(char * nombre);
register_t obtenerRegistro(char * nombre);
int obtenerIntruccionI(char * instruccion[], int numeroParametros, opcode_t codopt, uint32_t * opcode);


/*
 * Función strToUINT16.
 * Convierte una cadena de caracteres en un número de 16 bits sin signo.
 * <= Una cadena de caracteres.
 * <= La dirección de memoria de un número de 16 bits sin signo, donde
 * se va a almacenar el número convertido.
 * => Devuelve 1 si tiene éxito y 0 si no lo tiene.
*/
int strToUINT16(char * cadena, uint16_t * inmediato)
{
	int temp = 0;
	if (sscanf(cadena, "%d", &temp) == 1)
	{
		*inmediato = (uint16_t)temp;
		return 1;
	}
	else
		return 0;
}

/*
 * Función obtenerOpcode.
 * Busca en la lista de instrucciones, la instrucción dad
 * por el parámetro nombre.
 * Si no existe, devuelve un opcode con los atributos:
 * 	 opcode_t opcode = {NULL, 0x3F, '\0'};
*/
opcode_t obtenerOpcode(char * nombre)
{
	int i = 0;
	opcode_t opcode = {NULL, 0x3F, '\0', 0x00, 0};

	for (; listaInstrucciones[i].operacion != NULL; i++)
		if (!strcmp(nombre, listaInstrucciones[i].operacion))
		{
			opcode = listaInstrucciones[i];
			break;
		}

	return opcode;
}


/*
 * Función obtenerRegistro.
 * Busca en la lista de registros, la instrucción que coincida
 * en nombre o en número con el argumento dado.
 * Si no existe, devuelve un registro con los atributos:
 *    register_t registro = {NULL, NULL, 0};
*/
register_t obtenerRegistro(char * nombre)
{
	int i = 0;
	register_t registro = {NULL, NULL, 0};

	for (; listaRegistros[i].nombre != NULL; i++)
		if (!strcmp(listaRegistros[i].nombre, nombre) || !strcmp(listaRegistros[i].numero, nombre))
		{
			registro = listaRegistros[i];
			break;
		}
	
	return registro;
}

uint32_t obtenerInstruccionR(char * instruccion[])
{
	

}

/*
 * Devuelve una instrucción de tipo I a partir
 * del array de parámetros que recibe.
*/
int obtenerIntruccionI(char * instruccion[], int numeroParametros, opcode_t codopt, uint32_t * opcode)
{
	int resultado = 0;
	register_t rt, rs;
	uint32_t opcodeI = 0;
	uint16_t inmediato = 0;
	
	switch (codopt.codopt)
	{
		//Operación lb
		case 0x20:
			break;
		//Operación lw
		case 0x23:
			break;
		//Operación sb
		case 0x28:
			break;
		//Operación sw
		case 0x2B:
			break;

		default:
			switch (numeroParametros - 1)
			{
				case 3:
					rt = obtenerRegistro(instruccion[1]);
					if (rt.nombre != NULL)
					{
						rs = obtenerRegistro(instruccion[2]);
						if (rs.nombre != NULL)
						{
							/* Si se cumple la condición significa que son instrucciones de salto:
								beq o bne. */
							if (codopt.codopt == 0x04 || codopt.codopt == 0x05)
							{

							}
							else
							{
								if (strToUINT16(instruccion[3], &inmediato))
								{
									*opcode = (codopt.codopt << 26) | (rs.codigo << 21) 
													| (rt.codigo << 16) | inmediato;
									resultado = 1;
								}
								else
									printf("Error! La cadena \"%s\" no es un número válido de 16 bits!\n", instruccion[3]);
							}
						}
						else
							printf("Error! El registro \"%s\" no es un identificador de registro válido!\n", instruccion[2]);
					}
					else
						printf("Error! El registro \"%s\" no es un identificador de registro válido!\n", instruccion[1]);
			}
	}

	return resultado;
}


uint32_t obtenerInstruccionJ(char * instruccion[])
{
	uint32_t opcodeJ = 0;

	

}

/*
 * Función obtenerInstruccion.
 * A partir del array que contiene la instrucción y sus parámetros, genera
 * una instrucción de 32 bits para el juego de instrucciones de la arquitectura MIPS.
 *
*/
int obtenerInstruccion(char * instruccion[], int numeroParametros, uint32_t * opcode)
{
	int result = 0;
	*opcode = 0;

	opcode_t codopt = obtenerOpcode(instruccion[0]);
	if (codopt.operacion != NULL)
	{
		*opcode = codopt.codopt << 26;

		switch (codopt.tipo)
		{
			case 'R':
				break;

			case 'I':
				if (obtenerIntruccionI(instruccion, numeroParametros, codopt, opcode))
					result = 1;
				break;

			case 'J':
				break;
		}		
	}
	else 
		printf("Warning! La instrucción \"%s\" no está implementada! La instrucción es ignorada.\n", 
			instruccion[0]);

	return result;
}


