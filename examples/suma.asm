.data
	texto1:	.asciiz	"Programa que suma dos números!\n"
	texto2: .asciiz	"Introduce un número: "
	texto3:	.asciiz "Introduce otro número: "
	texto4:	.asciiz "La suma de los dos números es: "
	salto_linea:	.asciiz "\n"

.text
	addi $v0, $v0, 4 # v0 = 4
	lui $a0, texto1
	ori $a0, $a0, texto1 # a0 = [texto1]
	syscall # print_string

	lui $a0, texto2
	ori $a0, $a0, texto2 # a0 = [texto2]
	syscall # print_string

	addi $v0, $v0, 1 # v0 = 5
	syscall # read_integer

	addi $t0, $v0, 0 # t0 = v0

	xor $v0, $v0, $v0 # v0 = 0

	addi $v0, $v0, 4 # v0 = 4
	lui $a0, texto3
	ori $a0, $a0, texto3 # a0 = [texto3]
	syscall # print_string

	addi $v0, $v0, 1 # v0 = 5
	syscall # read_integer

	addi $t1, $v0, 0 # t1 = v0

	xor $v0, $v0, $v0 # v0 = 0

	addi $v0, $v0, 4 # v0 = 4
	lui $a0, texto4
	ori $a0, $a0, texto4 # a0 = [texto4]
	syscall

	add $t2, $t0, $t1 # t2 = t0 + t1

	xor $a0, $a0, $a0 # a0 = 0
	addi $a0, $t2, 0 # a0 = t2

	addi $v0, $v0, -3 # v0 = 1
	syscall

	xor $v0, $v0, $v0 # v0 = 0

	addi $v0, $v0, 4 # v0 = 4
	lui $a0, salto_linea
	ori $a0, $a0, salto_linea # a0 = [salto_linea]
	syscall