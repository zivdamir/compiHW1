#!/bin/bash
flex scanner.lex
g++ -std=c++17 lex.yy.c hw1.cpp -o hw1.out
mkdir test_results 2> /dev/null
#compile our code
for i in {1..22}
do 
    ./hw1.out</outsourced/td$i.txt>test_results/td$i_our.out 2> /dev/null
done