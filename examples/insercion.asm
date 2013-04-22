# Programa que ordena datos almacenados en memoria mediante el algoritmo
# de ordenación por inserción.
.data
	vector:	.word 4, 9, 13, -5, 18, 32, 45, -14, 882
	n: .word 9 # N contiene el número de elementos que hay en el vector

	texto1: .asciiz "Algoritmo de ordenación por Inserción!\n"
	texto2: .asciiz "Vector desordenado: "
	separador: .asciiz ", "
	salto_linea: .asciiz ";\n"
	texto3: .asciiz "Vector ordenado: "

.text
	j inicio

	# Función que imprime una cadena de texto. La dirección de la 
	# cadena a imprimir está en $a0.
	print_string:
		xor $v0, $v0, $v0 # v0 = 0
		addi $v0, $v0, 4 # v0 = 4
		syscall # print_string

		jr $ra

	# Función que imprime un entero almacenado en $a0.
	print_integer:
		xor $v0, $v0, $v0 # v0 = 0
		addi $v0, $v0, 1 # v0 = 1
		syscall # print_integer

		jr $ra

	# Recibe la posición del vector en $s0.
	# Obtiene el valor en $s1.
	get_i:
		lui $a1, vector
		ori $a1, $a1, vector

		sll $s0, $s0, 1 # multiplicamos por 2
		add $a1, $a1, $s0

		lw $s1, 0($a1)

		jr $ra

	# Recibe la posición del vector en $s0 y el
	# valor a escribir en $s1
	set_i:
		lui $a1, vector
		ori $a1, $a1, vector

		sll $s0, $s0, 1 # multiplicamos por 2
		add $a1, $a1, $s0

		sw $s1, 0($a1)

		jr $ra

	inicio:
		lui $a0, texto1
		ori $a0, $a0, texto1 # a0 = [texto1]
		jal print_string

		lui $a0, texto2
		ori $a0, $a0, texto2 # a0 = [texto2]
		jal print_string

		lui $a1, N
		ori $a1, $a1, N # a1 = [N]
		lw $t0, 0($a1) # t0 = N

		lui $a1, vector
		ori $a1, $a1, vector # a1 = [vector]

		xor $t1, $t1, $t1 # t1 = 0

		bucle:
			lw $a0, 0($a1) # v0 = a1[0]
			jal print_integer
			addi $a1, $a1, 2 # Incrementamos el puntero base

			addi $t1, $t1, 1

			beq $t0, $t1, fin_bucle

			lui $a0, separador
			ori $a0, $a0, separador # a0 = [separador]
			jal print_string

			bne $t0, $t1, bucle

		fin_bucle:

		lui $a0, salto_linea
		ori $a0, $a0, salto_linea # a0 = [salto_linea]
		jal print_string

		# Ordenación por inserción

		# t1 = i
		# t2 = j
		# t4 = x

		xor $t1, $t1, $t1
		addi $t1, $t1, 1

		xor $t2, $t2, $t2

		for:
			slt $t3, $t1, $t0 # t3 = t1 < N
			beq $t3, $zero, finfor
				xor $s0, $s0, $s0 # s0 = 0
				addi $s0, $t1, 0 # s0 = t1
				jal get_i # s1 = vector[t1]

				xor $t4, $t4, $t4 # t4 = 0
				addi $t4, $s1, 0 # t4 = s1

				xor $t2, $t2, $t2
				addi $t2, $t1, -1 # t2 = t1 - 1

				while:
					bltz $t2, fin_while # if t2 >= 0 then fin_while

					xor $s0, $s0, $s0 # s0 = 0
					addi $s0, $t2, 0 # s0 = t2
					jal get_i # s1 = vector[t2]

					slt $t3, $s1, $t4
					beq $t3, $zero, fin_while # if vector[t2] < t4 then fin_while

					xor $s0, $s0, $s0 # s0 = 0
					addi $s0, $t2, 1 # s0 = t2 + 1
					jal set_i

					addi $t2, $t2, -1 # t2--

					j while
				fin_while:

				xor $s1, $s1, $s1
				addi $s1, $t4, 0 # s1 = t4

				xor $s0, $s0, $s0 # s0 = 0
				addi $s0, $t2, 1 # s0 = t2 + 1
				jal set_i

				addi $t1, $t1, 1 # t1++
			j for
		finfor:

		lui $a0, texto3
		ori $a0, $a0, texto3 # a0 = [texto3]
		jal print_string
			
		lui $a1, vector
		ori $a1, $a1, vector # a1 = [vector]

		xor $t1, $t1, $t1 # t1 = 0

		bucle2:
			lw $a0, 0($a1) # v0 = a1[0]
			jal print_integer
			addi $a1, $a1, 2 # Incrementamos el puntero base

			addi $t1, $t1, 1

			beq $t0, $t1, fin_bucle2

			lui $a0, separador
			ori $a0, $a0, separador # a0 = [separador]
			jal print_string

			bne $t0, $t1, bucle2

		fin_bucle2:

		lui $a0, salto_linea
		ori $a0, $a0, salto_linea # a0 = [salto_linea]
		jal print_string
