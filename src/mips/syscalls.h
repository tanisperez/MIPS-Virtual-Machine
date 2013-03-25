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