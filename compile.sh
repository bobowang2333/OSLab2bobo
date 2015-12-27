#!/bin/bash
gcc -o main main.c share.c
gcc -o get get.c share.c 
gcc -o copy copy.c share.c 
gcc -o put put.c share.c
