.data
	hello:	.asciiz	"Hello World!\n"

.text
inicio:
	lui $a0, hello
	ori $a0, $a0, hello # a0 = [hello]
	addi $v0, $v0, 4 # v0 = 4
	syscall # print_string