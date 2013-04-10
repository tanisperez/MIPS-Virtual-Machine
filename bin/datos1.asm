.data
	N: .word 4
	arrayA: .float 1.0, 2.0, 3.0, 4.0
	head1: .asciiz "Hello"
	N2: .word 9

.text
inicio:
	addi $t1, $t1, 14
	addi $t2, $t2, 8
	sub $t3, $t1, $t2
	lui $a0, N2
	ori $a0, $a0, N2
	lw $t4, 0($a0)
	lui $a1, head1
	ori $a1, $a1, head1
	lb $t5, 1($a1)
fin:
