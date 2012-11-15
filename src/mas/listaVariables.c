#include <listaVariables.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

var_list_t * primero = NULL;
var_list_t * ultimo = NULL;

/*
 * Función insertarVariable.
 * Añade una variable con su nombre como identificador y su direccion de memoria
 * a la lista enlazada.
*/
void insertarVariable(char * variable, uint32_t direccionPuntero)
{
	var_list_t * temp = (var_list_t*) malloc(sizeof(var_list_t));

	if (temp == NULL)
	{
		printf("malloc() error! No se pudo reservar memoria!\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		temp->siguiente = NULL;
		temp->direccionPuntero = direccionPuntero;
		temp->nombreVariable = (char*)malloc(strlen(variable) + 1);
		if (temp->nombreVariable == NULL)
		{
			printf("malloc() error! No se pudo reservar memoria!\n");
			exit(EXIT_FAILURE);
		}
		else 
		{
			strncpy(temp->nombreVariable, variable, strlen(variable));

			if (primero == NULL)
			{
				primero = temp;
				ultimo = temp;
			}
			else
			{
				ultimo->siguiente = temp;
				ultimo = temp;
			}
		}	
	}
}

/*
 * Función vaciarLista.
 * Libera de memoria la lista enlazada.
*/
void vaciarLista()
{
	var_list_t * lista = primero;
	var_list_t * temp = NULL;

	while (lista != NULL)
	{
		temp = lista;
		lista = lista->siguiente;

		if (temp->nombreVariable != NULL)
			free(temp->nombreVariable);

		free(temp);
	}
}


/*
 * Función buscarVariable.
 * Busca una variable en la lista enlazada, si existe devuelve 
 * un 0, en caso contrario devuelve un número distinto de 0.
 * Si existe, cambia el valor de direccionPuntero al de la variable.
*/
int buscarVariable(char * variable, uint32_t * direccionPuntero)
{
	int result = 0;
	var_list_t * lista = primero;

	while (lista != NULL)
	{
		result = !strcmp(lista->nombreVariable, variable);

		if (result)
		{
			*direccionPuntero = lista->direccionPuntero;
			break;
		}
		else
			lista = lista->siguiente;
	}
	
	return result;
}


