#include <omp.h>
#include <iostream>
#include <vector>
#include <fstream>
int main() {
    const int SIZE = 1e6;
    std::vector<int> numbers(SIZE, 1); // Initialize all elements to 1
    int total_sum = 0;

    // make a input file 
    std::ofstream take_TimeObj;
    take_TimeObj.open("openmp01_Time.dat",std::ios::app); 
    // make the header for the csv or time data file
    // add clause so it doesn't repeat writing header in the file
    take_TimeObj.seekp(0, std::ios::end);
    if (take_TimeObj.tellp() == 0) {
      take_TimeObj << "Time,Threads\n";  
    }


    for(int num_threads = 1; num_threads <= 8; num_threads *= 2) {
        int total_sum = 0;
        // find execution time variable
        double start_time, end_time;

        omp_set_num_threads(num_threads); // Set the number of threads for this iteration
        start_time = omp_get_wtime(); // Start timing

        // Parallel region begins here
        #pragma omp parallel for reduction(+:total_sum)
        for (int i = 0; i < SIZE; i++) {
            total_sum += numbers[i];
        }
    
         end_time = omp_get_wtime(); // End timing
        std::cout << "Total sum is " << total_sum << " using " << num_threads << " threads." << std::endl;
        std::cout << "Execution time: " << (end_time - start_time) << " seconds." << std::endl;
        take_TimeObj << (end_time - start_time) << "," << num_threads<< std::endl;
    }  

    take_TimeObj.close();
    return 0;
}