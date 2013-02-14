addi $v0, $v0, 5 #$v0 = 5
syscall #read_integer en $v0
add $t0, $t0, $v0 #$t0 = $v0
xor $v0, $v0, $v0 #$v0 = 0
addi $v0, $v0, 5 #$v0 = 5
syscall #read_integer en $v0
add $t1, $t1, $v0 #t1 = $v0
add $a0, $t0, $t1 #$a0 = $t0 + $t1
xor $v0, $v0, $v0 #$v0 = 0
addi $v0, $v0, 1 #$v0 = 1
syscall #print_integer de $a0
