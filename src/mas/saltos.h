#ifndef SALTOS_H
#define SALTOS_H

#include <stdint.h>

/* Lista de etiquetas de salto conocidas */
typedef struct saltos_ {
	char * etiquetaSalto;
	int32_t direccionSalto;

	struct saltos_ * siguiente; //Puntero a la siguiente estructura
} saltos_t;

typedef struct saltos_list {
	saltos_t * primero;
	saltos_t * ultimo;
} saltos_list_t;

/* Lista de instrucciones de salto, de las que no se
   conocen su direccion de salto */
typedef struct i_saltos {
	char * etiquetaSalto; //Etiqueta de salto
	uint32_t posicionInstruccion; //Posición de la instrucción en el Buffer

	struct i_saltos * siguiente;
} i_saltos_t;

typedef struct i_saltos_list {
	i_saltos_t * primero;
	i_saltos_t * ultimo;
} i_saltos_list_t;


void listaSaltos_crear(saltos_list_t * lista);
void listaSaltos_insertar(saltos_list_t * lista, char * etiquetaSalto, int32_t direccionSalto);
void listaSaltos_vaciar(saltos_list_t * lista);
void listaSaltos_mostrar(saltos_list_t * lista);
int listaSaltos_buscar(saltos_list_t * lista, char * etiquetaSalto, int32_t * direccionSalto);


void listaISaltos_crear(i_saltos_list_t * lista);
void listaISaltos_insertar(i_saltos_list_t * lista, char * etiquetaSalto, uint32_t posicionInstruccion);
void listaISaltos_vaciar(i_saltos_list_t * lista);
void listaISaltos_mostrar(i_saltos_list_t * lista);

#endif