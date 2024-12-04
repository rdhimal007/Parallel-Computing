#!/bin/bash

# Base problem size for 1 thread
BASE_PROBLEM_SIZE=1000000 

echo "Threads,Time" > weak_Scaling.csv

for T in 1 2 4 8 16; do
    PROBLEM_SIZE=$(($BASE_PROBLEM_SIZE * $T))
    export OMP_NUM_THREADS=$T
    echo -n "$T," >> weak_Scaling.csv
    { time ./openmp02 $PROBLEM_SIZE ; } 2>&1 | grep real | awk '{print $2}' >> weak_Scaling.csv
done
