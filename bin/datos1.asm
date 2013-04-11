.data
	N: .word 1616
	arrayA: .float 1.0, 2.0, 3.0, 4.0
	head1: .asciiz "Hello"
	N2: .word 9

.text
inicio:
	lui $a0, N
	ori $a0, $a0, N
	lw $t0, 0($a0)
	addi $t0, $t0, -1600
	sw $t0, 0($a0)

	lui $a1, head1
	ori $a1, $a1, head1
	lb $t5, 1($a1)
	addi $t5, $t5, 1
	sb $t5, 1($a1)
fin:
