.data
	N: .dword 2147483647
	cadena: .asciiz "holaaa\n"
	cadena2: .asciiz "adios"

.text
inicio:
	lui $a0, cadena
	ori $a0, $a0, cadena
	addi $v0, $v0, 4
	syscall

	lui $a0, cadena2
	ori $a0, $a0, cadena2
	syscall
