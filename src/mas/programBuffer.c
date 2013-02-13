#include <programBuffer.h>
#include <malloc.h>


//Usar la estructura buffer_t
void buffer_init(uint32_t * buffer)
{
	buffer = (uint32_t *) realloc(buffer, DEFAULT_SIZE * sizeof(uint32_t));
	if (buffer == NULL)
		printf("Error! No se pudo reservar memoria para el buffer del programa!\n");
	else
	{

	}
}


void buffer_free(uint32_t * buffer)
{
	free(buffer);
}


