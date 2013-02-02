#ifndef VM_H
#define VM_H

#include <stdint.h>

typedef struct registers{
	int32_t zero, at;
	int32_t v0, v1;
	int32_t a0, a1, a2, a3;
	int32_t t0, t1, t2, t3, t4, t5, t6, t7, t8, t9;
	int32_t s0, s1, s2, s3, s4, s5, s6, s7;
	int32_t k0, k1;
	int32_t gp, sp, fp, ra;
} registers_t;

void interpretarArchivo(char * archivo);

#endif