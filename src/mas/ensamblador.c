#include <ensamblador.h>
#include <stdio.h>
#include <cadenas.h>
#include <mips.h>
#include <programBuffer.h>
#include <saltos.h>

/* Funciones privadas */
void generarBinario(char * destino);
int escribirInstruccionBuffer(char * instruccion[], int numeroParametros, int numeroLinea, buffer_t * b);
void procesarCodigoFuente(FILE * source, char * destino);

/* Variables globales */
saltos_list_t listaEtiquetasSalto;
i_saltos_list_t listaInstruccionesSaltoDesconocido;
buffer_t progBuffer;

/*
 * Función generarBinario.
 * Recibe un buffer y la ruta destino y se encarga
 * de crear ese fichero con el contenido del buffer.
*/
void generarBinario(char * destino)
{
	FILE * dest = fopen(destino, "w+");
	if (dest != NULL)
	{
		fwrite(progBuffer.buffer, sizeof(uint32_t),progBuffer.bufferUsado, dest);
		fclose(dest);
	}
	else
		printf("No se pudo crear \"%s\"!\n", destino);
}


/*
 * Función escribirInstruccionBuffer.
 * Recibe una instrucción con sus parámetros y un buffer donde se va a almacenar la instrucción
 * procesada.
*/
int escribirInstruccionBuffer(char * instruccion[], int numeroParametros, int numeroLinea, buffer_t * b)
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
 * Función procesarCodigoFuente.
 * Recibe por parámetro del handler del fichero código fuente
*/
void procesarCodigoFuente(FILE * source, char * destino)
{
	static char linea[MAX_LINEA];
	char * trozos[MAX_TROZOS];
	unsigned int numeroTrozos = 0, numLinea = 1;
	unsigned int ok = 1, numFallos = 0;

	buffer_init(&progBuffer);
	listaSaltos_crear(&listaEtiquetasSalto);
	listaISaltos_crear(&listaInstruccionesSaltoDesconocido);

	while(fgets(linea, MAX_LINEA, source) != NULL)
	{
		quitarSaltoLinea(linea);
		quitarComentarios(linea);
		minusculas(linea);
		
		if (esSalto(linea))
		{
			//añadir linea
			listaSaltos_insertar(&listaEtiquetasSalto, linea, progBuffer.bufferUsado << 2);
			//printf("Salto! en %.8x\n", b.bufferUsado << 2);
		}
		else
		{
			vaciarTrozos(trozos, MAX_TROZOS);
			numeroTrozos = trocearCadena(linea, trozos, MAX_TROZOS);

			if (numeroTrozos > 0)
			{
				if (numeroTrozos <= TROZOS_UTILES)
				{
					if (!(escribirInstruccionBuffer(trozos, numeroTrozos, numLinea, &progBuffer)))
					{
						ok = 0;
						if ((numFallos++) == MAX_FALLOS)
							break;
					}
				}
				else
					printf("Línea %d: Error! \"%s\" no es una instrucción válida!\n", numLinea, linea);
			}
		}
		numLinea++;
		
	}

	if (ok)
		generarBinario(destino);	
	
	listaSaltos_mostrar(&listaEtiquetasSalto);
	listaISaltos_mostrar(&listaInstruccionesSaltoDesconocido);

	listaSaltos_vaciar(&listaEtiquetasSalto);
	listaISaltos_vaciar(&listaInstruccionesSaltoDesconocido);
	buffer_free(&progBuffer);
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
		procesarCodigoFuente(source, destino);

		fclose(source);
	}
	else
		printf("No se pudo abrir \"%s\"!\n", archivo);
}
