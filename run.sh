#!/bin/bash
# script to compile and execute a C program

module load gcc
gcc -o counting ./src/pharmacy_counting.c
./counting
rm counting
