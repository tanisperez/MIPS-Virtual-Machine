/*
 *    File: ensamblador.h
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

#ifndef ENSAMBLADOR_H
#define ENSAMBLADOR_H

#include <elf.h>

#define MAX_LINEA 1000

#define MAX_TROZOS 100
#define TROZOS_UTILES 4

#define MAX_FALLOS 7

#define SECCION_NULL	0
#define SECCION_TEXT	1
#define SECCION_DATA	2

void ensamblarArchivo(char * archivo, char * destino);

#endif
