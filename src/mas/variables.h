/*
 *    Archivo: saltos.h
 *	  Este módulo contiene los prototipos de funciones y tipos de datos empleados
 *	  en el fichero variables.c
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

#ifndef VARIABLES_H
#define VARIABLES_H

#include <stdint.h>

/* Lista de etiquetas de variables */
typedef struct variables_{
	char * etiquetaVariable;
	uint32_t direccionVariable;

	struct variables_ * siguiente;
} variables_t;

typedef struct variables_list_{
	variables_t * primero;
	variables_t * ultimo;
} variables_list_t;

/* Funciones públicas */
void listaVariables_crear(variables_list_t * lista);
void listaVariables_insertar(variables_list_t * lista, char * etiquetaVariable, uint32_t direccionVariable);
void listaVariables_vaciar(variables_list_t * lista);
void listaVariables_mostrar(variables_list_t * lista);

#endif