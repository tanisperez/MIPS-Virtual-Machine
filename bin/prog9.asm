inicio:
	addi $t0, $t0, 100
	bltz $t0, menor
	j fin
menor:
	addi $t1, $t1, 1
fin:
