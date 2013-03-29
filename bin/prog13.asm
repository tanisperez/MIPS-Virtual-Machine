inicio:
	addi $t1, $t1, -1
	bgezal $t1, mayor
	bltzal $t1, menor
	j fin
mayor:
	addi $t2, $t2, 1
menor:
	addi $t3, $t3, 1
fin:
