/*
 *    Archivo: variables.c
 *	  Este módulo contiene las funciones para operar con listas enlazadas
 *	  que almacenan las etiquetas de variables.
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

#include "variables.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


/*
 * Función listaVariables_crear.
 * Inicializa la estructura variables_list_t.
*/
void listaVariables_crear(variables_list_t * lista)
{
	if (lista == NULL)
	{
		printf("listaVariables_crear error! Puntero nulo!\n");
		exit(EXIT_FAILURE);
	}
	
	lista->primero = NULL;
	lista->ultimo = NULL;
}


/*
 * Función listaVariables_insertar.
 * Inserta una etiqueta de salto y la dirección en la que se encuentra
 * dicha etiqueta en la lista de saltos.
*/
void listaVariables_insertar(variables_list_t * lista, char * etiquetaVariable, uint32_t direccionVariable)
{
	variables_t * temp = (variables_t*) malloc(sizeof(variables_t));

	if (temp == NULL)
	{
		printf("listaVariables_insertar() error! No se pudo reservar memoria!\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		temp->siguiente = NULL;
		temp->direccionVariable = direccionVariable;
		temp->etiquetaVariable = (char *) malloc(strlen(etiquetaVariable) + 1);
		if (temp->etiquetaVariable == NULL)
		{
			printf("listaVariables_insertar() error! No se pudo reservar memoria!\n");
			exit(EXIT_FAILURE);
		}
		else 
		{
			strcpy(temp->etiquetaVariable, etiquetaVariable);
			temp->etiquetaVariable[strlen(etiquetaVariable) - 1] = '\0';
			if (lista->primero == NULL)
			{
				lista->primero = temp;
				lista->ultimo = temp;
			}
			else
			{
				lista->ultimo->siguiente = temp;
				lista->ultimo = temp;
			}
		}	
	}
}


/*
 * Función listaVariables_vaciar.
 * Vacía y libera la memoria dinámica reservada de la
 * lista de variables.
*/
void listaVariables_vaciar(variables_list_t * lista)
{
	variables_t * l = lista->primero;
	variables_t * temp = NULL;

	while (l != NULL)
	{
		temp = l;
		l = l->siguiente;

		if (temp->etiquetaVariable != NULL)
			free(temp->etiquetaVariable);

		free(temp);
	}
}


/*
 * Función listaVariables_mostrar.
 * Muestra todas las etiquetas de variable con las direcciones
 * de memoria a la que apuntan.
*/
void listaVariables_mostrar(variables_list_t * lista)
{
	variables_t * l = lista->primero;
	variables_t * temp = NULL;

	while (l != NULL)
	{
		temp = l;
		l = l->siguiente;

		if (temp->etiquetaVariable != NULL)
			printf("Variable \"%s\" en %.8x\n", temp->etiquetaVariable, temp->direccionVariable);
	}
}