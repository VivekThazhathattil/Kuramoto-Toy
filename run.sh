#!/bin/bash

gcc -c cell.c;
gcc -c main.c;
gcc cell.o main.o -o main;

rm -rf *.o;
