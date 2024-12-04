[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/JdG5Y00g)
# C++ OpenMP Hello World Assignment

## Objective
Learn the basics of parallel programming in C++ using the OpenMP library. Write a program that utilizes multiple threads to print "Hello, World!" from each thread. You can use the systems{1-4}.cs.uic.edu or extreme.acer.uic.edu systems. If you use the CS machines, there is no waiting in the queue. If you use ACER resource, you need a PBS script to submit; don't run on the login node - that is frowned upon. You will also need to make sure you have the correct modules loaded.

## Starter Code
Below is the starter code for your assignment. Your task is to complete the missing part of the code.

```c++
#include <omp.h>
#include <iostream>

int main() {
    // Set the number of threads
    omp_set_num_threads(4);
    
    // Parallel region begins here
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        // TODO: Each thread should print "Hello, World!" followed by its thread number
    }
    
    return 0;
}
```

## Instructions

1. Ensure you have a C++ compiler and OpenMP installed on your system.
2. Complete the code inside the parallel block. Each thread should print "Hello, World!" followed by its thread number.
3. Compile the code using a command like `g++ -fopenmp openmp00.cc -o openmp00` (or build a Makefile).
4. Run the compiled program and observe the output. The order of the output might change with each execution due to the nature of parallel execution.

## Expected Learning Outcome

Gaining an understanding of fundamental parallel programming concepts and developing proficiency in employing OpenMP directives to establish parallel regions.
