addi $v0, $v0, 5
syscall
add $t0, $t0, $v0
xor $v0, $v0, $v0
addi $v0, $v0, 5
syscall
add $t1, $t1, $v0
add $a0, $t0, $t1
xor $v0, $v0, $v0
addi $v0, $v0, 1
syscall
