.data
	texto1: .asciiz "Serie de Fibonacci!\n"
	texto2: .asciiz "Introduce el número de la serie que deseas calcular (n < 49): "
	texto3: .asciiz "Fib(n) = "
	salto_linea:	.asciiz	"\n"

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
	addi $t2, $v0, 0 # t2 = v0
	addi $v0, $v0, -2 # v0 = v0 - 2

	#Empieza el algoritmo

	bltz $v0, resultado # Si v0 < 0 devolver n

	xor $t0, $t0, $t0 # t0 = 0
	addi $t1, $t1, 1 # t1 = 1

	addi $v0, $v0, 1
	bucle:
		add $t2, $t0, $t1 # t2 = t0 + t1
		
		xor $t0, $t0, $t0
		addi $t0, $t1, 0 # t0 = t1

		xor $t1, $t1, $t1
		addi $t1, $t2, 0 # t1 = t2

		addi $v0, $v0, -1 # v0--
		bne $v0, $zero, bucle # mientras v0 != 0 saltar a bucle


resultado:
	xor $v0, $v0, $v0
	addi $v0, $v0, 4 # v0 = 4
	lui $a0, texto3
	ori $a0, $a0, texto3 # a0 = [texto3]
	syscall # print_string

	addi $v0, $v0, -3 # vo = 1
	xor $a0, $a0, $a0
	addi $a0, $t2, 0 # a0 = t2
	syscall # print_integer

	xor $v0, $v0, $v0
	addi $v0, $v0, 4 # v0 = 4
	lui $a0, salto_linea
	ori $a0, $a0, salto_linea # a0 = [salto_linea]
	syscall # print_string
