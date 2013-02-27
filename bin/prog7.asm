inicio:
	addi $v0, $v0, 1 # $v0 = 1
	addi $t1, $t1, 10 # $t1 = 10
	bucle:
		addi $a0, $a0, 1
		syscall # print_integer
		bne $a0, $t1, bucle
fin:
