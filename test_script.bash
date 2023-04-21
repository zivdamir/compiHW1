#!/bin/bash
flex scanner.lex
g++ -std=c++17 lex.yy.c hw1.cpp -o hw1.out
 
#compile our code
for i in {1..57}
do 
    ./hw1.out<tests/input/t$i.in>tests/output/t$i.out 
    diff tests/output/t$i.out tests/expected/t$i.out
done