inicio:
	addi $v0, $v0, 5 # $v0 = 5
	syscall # read_integer en $v0
	addi $t0, $t0, 2 # $t0 = 2
	div $v0, $t0 # $LO = $v0 / $t0; $HI = $v0 % $t0
	mfhi $t0 # $t0 = $v0 % $t0
	beq $t0, $zero, par
	j fin
par:
	addi $a0, $a0, 1 # $a0 = 1 es par
fin:
	xor $v0, $v0, $v0 # $v0 = 0
	addi $v0, $v0, 1 # $v0 = 1
	syscall # print_integer de $a0
