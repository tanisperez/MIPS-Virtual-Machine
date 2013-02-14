#include <ensamblador.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <mips.h>
#include <programBuffer.h>

/* Funciones privadas */
void generarBinario(buffer_t * b, char * destino);
void procesarArchivo(FILE * source, char * destino);
void vaciarTrozos(char * trozos[], int maxTrozos);
unsigned int trocearCadena(char * cadena, char * trozos[], int MaxTrozos);
void minusculas(char * string);
void quitarComentarios(char * string);
int escribirInstruccion(char * instruccion[], int numeroParametros, int numeroLinea, buffer_t * b);


/*
 * Función escribirInstruccion.
 * Recibe una instrucción con sus parámetros y un buffer donde se va a almacenar la instrucción
 * procesada.
*/
int escribirInstruccion(char * instruccion[], int numeroParametros, int numeroLinea, buffer_t * b)
{
	uint32_t opcode = 0;

	if (obtenerInstruccion(instruccion, numeroParametros, &opcode))
	{
		printf("Instrucción: %s, Opcode: %.8x\n", instruccion[0], opcode);
		buffer_addOpcode(b, opcode);

		return 1;
	}
	else
	{
		printf("Línea %d: Error! Sintaxis incorrecta!\n", numeroLinea);
		return 0;
	}
} 


/*
 * Función minusculas.
 * Convierte a minúsculas la cadena pasada por parámetro
*/
void minusculas(char * string)
{
	for (; *string != '\0'; *string++ = tolower(*string));
}


/*
 * Función quitarComentarios.
 * Recibe una cadena de texto y reemplaza los "#" por caracteres
 * nulos, para que signifique que la cadena termina ahí y no
 * lea el comentario el ensamblador.
*/
void quitarComentarios(char * string)
{
	while (*string != '\0')
	{
		if (*string == '#')
			*string = '\0';
		else
			string++;
	}
}


/*
 * Función trocearCadena.
 * Recibe por parámetro una cadena de texto. Trocea la cadena, quitando
 * los espacios, comas y saltos de línea y guarda los pedazos en trozos[] según
 * un número máximo de maxTrozos.
 * Devuelve el número de trozos en los que se partió la cadena.
*/
unsigned int trocearCadena(char * cadena, char * trozos[], int maxTrozos)
{
	int i = 1;

	if ((trozos[0] = strtok(cadena," ,\t\n")) == NULL)
		return 0;
	
	while (i < maxTrozos && (trozos[i] = strtok(NULL," ,\t\n")) != NULL)
		i++;

	return i;
}


/*
 * Función vaciarTrozos.
 * Recibe un array de punteros a caracteres y un número máximo de trozos.
 * Establece a NULL cada trozo.
*/
void vaciarTrozos(char * trozos[], int maxTrozos)
{
	int i = 0;
	for (; i < maxTrozos; i++)
		trozos[i] = NULL;
}


/*
 * Función generarBinario.
 * Recibe un buffer y la ruta destino y se encarga
 * de crear ese fichero con el contenido del buffer.
*/
void generarBinario(buffer_t * b, char * destino)
{
	FILE * dest = fopen(destino, "w+");
	if (dest != NULL)
	{
		fwrite(b->buffer, sizeof(uint32_t), b->bufferUsado, dest);
		fclose(dest);
	}
	else
		printf("No se pudo crear \"%s\"!\n", destino);
}


/*
 * Función procesarArchivo.
 * Recibe por parámetro del handler del fichero código fuente
*/
void procesarArchivo(FILE * source, char * destino)
{
	buffer_t b;
	static char linea[MAX_LINEA];
	char * trozos[MAX_TROZOS];
	unsigned int numeroTrozos = 0, numLinea = 1;
	unsigned int ok = 1, numFallos = 0;

	buffer_init(&b);

	while(fgets(linea, MAX_LINEA, source) != NULL)
	{
		quitarComentarios(linea);
		minusculas(linea);

		vaciarTrozos(trozos, MAX_TROZOS);
		numeroTrozos = trocearCadena(linea, trozos, MAX_TROZOS);

		if (numeroTrozos > 0)
		{
			if (numeroTrozos <= TROZOS_UTILES)
			{
				if (!(escribirInstruccion(trozos, numeroTrozos, numLinea, &b)))
				{
					ok = 0;
					if ((numFallos++) == MAX_FALLOS)
						break;
				}
			}
			else
				printf("Línea %d: Error! \"%s\" no es una instrucción válida!\n", numLinea, linea);
		}
		numLinea++;
	}

	if (ok)
		generarBinario(&b, destino);	

	buffer_free(&b);
}


/*
 * Función ensamblarArchivo.
 * Recibe por parámetro la ruta del código fuente y el
 * nombre del fichero destino que se va a ensamblar.
*/
void ensamblarArchivo(char * archivo, char * destino)
{
	FILE * source = fopen(archivo, "r");
	if (source != NULL)
	{
		procesarArchivo(source, destino);

		fclose(source);
	}
	else
		printf("No se pudo abrir \"%s\"!\n", archivo);
}
