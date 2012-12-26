#include <saltos.h>
#include <ensamblador.h>
#include <string.h>
#include <ctype.h>

/*
 * Crear una función esSalto que compruebe si una línea de un 
 * archivo de código fuente es una etiqueta de salto válida.
 *
*/


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
int esSalto(char * linea)
{
	int result = 0, i = 1;
	char * salto = strtok(linea, " ,\t\n");

	if (salto != NULL)
	{
		//Primero comprobamos que termina en ":" y
		// que no empieza por un número. 
		if (strlen(salto) > 1
			&& salto[strlen(salto) - 1] == ':'
			&& !isdigit(salto[0]))
		{
			for (; i < strlen(salto); i++)
			{
				//Comprobar caracteres a..z
				if (salto[i] == '_' || isdigit(salto[i]) || isalpha(salto[i]))
					result = 1;
				else
					break;
			}
		}
	}

	return result;
}


void buscarDireccionesSalto(FILE * source)
{
 	static char linea[MAX_LINEA];

 	while(fgets(linea, MAX_LINEA, source) != NULL)
 	{
 		if (esSalto(linea))
 		{
 			printf("Se encontró un salto: %s\n", linea);
 		}

 	}
}