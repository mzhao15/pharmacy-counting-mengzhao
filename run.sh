#!/bin/bash
# script to compile and execute a C program

module load gcc
gcc -o counting.out ./src/pharmacy_counting.c
./counting.out
rm counting.out
