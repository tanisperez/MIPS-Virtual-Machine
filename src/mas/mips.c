#include <mips.h>
#include <stdio.h>
#include <stdint.h>

unsigned char ensambladoOK = 1;

opcode_t listaInstrucciones[] = {
	/* Instrucciones Tipo-R */
	{"add",		0x00, 'R', 0x20}, //add $d, $s, $t
	{"addu",	0x00, 'R', 0x21}, //addu $d, $s, $t
	{"and",		0x00, 'R', 0x24}, //and $d, $s, $t
	{"div",		0x00, 'R', 0x1A}, //div $s, $t
	{"divu",	0x00, 'R', 0x1B}, //divu $s, $t
	{"jr",		0x00, 'R', 0x08}, //jr $s
	{"mfhi",	0x00, 'R', 0x10}, //mfhi $d
	{"mflo",	0x00, 'R', 0x12}, //mflo $d
	{"mult",	0x00, 'R', 0x18}, //mult $s, $t
	{"multu",	0x00, 'R', 0x19}, //multu $s, $t
	{"nop",		0x00, 'R', 0x00}, //nop
	{"or",		0x00, 'R', 0x25}, //or $d, $s, $t
	{"sll",		0x00, 'R', 0x00}, //sll $d, $t, h
	{"sllv",	0x00, 'R', 0x04}, //sllv $d, $t, $s
	{"slt",		0x00, 'R', 0x2A}, //slt $d, $s, $t
	{"sltu",	0x00, 'R', 0x2B}, //sltu $d, $s, $t
	{"sra",		0x00, 'R', 0x03}, //sra $d, $t, h
	{"srl",		0x00, 'R', 0x02}, //srl $d, $t, h
	{"srlv",	0x00, 'R', 0x06}, //srlv $d, $t, $s
	{"sub",		0x00, 'R', 0x22}, //sub $d, $s, $t
	{"subu",	0x00, 'R', 0x23}, //subu $d, $s, $t
	{"xor",		0x00, 'R', 0x26}, //xor $d, $s, $t
	{"syscall",	0x00, 'R', 0x0C}, //syscall
	/* Instrucciones Tipo-I */
	{"addi", 	0x08, 'I', 0x00}, //addi $t, $s, imm
	{"addiu", 	0x09, 'I', 0x00}, //addiu $t, $s, imm
	{"andi",	0x0C, 'I', 0x00}, //andi $t, $s, imm
	{"beq",		0x04, 'I', 0x00}, //beq $s, $t, offset
	{"bgez",	0x01, 'I', 0x01}, //bgez $s, offset
	{"bgezal",	0x01, 'I', 0x11}, //bgezal $s, offset
	{"bgtz",	0x07, 'I', 0x00}, //bgtz $s, offset
	{"blez",	0x06, 'I', 0x00}, //blez $s, offset
	{"bltz",	0x01, 'I', 0x00}, //bltz $s, offset
	{"bltzal",	0x01, 'I', 0x10}, //bltzal $s, offset
	{"bne",		0x05, 'I', 0x00}, //bne $s, $t, offset
	{"lb",		0x20, 'I', 0x00}, //lb $t, offset($s)
	{"lui",		0x0F, 'I', 0x00}, //lui $t, imm
	{"lw",		0x23, 'I', 0x00}, //lw $t, offset($s)
	{"ori",		0x0D, 'I', 0x00}, //ori $t, $s, imm
	{"sb",		0x28, 'I', 0x00}, //sb $t, offset($s)
	{"slti",	0x0A, 'I', 0x00}, //slti $t, $s, imm
	{"sltiu",	0x0B, 'I', 0x00}, //sltiu $t, $s, imm
	{"sw",		0x2B, 'I', 0x00}, //sw $t, offset($s)
	{"xori",	0x0E, 'I', 0x00}, //xori $t, $s, imm
	/* Instrucciones Tipo-J */
	{"j",		0x02, 'J', 0x00}, //j target
	{"jal",		0x03, 'J', 0x00}, //jal target
	{NULL, 		0x3F, '\0', 0x00},
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

opcode_t obtenerOpcode(char * nombre);
register_t obtenerRegistro(char * nombre);
uint32_t obtenerIntruccionI(char * instruccion[], int numeroParametros);

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
	opcode_t opcode = {NULL, 0x3F, '\0'};

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
uint32_t obtenerIntruccionI(char * instruccion[], int numeroParametros)
{
	uint32_t opcodeI = 0;
	uint16_t inmediato = 0;
	uint8_t rs = 0, rt = 0;

	register_t registro = obtenerRegistro(instruccion[1]);
	
	ensambladoOK = 0;
	if (registro.nombre != NULL)
	{
		rt = registro.codigo;
		registro = obtenerRegistro(instruccion[2]);
		if (registro.nombre != NULL)
		{
			rs = registro.codigo;

			if (!strcmp(instruccion[3], "$zero"))
				strcpy(instruccion[3], "0");

			/* Comprobar la longitud en el sscanf */
			if (sscanf(instruccion[3], "%d", &inmediato) == 1)
			{
				opcodeI |= (rs << 21) | (rt << 16) | inmediato;
				ensambladoOK = 1;
			}
			else
				printf("Error! \"%s\" no es un número de 16 bits válido.\n", instruccion[3]);
		}
		else
			printf("Error! El registro \"%s\" no existe.\n", instruccion[2]);
	}
	else
		printf("Error! El registro \"%s\" no existe.\n", instruccion[1]);
	
	return opcodeI;
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
				*opcode += obtenerIntruccionI(instruccion, numeroParametros);
				if (ensambladoOK)
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


