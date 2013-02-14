#include <programBuffer.h>
#include <stdio.h>
#include <malloc.h>

/* Funciones privadas */
void buffer_realloc(buffer_t * b);

/*
 * Función buffer_init.
 * Recibe la dirección de memoria de una estructura buffer_t y
 * la inicializa. Reserva una cantidad de memoria DEFAULT_SIZE * sizeof(uint32_t),
 * cuya constante está definida en programBuffer.h.
*/
void buffer_init(buffer_t * b)
{
	if (b == NULL)
		printf("Error! Puntero nulo en buffer_init()!\n");

	b->buffer = NULL;
	b->tamBuffer = 0;
	b->bufferUsado = 0;
	b->buffer = (uint32_t *) realloc(b->buffer, DEFAULT_SIZE * sizeof(uint32_t));

	if (b->buffer != NULL)
		b->tamBuffer = DEFAULT_SIZE;
	else
		printf("Error! No se pudo reservar memoria con realloc en buffer_init()!\n");
}


/*
 * Función buffer_realloc.
 * Recibe por parámetro la dirección de memoria de una estructura buffer_t y se
 * encarga de incrementar su tamaño según la constante DEFAULT_SIZE. Esta función
 * no se puede llamar explícitamente, depende de buffer_addOpcode().
*/
void buffer_realloc(buffer_t * b)
{
	b->tamBuffer += DEFAULT_SIZE;
	b->buffer = (uint32_t *) realloc(b->buffer, DEFAULT_SIZE * sizeof(uint32_t));

	if (b->buffer == NULL)
		printf("Error! No se pudo reservar memoria con realloc en buffer_realloc()!\n");
}


/*
 * Función buffer_addOpcode.
 * Recibe por parámetro la dirección de memoria de una estructura buffer_t y
 * un número sin signo de 4 bytes, que es la operación a guardar.
 * La escribe en memoria y si necesita más memoria llama a buffer_realloc().
*/
void buffer_addOpcode(buffer_t * b, uint32_t opcode)
{
	if (b != NULL)
	{
		if (b->bufferUsado == b->tamBuffer)
			buffer_realloc(b);
		
		b->buffer[b->bufferUsado] = opcode;
		b->bufferUsado++;
	}
	else
		printf("Error! No se pudo reservar memoria con realloc en buffer_addOpcode()!\n");
}


/*
 * Función buffer_free.
 * Libera la memoria reservada de la estructura buffer_t.
*/
void buffer_free(buffer_t * b)
{
	if (b != NULL)
		free(b->buffer);
}


