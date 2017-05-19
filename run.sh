#!/bin/bash

g++ sa.cpp -o sa -O2

for i in `seq 1 10`;
do
    ./sa inputs/uf250-01.cnf > tests/runs/teste$i.txt
    echo $i
done
