#!/bin/sh
valgrind --leak-check=full --show-reachable=yes -v ./mas prog4.asm -o prog4.bin
#valgrind --leak-check=full --show-reachable=yes -v ./mips prog2.bin
