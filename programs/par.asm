.data
	texto1: .asciiz "Comprobación de paridad\n"
	texto2: .asciiz "Introduce un número: "
	msg_par: .asciiz "El número que introduciste es par\n"
	msg_impar: .asciiz "El número que introduciste es impar\n"

.text
inicio:
	addi $v0, $v0, 4 # v0 = 4
	lui $a0, texto1 
	ori $a0, $a0, texto1 # a0 = [texto1]
	syscall # print_string

	lui $a0, texto2 
	ori $a0, $a0, texto2 # a0 = [texto2]
	syscall

	addi $v0, $v0, 1 # v0 = 5
	syscall # read_integer

	addi $t0, $t0, 2 # $t0 = 2
	div $v0, $t0 # $LO = $v0 / $t0; $HI = $v0 % $t0
	mfhi $t0 # $t0 = $v0 % $t0
	bne $t0, $zero, impar

	lui $a0, msg_par
	ori $a0, $a0, msg_par
	j fin

impar:
	lui $a0, msg_impar
	ori $a0, $a0, msg_impar

fin:
	xor $v0, $v0, $v0 # $v0 = 0
	addi $v0, $v0, 4 # $v0 = 4
	syscall