/*
 *    File: syscalls.h
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

#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>

/* Puede que solo haya 12 */
#define SYS_PRINT_INTEGER	1
#define SYS_READ_INTEGER	5
#define SYS_EXIT			10
#define SYS_PRINT_CHAR		11
#define SYS_READ_CHAR		12

void print_integer(uint32_t i);
void read_integer(uint32_t * i);
void print_char(uint32_t c);
void read_char(uint32_t * c);

#endif