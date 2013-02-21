#include <saltos.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

/***************************************************************************************************
 ***************************************************************************************************
 ************ Funciones para manejar la lista de saltos conocidos **********************************
 ***************************************************************************************************
 **************************************************************************************************/

/*
 * Función listaSaltos_crear.
 * Inicializa la estructura saltos_list_t.
*/
void listaSaltos_crear(saltos_list_t * lista)
{
	if (lista == NULL)
	{
		printf("listaSaltos_crear error! Puntero nulo!\n");
		exit(EXIT_FAILURE);
	}
	
	lista->primero = NULL;
	lista->ultimo = NULL;
}


/*
 * Función listaSaltos_insertar.
 * Inserta una etiqueta de salto y la dirección en la que se encuentra
 * dicha etiqueta en la lista de saltos.
*/
void listaSaltos_insertar(saltos_list_t * lista, char * etiquetaSalto, int32_t direccionSalto)
{
	saltos_t * temp = (saltos_t*) malloc(sizeof(saltos_t));

	if (temp == NULL)
	{
		printf("listaSaltos_insertar() error! No se pudo reservar memoria!\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		temp->siguiente = NULL;
		temp->direccionSalto = direccionSalto;
		temp->etiquetaSalto = (char *) malloc(strlen(etiquetaSalto));
		if (temp->etiquetaSalto == NULL)
		{
			printf("listaSaltos_insertar() error! No se pudo reservar memoria!\n");
			exit(EXIT_FAILURE);
		}
		else 
		{
			strcpy(temp->etiquetaSalto, etiquetaSalto);
			temp->etiquetaSalto[strlen(etiquetaSalto) - 1] = '\0';
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
 * Función listaSaltos_vaciar.
 * Vacía y libera la memoria dinámica reservada de la
 * lista de saltos.
*/
void listaSaltos_vaciar(saltos_list_t * lista)
{
	saltos_t * l = lista->primero;
	saltos_t * temp = NULL;

	while (l != NULL)
	{
		temp = l;
		l = l->siguiente;

		if (temp->etiquetaSalto != NULL)
			free(temp->etiquetaSalto);

		free(temp);
	}
}


/*
 * Función listaSaltos_mostrar.
 * Muestra todas las etiquetas de saltos con sus direcciones de salto
 * que haya almacenadas en la lista.
*/
void listaSaltos_mostrar(saltos_list_t * lista)
{
	saltos_t * l = lista->primero;
	saltos_t * temp = NULL;

	while (l != NULL)
	{
		temp = l;
		l = l->siguiente;

		if (temp->etiquetaSalto != NULL)
			printf("Salto \"%s\" en %.8x\n", temp->etiquetaSalto, temp->direccionSalto);
	}
}



/*
 * Función listaSaltos_buscar.
 * Buscar en la lista una etiqueta de salto, si tiene éxito,
 * guarda la dirección de salto en el puntero direccion y devuelve 1.
 * En caso contrario devuelve 0.
*/
int listaSaltos_buscar(saltos_list_t * lista, char * etiqueta, int32_t * direccion)
{
	saltos_t * l = lista->primero;
	saltos_t * temp = NULL;

	while (l != NULL)
	{
		temp = l;
		l = l->siguiente;

		if (strcmp(temp->etiquetaSalto, etiqueta) == 0)
		{
			*direccion = temp->direccionSalto;
			return 1;	
		}
	}

	return 0;
}



/***************************************************************************************************
 ***************************************************************************************************
 ************ Funciones para manejar la lista de instrucciones con saltos desconocidos *************
 ***************************************************************************************************
 **************************************************************************************************/


/*
 * Función listaISaltos_crear.
 * Inicializa la estructura i_saltos_list_t.
*/
void listaISaltos_crear(i_saltos_list_t * lista)
{
	if (lista == NULL)
	{
		printf("listaSaltos_crear error! Puntero nulo!\n");
		exit(EXIT_FAILURE);
	}
	
	lista->primero = NULL;
	lista->ultimo = NULL;
}


/*
 * Función listaISaltos_insertar.
 * Inserta una etiqueta de salto y la dirección en la que se encuentra
 * dicha etiqueta en la lista de saltos.
*/
void listaISaltos_insertar(i_saltos_list_t * lista, char * etiquetaSalto, uint32_t posicionInstruccion)
{
	i_saltos_t * temp = (i_saltos_t*) malloc(sizeof(i_saltos_t));

	if (temp == NULL)
	{
		printf("listaSaltos_insertar() error! No se pudo reservar memoria!\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		temp->siguiente = NULL;
		temp->posicionInstruccion = posicionInstruccion;
		temp->etiquetaSalto = (char *) malloc(strlen(etiquetaSalto));
		if (temp->etiquetaSalto == NULL)
		{
			printf("listaSaltos_insertar() error! No se pudo reservar memoria!\n");
			exit(EXIT_FAILURE);
		}
		else 
		{
			strcpy(temp->etiquetaSalto, etiquetaSalto);
			temp->etiquetaSalto[strlen(etiquetaSalto) - 1] = '\0';
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
 * Función listaISaltos_vaciar.
 * Vacía y libera la memoria dinámica reservada de la
 * lista de saltos.
*/
void listaISaltos_vaciar(i_saltos_list_t * lista)
{
	i_saltos_t * l = lista->primero;
	i_saltos_t * temp = NULL;

	while (l != NULL)
	{
		temp = l;
		l = l->siguiente;

		if (temp->etiquetaSalto != NULL)
			free(temp->etiquetaSalto);

		free(temp);
	}
}


/*
 * Función listaSaltos_mostrar.
 * Muestra todas las etiquetas de saltos con sus direcciones de salto
 * que haya almacenadas en la lista.
*/
void listaISaltos_mostrar(i_saltos_list_t * lista)
{
	i_saltos_t * l = lista->primero;
	i_saltos_t * temp = NULL;

	while (l != NULL)
	{
		temp = l;
		l = l->siguiente;

		if (temp->etiquetaSalto != NULL)
			printf("Etiqueta \"%s\" en %.8x\n", temp->etiquetaSalto, temp->posicionInstruccion);
	}
}
