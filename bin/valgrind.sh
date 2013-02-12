#!/bin/sh
./mas prog2.asm -o prog2.bin
valgrind --leak-check=full --show-reachable=yes -v ./mips prog2.bin
