/*
 *    File: cadenas.h
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
int esEtiquetaSalto(const char * linea);
int esVariable(const char * linea);

#endif