inicio:
	addi $t0, $t0, 1
	bgez $t0, mayor
	j fin

mayor:
	addi $a0, $a0, 1

fin:
