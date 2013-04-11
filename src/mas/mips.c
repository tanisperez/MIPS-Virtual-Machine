/*
 *    File: mips.c
 *	  Contiene todas las instrucciones de la arquitectura MIPS, con sus códigos
 *	  de operación, tipo de instrucción (R, J o I), código de función y número de parámetros.
 *	  A partir de una cadena de instrucción, identifica que tipo de instrucción es y la pasa
 *	  a código máquina.
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

#include "mips.h"
#include <stdio.h>
#include <string.h>
#include "cadenas.h"
#include "programBuffer.h"
#include "saltos.h"
#include "variables.h"

opcode_t listaInstrucciones[] = {
	/* Instrucciones Tipo-R */
	{"add",		0x00, 'R', 0x20, 3}, //add $d, $s, $t
	{"addu",	0x00, 'R', 0x21, 3}, //addu $d, $s, $t
	{"and",		0x00, 'R', 0x24, 3}, //and $d, $s, $t
	{"div",		0x00, 'R', 0x1A, 2}, //div $s, $t
	{"divu",	0x00, 'R', 0x1B, 2}, //divu $s, $t
	{"jalr",	0x00, 'R', 0x09, 2}, //jalr $d, $s
	{"jr",		0x00, 'R', 0x08, 1}, //jr $s
	{"mfhi",	0x00, 'R', 0x10, 1}, //mfhi $d
	{"mflo",	0x00, 'R', 0x12, 1}, //mflo $d
	{"mthi",	0x00, 'R', 0x11, 1}, //mthi $s
	{"mtlo",	0x00, 'R', 0x13, 1}, //mtlo $s
	{"mult",	0x00, 'R', 0x18, 2}, //mult $s, $t
	{"multu",	0x00, 'R', 0x19, 2}, //multu $s, $t
	{"nor",		0x00, 'R', 0x27, 3}, //nor $d, $s, $t
	{"or",		0x00, 'R', 0x25, 3}, //or $d, $s, $t
	{"sll",		0x00, 'R', 0x00, 3}, //sll $d, $t, h
	{"sllv",	0x00, 'R', 0x04, 3}, //sllv $d, $t, $s
	{"slt",		0x00, 'R', 0x2A, 3}, //slt $d, $s, $t
	{"sltu",	0x00, 'R', 0x2B, 3}, //sltu $d, $s, $t
	{"sra",		0x00, 'R', 0x03, 3}, //sra $d, $t, h
	{"srav",	0x00, 'R', 0x07, 3}, //srav $d, $t, $s
	{"srl",		0x00, 'R', 0x02, 3}, //srl $d, $t, h
	{"srlv",	0x00, 'R', 0x06, 3}, //srlv $d, $t, $s
	{"sub",		0x00, 'R', 0x22, 3}, //sub $d, $s, $t
	{"subu",	0x00, 'R', 0x23, 3}, //subu $d, $s, $t
	{"xor",		0x00, 'R', 0x26, 3}, //xor $d, $s, $t
	{"syscall",	0x00, 'R', 0x0C, 0}, //syscall
	/* Instrucciones Tipo-I */
	{"addi", 	0x08, 'I', 0x00, 3}, //addi $t, $s, imm
	{"addiu", 	0x09, 'I', 0x00, 3}, //addiu $t, $s, imm
	{"andi",	0x0C, 'I', 0x00, 3}, //andi $t, $s, imm
	{"beq",		0x04, 'I', 0x00, 3}, //beq $s, $t, offset
	{"bgez",	0x01, 'I', 0x01, 2}, //bgez $s, offset
	{"bgezal",	0x01, 'I', 0x11, 2}, //bgezal $s, offset
	{"bgtz",	0x07, 'I', 0x00, 2}, //bgtz $s, offset
	{"blez",	0x06, 'I', 0x00, 2}, //blez $s, offset
	{"bltz",	0x01, 'I', 0x00, 2}, //bltz $s, offset
	{"bltzal",	0x01, 'I', 0x10, 2}, //bltzal $s, offset
	{"bne",		0x05, 'I', 0x00, 3}, //bne $s, $t, offset
	{"lb",		0x20, 'I', 0x00, 2}, //lb $t, offset($s)
	{"lui",		0x0F, 'I', 0x00, 2}, //lui $t, imm
	{"lw",		0x23, 'I', 0x00, 2}, //lw $t, offset($s)
	{"ori",		0x0D, 'I', 0x00, 3}, //ori $t, $s, imm
	{"sb",		0x28, 'I', 0x00, 2}, //sb $t, offset($s)
	{"slti",	0x0A, 'I', 0x00, 3}, //slti $t, $s, imm
	{"sltiu",	0x0B, 'I', 0x00, 3}, //sltiu $t, $s, imm
	{"sw",		0x2B, 'I', 0x00, 2}, //sw $t, offset($s)
	{"xori",	0x0E, 'I', 0x00, 3}, //xori $t, $s, imm
	/* Instrucciones Tipo-J */
	{"j",		0x02, 'J', 0x00, 1}, //j target
	{"jal",		0x03, 'J', 0x00, 1}, //jal target
	{NULL, 		0x3F, '\0', 0x00, 0},
	};

