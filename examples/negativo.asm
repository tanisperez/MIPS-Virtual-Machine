.data
	texto1:	.asciiz	"Comprueba si un número es negativo!\n"
	texto2:	.asciiz "Introduce un número: "
	texto3:	.asciiz "El número que introduciste es negativo!\n"
	texto4: .asciiz "El número que introduciste es positivo!\n"

.text
	j inicio

	# Función que imprime una cadena de texto. La dirección de la 
	# cadena a imprimir está en $a0.
	print_string:
		xor $v0, $v0, $v0 # v0 = 0
		addi $v0, $v0, 4 # v0 = 4
		syscall # print_string

		jr $ra

	# Almacena en $v0 un número entero leído por teclado
	read_integer:
		xor $v0, $v0, $v0 # v0 = 0
		addi $v0, $v0, 5 # v0 = 1
		syscall # read_integer

		jr $ra

	# Finaliza la ejecución del programa
	exit:
		xor $v0, $v0, $v0 # v0 = 0
		addi $v0, $v0, 10 # v0 = 10
		syscall # exit

	inicio:
		lui $a0, texto1
		ori $a0, $a0, texto1 # a0 = [texto1]
		jal print_string

		lui $a0, texto2
		ori $a0, $a0, texto2 # a0 = [texto2]
		jal print_string

		jal read_integer

		slt $t0, $v0, $zero # if v0 < 0 then t0 = 1 else t0 = 0
		beq $t0, $zero, positivo

		lui $a0, texto3
		ori $a0, $a0, texto3 # a0 = [texto3]
		jal print_string
		j exit

	positivo:
		lui $a0, texto4
		ori $a0, $a0, texto4 # a0 = [texto4]
		jal print_string
		j exit








