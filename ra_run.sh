#!/bin/bash

g++ random_search.cpp -o rs -O2

for i in `seq 1 10`;
do
    ./rs inputs/uf250-01.cnf > tests/runs/teste$i.txt
    echo $i
done
