#!/bin/bash

gcc -c -g3 cell.c;
gcc -c -g3 main.c;
gcc -g3 cell.o main.o -lm -o main;

rm -rf *.o;
