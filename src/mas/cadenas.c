#include <cadenas.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

/*
 * Función strToUINT16.
 * Convierte una cadena de caracteres en un número de 16 bits sin signo.
 * <= Una cadena de caracteres.
 * <= La dirección de memoria de un número de 16 bits sin signo, donde
 * se va a almacenar el número convertido.
 * => Devuelve 1 si tiene éxito y 0 si no lo tiene.
*/
int strToUINT16(char * cadena, uint16_t * inmediato)
{
	int temp = 0;
	if (sscanf(cadena, "%d", &temp) == 1)
	{
		*inmediato = (uint16_t)temp;
		return 1;
	}
	else
		return 0;
}


/*
 * Función strToUINT8.
 * Convierte una cadena de caracteres en un número de 8 bits sin signo.
 * <= Una cadena de caracteres.
 * <= La dirección de memoria de un número de 8 bits sin signo, donde
 * se va a almacenar el número convertido.
 * => Devuelve 1 si tiene éxito y 0 si no lo tiene.
*/
int strToUINT8(char * cadena, uint8_t * desplazamiento)
{
	int temp = 0;
	if (sscanf(cadena, "%d", &temp) == 1)
	{
		*desplazamiento = (uint8_t)temp;
		return 1;
	}
	else
		return 0;
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
 * Función quitarSaltoLinea.
 * Elimina el salto de línea de una cadena de caracteres.
*/
void quitarSaltoLinea(char * string)
{
	if (string[strlen(string) - 1] == '\n')
		string[strlen(string) - 1] = '\0';
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
  * Función match.
  * Comprueba si coincide la cadena string con la
  * expresión regular almacenada en pattern.
  * Devuelve 1 si tiene éxito y 0 en caso contrario.
 */
int match(const char * string, char * pattern)
{
	regex_t re;
    int status;

    if (regcomp(&re, pattern, REG_EXTENDED | REG_NOSUB) != 0)
        return 0;

    status = regexec(&re, string, (size_t)0, NULL, 0);
    regfree(&re);

    if (status != 0)
        return 0;
  	else
    	return 1;
}


/*
 * Función: esSalto.
 * Determina si una línea es una etiqueta de salto válida,
 * para ello comprueba su sintaxis.
 * Una etiqueta de salto válida:
 * - No puede contener símbolos no numéricos, excepto los dos puntos al final de la cadena
 *   y la barra baja.
 * - No puede contener espacios.
 *- No puede empezar por un número.
 *
*/
int esSalto(const char * linea)
{
	return match(linea, "^[_a-z]([0-9a-z_]+):");
}


