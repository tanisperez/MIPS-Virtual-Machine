inicio:
	addi $t0, $t0, 2
	sll $t0, $t0, 2
	addi $t1, $t1, 8
	srl $t1, $t1, 2
	addi $t2, $t2, -18
	addi $t3, $t3, 1
	#sra $t2, $t2, 1
	srav $t2, $t2, $t3
fin:
