#!/bin/bash
# script to compile and execute a C program
declare -r color_start="\033["
declare -r color_red="${color_start}0;31m"
declare -r color_green="${color_start}0;32m"
declare -r color_blue="${color_start}0;34m"
declare -r color_norm="${color_start}0m"

module load gcc
gcc -o counting ./src/pharmacy_counting.c
./counting
rm counting
