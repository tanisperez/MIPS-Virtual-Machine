/*
 *    File: ensamblador.c
 *	  Se encarga de abrir el archivo de código fuente, ir procesando
 *	  todas las instrucciones y guardar el código máquina resultante en
 *    un archivo.
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
 */

#include "ensamblador.h"
#include <stdio.h>
#include "cadenas.h"
#include "mips.h"
#include "programBuffer.h"
#include "dataBuffer.h"
#include "saltos.h"
#include "variables.h"

/* Funciones privadas */
void generarBinario(char * destino);
void recorrerListaInstruccionesSaltoDesconocido();
int escribirInstruccionBuffer(char * instruccion[], int numeroParametros, int numeroLinea, buffer_t * b);
void procesarCodigoFuente(FILE * source, char * destino);

/* Variables globales */
saltos_list_t listaEtiquetasSalto;
i_saltos_list_t listaInstruccionesSaltoDesconocido;
variables_list_t listaEtiquetasVariable;
buffer_t progBuffer;
data_buffer_t dataBuffer;
uint8_t tipoSeccion;

/*
 * Función generarBinario.
 * Recibe un buffer y la ruta destino y se encarga
 * de crear ese fichero con el contenido del buffer.
*/
void generarBinario(char * destino)
{
	Elf32_Ehdr elf_header;
	Elf32_Phdr prog_header;

	FILE * dest = fopen(destino, "w+");
	if (dest != NULL)
	{
		/* 
			http://en.wikipedia.org/wiki/Executable_and_Linkable_Format
			http://www.ouah.org/RevEng/x430.htm
			http://linux.die.net/include/elf.h
			http://man7.org/linux/man-pages/man5/elf.5.html 
		*/
		elf_header.e_ident[EI_MAG0] = ELFMAG0;
		elf_header.e_ident[EI_MAG1] = ELFMAG1;
		elf_header.e_ident[EI_MAG2] = ELFMAG2;
		elf_header.e_ident[EI_MAG3] = ELFMAG3;

		elf_header.e_type = ET_EXEC;						/* Object file type */
		elf_header.e_machine = EM_MIPS_RS3_LE; 				/* MIPS R3000 little-endian */
		elf_header.e_version = EV_CURRENT;					/* Object file version */
		elf_header.e_entry = sizeof(Elf32_Ehdr) +			/* Virtual Entry Point */
				sizeof(Elf32_Phdr);
		elf_header.e_phoff = sizeof(Elf32_Ehdr); 			/* Program header table file offset */
		elf_header.e_shoff = 0; 							/* Section header table file offset */
		elf_header.e_flags = EF_MIPS_ARCH_2; 				/* Processor-specific flags */
		elf_header.e_ehsize = sizeof(Elf32_Ehdr);			/* Elf elf_header size in bytes */
		elf_header.e_phnum = 1 + (dataBuffer.bufferUsado > 0);	/* Program header table entry count */
		elf_header.e_phentsize = sizeof(Elf32_Phdr) 		/* Program header table entry size */
				* elf_header.e_phnum;		
		elf_header.e_shentsize = 0;							/* Section header table entry size */
		elf_header.e_shnum = 0;								/* Section header table entry count */
		elf_header.e_shstrndx = 0;							/* Section header string table index */

		fwrite(&elf_header, sizeof(Elf32_Ehdr), 1, dest);

		prog_header.p_type = PT_LOAD;						/* Segment type */
		prog_header.p_offset = sizeof(Elf32_Ehdr);			/* Segment file offset */
		prog_header.p_vaddr	= sizeof(Elf32_Ehdr) + 			/* Segment virtual address */
				sizeof(Elf32_Phdr) * elf_header.e_phnum;
		prog_header.p_paddr	= sizeof(Elf32_Ehdr) +			/* Segment physical address */
				sizeof(Elf32_Phdr) * elf_header.e_phnum;
		prog_header.p_filesz = progBuffer.bufferUsado * 4;	/* Segment size in file */
		prog_header.p_memsz = progBuffer.bufferUsado * 4;	/* Segment size in memory */
		prog_header.p_flags = PF_X | PF_R;					/* Segment flags */
		prog_header.p_align = 0;							/* Segment alignment */

		fwrite(&prog_header, sizeof(Elf32_Phdr), 1, dest);

		if (dataBuffer.bufferUsado > 0)
		{
			prog_header.p_type = PT_NOTE;
			prog_header.p_offset = sizeof(Elf32_Ehdr) + sizeof(Elf32_Phdr);
			prog_header.p_vaddr += prog_header.p_filesz;
			prog_header.p_paddr += prog_header.p_filesz;
			prog_header.p_filesz = dataBuffer.bufferUsado;
			prog_header.p_memsz = dataBuffer.bufferUsado;
			prog_header.p_flags = PF_R;
			prog_header.p_align = 0;

			fwrite(&prog_header, sizeof(Elf32_Phdr), 1, dest);
		}

		fwrite(progBuffer.buffer, sizeof(uint32_t), progBuffer.bufferUsado, dest);
		
		if (dataBuffer.bufferUsado > 0)
			fwrite(dataBuffer.buffer, dataBuffer.bufferUsado, 1, dest);
		fclose(dest);
	}
	else
		printf("No se pudo crear \"%s\"!\n", destino);
}


