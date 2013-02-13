#include <syscalls.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

extern void liberarPrograma();

/* Syscall 1 */
void print_integer(uint32_t i)
{
	printf("%d", i);
}

/* Syscall 5 */
void read_integer(uint32_t * i)
{
	char buff[100];

	if (fgets(buff, 100, stdin) != NULL && i != NULL)
	{
		buff[strlen(buff) - 1] = '\0';
		if (sscanf(buff, "%d", i) != 1)
			printf("Error! \"%s\" no es un número entero!\n", buff); //¿Exception?
	}
	else
		printf("syscall read_integer error! Error en la entrada de datos!\n");
}

/* Syscall 10 */
void exit1(uint32_t * byteCode)
{
	liberarPrograma();
}


/* Syscall 11 */
void print_char(uint32_t c)
{
	putchar(c);
}

/* Syscall 12 */
void read_char(uint32_t * c)
{
	*c = getchar();
}