#!/bin/bash
# script to compile and execute a C program

module load gcc
gcc -o output ./src/pharmacy_counting.c
./output
rm output
