.data
	mensaje: .asciiz "Hola!"

.text
inicio:
	addi $v0, $v0, 4
	lui $a0, mensaje
	ori $a0, $a0, mensaje
	syscall
