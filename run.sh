#!/bin/bash

g++ main.cpp -o main

for i in `seq 1 10`;
do
    ./main tests/uf20-01.cnf > tests/runs/teste$i.txt
done