registro_t listaRegistros[] = {
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

/* Funciones privadas */
opcode_t obtenerOpcode(char * nombre);
registro_t obtenerRegistro(char * nombre);
int obtenerInstruccionR(char * instruccion[], int numeroParametros, opcode_t codopt, uint32_t * opcode);
int obtenerInstruccionI(char * instruccion[], int numeroParametros, opcode_t codopt, uint32_t * opcode);
int obtenerInstruccionJ(char * instruccion[], int numeroParametros, opcode_t codopt, uint32_t * opcode);

/* Variables externas de ensamblador.c */
extern saltos_list_t listaEtiquetasSalto;
extern i_saltos_list_t listaInstruccionesSaltoDesconocido;
extern variables_list_t listaEtiquetasVariable;
extern buffer_t progBuffer;


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
 *    registro_t registro = {NULL, NULL, 0};
*/
registro_t obtenerRegistro(char * nombre)
{
	int i = 0;
	registro_t registro = {NULL, NULL, 0};

	for (; listaRegistros[i].nombre != NULL; i++)
		if (!strcmp(listaRegistros[i].nombre, nombre) || !strcmp(listaRegistros[i].numero, nombre))
		{
			registro = listaRegistros[i];
			break;
		}
	
	return registro;
}

int obtenerInstruccionR(char * instruccion[], int numeroParametros, opcode_t codopt, uint32_t * opcode)
{
	int resultado = 0;
	registro_t rt, rs, rd;
	uint8_t desplazamiento = 0;

	switch (numeroParametros - 1)
	{
	case 0:
		//Si es la instrucción syscall
		if (codopt.codfunc == 0x0C)
		{
			*opcode = codopt.codfunc;
			resultado = 1;
		}
		else
			if (codopt.codfunc == 0x00) //nop
			{
				*opcode = 0;
				resultado = 1;
			}	
		break;
	case 1:
		rd = obtenerRegistro(instruccion[1]);
		if (rd.nombre != NULL)
		{
			if (codopt.codfunc == 0x08 || codopt.codfunc == 0x011 || codopt.codfunc == 0x13)
			{
				rs.codigo = rd.codigo;
				rd.codigo = 0x00;
			}
			else
				rs.codigo = 0x00;

			rt.codigo = 0x00;
			*opcode = (codopt.codopt << 26) | (rs.codigo << 21) 
					| (rt.codigo << 16) | (rd.codigo << 11) | (codopt.codfunc);
			resultado = 1;
		}
		else
			printf("Error! El registro \"%s\" no es un identificador válido de registro!\n", instruccion[1]);

		break;
	case 2:
			rs = obtenerRegistro(instruccion[1]);
			if (rs.nombre != NULL)
			{
				rt = obtenerRegistro(instruccion[2]);
				if (rt.nombre != NULL)
				{
						rd.codigo = 0x00;
						*opcode = (codopt.codopt << 26) | (rs.codigo << 21) 
									| (rt.codigo << 16) | (rd.codigo << 11) | (codopt.codfunc);
						resultado = 1;
				}
				else
					printf("Error! El registro \"%s\" no es un identificador válido de registro!\n", instruccion[2]);
			}
			else
				printf("Error! El registro \"%s\" no es un identificador válido de registro!\n", instruccion[1]);
		break;

	case 3:
		// Si es la instrucción sll, srl o sra
		if (codopt.codfunc == 0x00 || codopt.codfunc == 0x03 || codopt.codfunc == 0x02)
		{
			rd = obtenerRegistro(instruccion[1]);
			if (rd.nombre != NULL)
			{
				rt = obtenerRegistro(instruccion[2]);
				if (rt.nombre != NULL)
				{
					if (strToUINT8(instruccion[3], &desplazamiento))
					{
						rs.codigo = 0x00;
						*opcode = (codopt.codopt << 26) | (rs.codigo << 21) 
									| (rt.codigo << 16) | (rd.codigo << 11) 
									| (desplazamiento << 6) |(codopt.codfunc);
						resultado = 1;
					}
					else
						printf("Error! La cadena \"%s\" no es un número válido de 8 bits!\n", instruccion[3]);
				}
				else
					printf("Error! El registro \"%s\" no es un identificador válido de registro!\n", instruccion[2]);
			}
			else
				printf("Error! El registro \"%s\" no es un identificador válido de registro!\n", instruccion[1]);	
		}
		else
		{
			rd = obtenerRegistro(instruccion[1]);
			if (rd.nombre != NULL)
			{
				rs = obtenerRegistro(instruccion[2]);
				if (rs.nombre != NULL)
				{
					rt = obtenerRegistro(instruccion[3]);
					if (rt.nombre != NULL)
					{
						*opcode = (codopt.codopt << 26) | (rs.codigo << 21) 
												| (rt.codigo << 16) | (rd.codigo << 11) | (codopt.codfunc);
						resultado = 1;
					}
					else
						printf("Error! El registro \"%s\" no es un identificador válido de registro!\n", instruccion[3]);
				}
				else
					printf("Error! El registro \"%s\" no es un identificador válido de registro!\n", instruccion[2]);	
			}
			else
				printf("Error! El registro \"%s\" no es un identificador válido de registro!\n", instruccion[1]);
		}
		break;

	}


	return resultado;
}

/*
 * Algoritmo para los saltos.
 * A medida que obtengo las instrucciones las voy guardando en memoria.
 * Para las instrucciones que sean de salto, hago lo siguiente:

   - Encontramos una etiqueta dentro de una instruccion, pues la añadimos a la lista con el nombre,
		la direccion relativa (o efectiva, no lo se aun) en blanco y la direccion de la instruccion que la llama (otra lista enlazada). Es decir, si es la
		segunda instrucción, ponemos un 4.

   - Si encontramos una etiqueta, la buscamos en la lista y si existe modificamos la entrada poniendo la direccion relativa de salto, si no creamos la entrada en la lista.

	Al finalizar de procesar todas las lineas del codigo fuente, revisamos la lista de etiquetas y en cada etiqueta,
	hay una lista de instrucciones que necesitan la direccion de esa etiqueta, vamos a esa instruccion y ponemos
	el valor de salto.

*/

/*
 * Devuelve una instrucción de tipo I a partir
 * del array de parámetros que recibe.
*/
int obtenerInstruccionI(char * instruccion[], int numeroParametros, opcode_t codopt, uint32_t * opcode)
{
	int resultado = 0;
	registro_t rt, rs;
	uint32_t opcodeI = 0;
	uint16_t inmediato = 0;
	uint32_t direccion = 0;
	int16_t saltoRelativo = 0;
	char * desplazamiento = NULL;
	char * registro = NULL;
	
	switch (codopt.codopt)
	{
	//Operación lui
	case 0x0F:
		if (numeroParametros == 3)
		{
			rt = obtenerRegistro(instruccion[1]);
			if (rt.nombre != NULL)
			{
				if (listaVariables_buscar(&listaEtiquetasVariable, instruccion[2], &direccion))
				{
					*opcode = (codopt.codopt << 26) | (rt.codigo << 16) | ((direccion & 0xFFFF0000) >> 16);
					resultado = 1;
				}
				else
					printf("Error! No se encontró la etiqueta \"%s\"\n", instruccion[2]);
			}
		}
		else
			printf("Error! Número de parámetros incorrecto!\n");
		break;
	//Operación sb
	case 0x28:
	//Operación sw
	case 0x2B:
	//Operación lb
	case 0x20:
	//Operación lw
	case 0x23:
		rt = obtenerRegistro(instruccion[1]);
		if (rt.nombre != NULL)
		{
			desplazamiento = (char *) malloc(strlen(instruccion[2]) + 1);
			if (desplazamiento != NULL)
			{
				registro = (char *) malloc(strlen(instruccion[2]) + 1);
				if (registro != NULL)
				{
					obtenerRegistroYDesplazamiento(instruccion[2], desplazamiento, registro);

					rs = obtenerRegistro(registro);
					if (rs.nombre != NULL)
					{
						if (strToUINT16(desplazamiento, &inmediato))
						{
							*opcode = (codopt.codopt << 26) | (rs.codigo << 21) 
												| (rt.codigo << 16) | inmediato;
							resultado = 1;
						}
						else
							printf("Error! La cadena \"%s\" no es un número válido de 16 bits!\n", desplazamiento);
					}
					else
						printf("Error! El registro \"%s\" no es un identificador de registro válido!\n", registro);

					free(registro);
				}
				else
					printf("No se pudo reservar memoria para el registro!\n");

				free(desplazamiento);
			}
			else
				printf("No se pudo reservar memoria para el desplazamiento!\n");
		}
		else
			printf("Error! El registro \"%s\" no es un identificador de registro válido!\n", instruccion[1]);
		break;

	default:
		switch (numeroParametros - 1)
		{

		case 2:
			rs = obtenerRegistro(instruccion[1]);
			if (rs.nombre != NULL)
			{
				if (listaSaltos_buscar(&listaEtiquetasSalto, instruccion[2], &direccion))
				{
					saltoRelativo = (int16_t)(direccion / 4) - progBuffer.bufferUsado;

					*opcode = (codopt.codopt << 26) | (rs.codigo << 21) | (codopt.codfunc << 16) 
						| (saltoRelativo & 0x0000FFFF);
					resultado = 1;
				}
				else
				{
					listaISaltos_insertar(&listaInstruccionesSaltoDesconocido, instruccion[2], progBuffer.bufferUsado);
					*opcode = (codopt.codopt << 26) | (rs.codigo << 21) | (codopt.codfunc << 16);
					resultado = 1;
				}
			}
			else
				printf("Error! El registro \"%s\" no es un identificador de registro válido!\n", instruccion[1]);
			break;
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
						if (listaSaltos_buscar(&listaEtiquetasSalto, instruccion[3], &direccion))
						{
							saltoRelativo = (int16_t)(direccion / 4) - progBuffer.bufferUsado;
							*opcode = (codopt.codopt << 26) | (rs.codigo << 21) 
											| (rt.codigo << 16) | (saltoRelativo & 0x0000FFFF);
							resultado = 1;
						}
						else
						{
							listaISaltos_insertar(&listaInstruccionesSaltoDesconocido, instruccion[3], progBuffer.bufferUsado);
							*opcode = (codopt.codopt << 26) | (rs.codigo << 21) 
											| (rt.codigo << 16);
							resultado = 1;
						}
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
							if (listaVariables_buscar(&listaEtiquetasVariable, instruccion[3], &direccion))
							{
								inmediato = (uint16_t)direccion & 0x0000FFFF;
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


int obtenerInstruccionJ(char * instruccion[], int numeroParametros, opcode_t codopt, uint32_t * opcode)
{
	int resultado = 0;
	uint32_t opcodeJ = 0;
	int32_t direccionSalto = 0;

	if (numeroParametros == 2)
	{
		//Comprobar con esSalto la etiqueta de salto
		if (esEtiquetaSalto(instruccion[1]))
		{
			if (listaSaltos_buscar(&listaEtiquetasSalto, instruccion[1], &direccionSalto))
			{
				*opcode = (codopt.codopt << 26) | (0x03FFFFFF & direccionSalto);
				resultado = 1;
			}
			else
			{
				listaISaltos_insertar(&listaInstruccionesSaltoDesconocido, instruccion[1], progBuffer.bufferUsado);
				*opcode = (codopt.codopt << 26) | (0x00000000);
				resultado = 1;
			}
		}
		else
			printf("Error! La etiqueta de salto \"%s\" contiene caracteres inválidos!\n", instruccion[1]);
	}

	return resultado;
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
		switch (codopt.tipo)
		{
			case 'R':
				return obtenerInstruccionR(instruccion, numeroParametros, codopt, opcode);
			case 'I':
				return obtenerInstruccionI(instruccion, numeroParametros, codopt, opcode);
			case 'J':
				return obtenerInstruccionJ(instruccion, numeroParametros, codopt, opcode);
		}		
	}
}


