#ifndef LISTAVARIABLES_H
#define LISTAVARIABLES_H

#include <stdint.h>

typedef struct var_list {
	struct var_list * siguiente;
	char * nombreVariable;
	uint32_t direccionPuntero;
} var_list_t;

void insertarVariable(char * variable, uint32_t direccionPuntero);
void vaciarLista();
int buscarVariable(char * variable, uint32_t * direccionPuntero);

#endif
