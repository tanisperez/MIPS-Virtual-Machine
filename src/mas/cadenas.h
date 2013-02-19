#ifndef CADENAS_H
#define CADENAS_H

#include <stdint.h>

int strToUINT16(char * cadena, uint16_t * inmediato);
int strToUINT8(char * cadena, uint8_t * desplazamiento);

void minusculas(char * string);
void quitarComentarios(char * string);
void quitarSaltoLinea(char * string);

unsigned int trocearCadena(char * cadena, char * trozos[], int maxTrozos);
void vaciarTrozos(char * trozos[], int maxTrozos);

int match(const char * string, char * pattern);

/* Funciones expresiones regulares */
int esSalto(const char * linea);

#endif