/*
 * Función recorrerListaInstruccionesSaltoDesconocido.
 * Recorre la lista de saltos que tiene la dirección de salto
 * sin establecer y la calcula.
*/
void recorrerListaInstruccionesSaltoDesconocido()
{
	uint8_t codopt = 0;
	uint32_t opcode = 0;
	int32_t direccionSalto = 0;
	i_saltos_t * l = listaInstruccionesSaltoDesconocido.primero;
	i_saltos_t * temp = NULL;

	while (l != NULL)
	{
		opcode = progBuffer.buffer[l->posicionInstruccion];
		codopt = (uint8_t)(opcode >> 26);

		switch (codopt)
		{
			case 0x01:
			case 0x04:
			case 0x05:
			case 0x06:
			case 0x07:
				if (listaSaltos_buscar(&listaEtiquetasSalto, l->etiquetaSalto, &direccionSalto))
				{
					progBuffer.buffer[l->posicionInstruccion] = (opcode & 0xFFFF0000) | 
						((int16_t)(direccionSalto / 4) - l->posicionInstruccion);
				}
				else
					printf("Error crítico!\n");
				break;
			case 0x02:
				if (listaSaltos_buscar(&listaEtiquetasSalto, l->etiquetaSalto, &direccionSalto))
					progBuffer.buffer[l->posicionInstruccion] = (codopt << 26) | (0x03FFFFFF & direccionSalto);
				else
					printf("Error crítico!\n");
				break;
		}

		l = l->siguiente;
	}
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
		#ifdef DEBUG
			printf("Instrucción: %s, Opcode: %.8x\n", instruccion[0], opcode);
		#endif
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
	unsigned int i = 0;
	unsigned int numeroTrozos = 0, numLinea = 1;
	unsigned int ok = 1, numFallos = 0;

	void * dato = NULL;
	uint32_t tam = 0;

	buffer_init(&progBuffer);
	data_buffer_init(&dataBuffer);
	listaSaltos_crear(&listaEtiquetasSalto);
	listaISaltos_crear(&listaInstruccionesSaltoDesconocido);
	listaVariables_crear(&listaEtiquetasVariable);
	tipoSeccion = SECCION_NULL;

	while(fgets(linea, MAX_LINEA, source) != NULL)
	{
		quitarComentarios(linea);
		minusculas(linea);

		vaciarTrozos(trozos, MAX_TROZOS);
		numeroTrozos = trocearCadena(linea, trozos, MAX_TROZOS);
		if (numeroTrozos > 0)
		{
			if (strcmp(trozos[0], ".text") == 0)
				tipoSeccion = SECCION_TEXT;
			else
				if (strcmp(trozos[0], ".data") == 0)
					tipoSeccion = SECCION_DATA;
				else
				{
					switch (tipoSeccion)
					{
						case SECCION_NULL:
							printf("Línea %d: Error! Sintaxis no reconocida, recuerde declarar las secciones!\n", numLinea);
							break;
						case SECCION_TEXT:
							if (esSalto(trozos[0]))
							{
								listaSaltos_insertar(&listaEtiquetasSalto, trozos[0], progBuffer.bufferUsado * 4);
							}
							else
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
									printf("Línea %d: Error! \"%s\" no es una instrucción válida!\n", numLinea, trozos[0]);
							}
							break;
						case SECCION_DATA:
								if (esVariable(trozos[0]) && numeroTrozos >= 3)
								{
									listaVariables_insertar(&listaEtiquetasVariable, trozos[0], dataBuffer.bufferUsado);
									for (i = 2; i < numeroTrozos; i++)
									{
										dato = obtenerPunteroADato(trozos[1], trozos[i], &tam);
										if (dato != NULL)
										{
											data_buffer_write(&dataBuffer, dato, tam);
										}
										else
											printf("Error, no se pudo obtener el puntero al dato\n");
									}
								}
								else
									printf("Línea %d: Error! \"%s\" no es un identificador de variable válido!\n", numLinea, trozos[0]);
							break;
					}
				}	
		}

		numLinea++;		
	}

	recorrerListaInstruccionesSaltoDesconocido();

	if (ok)
		generarBinario(destino);

	listaSaltos_vaciar(&listaEtiquetasSalto);
	listaISaltos_vaciar(&listaInstruccionesSaltoDesconocido);
	listaVariables_vaciar(&listaEtiquetasVariable);

	buffer_free(&progBuffer);
	data_buffer_free(&dataBuffer);
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
