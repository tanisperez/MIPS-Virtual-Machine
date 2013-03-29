/*
 *    File: vm.h
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

#ifndef VM_H
#define VM_H

#include <stdint.h>

#define REG_COUNT 32

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
	void (*funcion)(int32_t * rs, int32_t * rt, int32_t * rd, uint8_t shamt, int16_t offset, uint32_t direction);
} opcode_t;

typedef struct reg{
	char * nombre;
	uint8_t codigo;
	int32_t * reg_pointer;
} registro_t;


/* Funciones públicas */
void interpretarArchivo(char * archivo);

#endif