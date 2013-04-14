/*
 *    File: cadenas.c
 *	  Incluye una serie de funciones para operar con cadenas.
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

#include "cadenas.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

/* Prototipos de funciones privadas */
void * obtenerWordPtr(char * cadena);
void * obtenerDWordPtr(char * cadena);
void * obtenerFloatPtr(char * cadena);
void * obtenerAsciizPtr(char * cadena);

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
	return match(linea, "^[_a-z][0-9a-z_]+:");
}


/*
 * Fúnción: esEtiquetaSalto.
 * Determina si una etiqueta de salto, dentro de una
 * instrucción es válida.
*/
int esEtiquetaSalto(const char * linea)
{
	return match(linea, "^[_a-z][0-9a-z_]+");
}


/*
 * Función: esVariable.
 * Determina si una cadena es un identificador de variable válido.
*/
 int esVariable(const char * linea)
 {
 	return match(linea, "^[a-z][0-9a-z_]*:");
 }


/* Declaramos un array con los tipos de datos que soporta el ensamblador,
 * el tamaño de cada tipo y la función a ejecutar para parsear el dato
 */
tipos_dato_t tipos[] = {
	{".word", 	TYPE_WORD,		sizeof(uint16_t),	obtenerWordPtr},
	{".dword",	TYPE_DWORD,		sizeof(uint32_t),	obtenerDWordPtr},
	{".float", 	TYPE_FLOAT,		sizeof(float), 		obtenerFloatPtr},
	{".asciiz",	TYPE_ASCIIZ,	sizeof(char),		obtenerAsciizPtr},
	{NULL,		TYPE_NULL,		0, 					NULL}
};


/*
 * Función: obtenerPunteroADato.
 * Recibe en tipo una cadena con el tipo de dato (.word, .float, etc...),
 * en cadena almacena el dato como string y en tamaño se va a guardar el tamaño
 * que ocupa dicha variable.
 * La función devuelve un puntero de tipo void * que apunta a la variable convertida
 * a su formato adecuado.
*/
void * obtenerPunteroADato(const char * tipo, char * cadena, uint32_t * tam)
{
	int i = 0;
	void * temp = NULL;

	for (; tipos[i].nombre != NULL; i++)
	{
		if (strcmp(tipos[i].nombre, tipo) == 0)
		{
			

			if (tipos[i].obtenerVar != NULL)
			{
				temp = tipos[i].obtenerVar(cadena);

				if (tipos[i].flag == TYPE_ASCIIZ)
					*tam = strlen((char*)temp) + 1;
				else
					*tam = tipos[i].tam;

				return temp;
			}
			else
			{
				printf("Función sin implementar para el tipo de datos: %s\n", tipos[i].nombre);
				break;
			}
		}
	}

	return NULL;
}

/*
 * Función: obtenerWordPtr.
 * Devuelve un puntero a una variable de tipo
 * uint16_t (Word) a partir de una cadena de texto.
*/
void * obtenerWordPtr(char * cadena)
{
	static uint16_t temp = 0;

	if (sscanf(cadena, "%d", &temp) == 1)
		return &temp;
	else
		return NULL;
}

/*
 * Función: obtenerDWordPtr.
 * Devuelve un puntero a una variable de tipo
 * uint32_t (DWord) a partir de una cadena de texto.
*/
void * obtenerDWordPtr(char * cadena)
{
	static uint32_t temp = 0;

	if (sscanf(cadena, "%ld", &temp) == 1)
		return &temp;
	else
		return NULL;
}

/*
 * Función: obtenerFloatPtr.
 * Devuelve un puntero a una variable de tipo
 * float a partir de una cadena de texto.
*/
void * obtenerFloatPtr(char * cadena)
{
	static float temp = 0;

	if (sscanf(cadena, "%f", &temp) == 1)
		return &temp;
	else
		return NULL;
}

/*
 * Función: obtenerAsciizPtr.
 * Devuelve un puntero a un array de caracteres
 * a partir de una cadena de texto.
*/
void * obtenerAsciizPtr(char * cadena)
{
	int i = 0;
	static char temp[100];
	memset(temp, 0, 100);

	cadena[strlen(cadena) - 1] = '\0';
	++cadena;

	while (*cadena != '\0' && i < 100)
	{
		if (*cadena == '\\' && *(cadena+1) == 'n')
		{
			temp[i] = '\n';
			i += 2;
			cadena += 2;
		}
		else 
		{
			temp[i++] = *cadena;
			cadena++;
		}
	}

	temp[i] = '\0';

	return &temp;
}


/*
 * Función: obtenerRegistroYDesplazamiento.
 * A partir de una cadena del tipo 4($a0), la separa, y copia el desplazamiento
 * y el registro indicado.
*/
int obtenerRegistroYDesplazamiento(char * cadena, char * desplazamiento, char * registro)
{
	char * temp = strtok(cadena, " (\t\n");
	if (temp != NULL)
		strcpy(desplazamiento, temp);
	else
		return 0;

	if ((temp = strtok(NULL, " )\t\n")) != NULL)
		strcpy(registro, temp);
	else
		return 0;

	return 1;
}