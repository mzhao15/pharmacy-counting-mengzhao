#!/bin/bash
# script to compile and execute a C program

module load gcc/1.10.2
gcc -o counting ./src/pharmacy_counting.c
./counting
rm counting
