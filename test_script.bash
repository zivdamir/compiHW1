#!/bin/bash
flex scanner.lex
g++ -std=c++17 lex.yy.c hw1.cpp -o hw1.out
 
#compile our code
for i in {1..22}
do 
    ./hw1.out<outsourced/td$i.in>test_results/td$i.out 
done