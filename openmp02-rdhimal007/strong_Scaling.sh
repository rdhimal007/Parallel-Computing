#!/bin/bash

THREADS=(1 2 4 8 16)
# problem size constant for strong scaling
PROBLEM_SIZE=1000000 

echo "Threads,Time" > strong_Scaling.csv

for T in "${THREADS[@]}"; do
    export OMP_NUM_THREADS=$T
    echo -n "$T," >> strong_Scaling.csv
    { time ./openmp02 $PROBLEM_SIZE ; } 2>&1 | grep real | awk '{print $2}' >> strong_Scaling.csv
done
