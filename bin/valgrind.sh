#!/bin/sh
valgrind --leak-check=full --show-reachable=yes -v ./mas exceptions.asm -o exceptions.elf
valgrind --leak-check=full --show-reachable=yes -v ./mips exceptions.elf
