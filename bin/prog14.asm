	j inicio
func:
	addi $t1, $t1, 1
	mthi $t1
	jr $ra
inicio:
	jal func
	addi $t2, $t2, 2
	mtlo $t2
fin:
