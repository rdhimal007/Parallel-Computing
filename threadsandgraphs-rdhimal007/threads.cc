/*
	<Roshan Dhimal>
	<Git and Github>
	<02/08/2024>
	I certify that this is my work and, where appropriate, an extension of the starter code
	provided for the assignment. 
*/


#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <fstream>
#include <cmath>
#include <sys/stat.h>
#include <unistd.h>

// global variable for the what computer used
#define personalCom = 1;
#define superCom = 2;
#define uicSystemCom = 3;
// Function to perform quick sort (students should not modify this)
void quickSort(std::vector<int>& values, int left, int right, int depth = 0);
int partition(std::vector<int>& values, int left, int right);

int 
main(int argc, char *argv[]) 
{
    using namespace std;

    const int SIZE = 500000;
    std::vector<int> originalValues(SIZE);
    // system indentifier added to the file for analyzer
    int cmd, expCmd;
    cmd = expCmd = 0;
    cout << "What System are you using? Enter 1 => Local, 2: HPC, 3: UIC ACER ";
    cin >> cmd;
    // added layer to spefify how many times threads should run
    cout << "How many times do you want to run Experiment ";
    cin >> expCmd;

    // outfile variable for timing data
    ofstream timeData;
    // output file
    // adding the parameter in the outfile where it keeps writing data without erasing 
    timeData.open("threads.dat",ios::app); 
    // make the header for the csv or time data file
    // add clause so it doesn't repeat writing header in the file
    timeData.seekp(0, ios::end);
    if (timeData.tellp() == 0) {
      timeData << "Time,Threads,systemIndetifier\n";  
    }
    // bool emfile = fs::file_size("threads.dat") == 0;
    // if (emfile){
    //   timeData << "Time,Threads,systemIndetifier\n";  
    // }

    // Fill the vector with random integers
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, SIZE);
    for (int& value : originalValues) {
        value = distrib(gen);
    }// End of For

    int maxThreads = std::thread::hardware_concurrency();
    std::cout << "Maximum Threads: " << maxThreads << std::endl;

    // Run experiments with different thread counts (students add timing and data collection code in loop)
    for (int currentThreads = 1; currentThreads <= std::max(1, maxThreads); currentThreads *= 2) {
        // dedicated amount of experiment to run
        for(int i = 0; i < expCmd; i++){
            int depth = std::max(1, int(log2(currentThreads)));
            std::cout << "Testing with " << currentThreads << " threads (Depth: " << depth << ")\n";

            // Good idea to run a number of experiments with exactly the same data
            std::vector<int> values = originalValues;

            auto startTime = std::chrono::high_resolution_clock::now();

            // Perform quick sort (students should not modify this)
            quickSort(values, 0, SIZE - 1, depth);

            auto endTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = endTime - startTime;

            // Students write code here to collect and process timing data
            // For example: Store timing data in a data structure or file

            timeData << duration.count() <<","<< currentThreads << ","<< cmd << endl;

            std::cout << duration.count() << " seconds\n";
        }
    }// End of FOR looping over thread pools 

    // close the open file
    timeData.close();

    return 0;
}// End of MAIN

// Quick Sort Algorithm (students should not modify this)
void quickSort(std::vector<int>& values, int left, int right, int depth) {
    if (left < right) {
        int pivotIndex = partition(values, left, right);

        if (depth > 0) {
            std::thread leftThread(quickSort, std::ref(values), left, pivotIndex - 1, depth - 1);
            quickSort(values, pivotIndex + 1, right, depth - 1);
            leftThread.join();
        } else {
            quickSort(values, left, pivotIndex - 1, 0);
            quickSort(values, pivotIndex + 1, right, 0);
        }// End of IF / ELSE
    }// End of IF
}// End of quickSort()

// Partition function for Quick Sort (students should not modify this)
int partition(std::vector<int>& values, int left, int right) {
    int pivot = values[right];
    int i = (left - 1);

    for (int j = left; j <= right - 1; j++) {
        if (values[j] < pivot) {
            i++;
            std::swap(values[i], values[j]);
        }// End of IF
    }// End of FOR
    std::swap(values[i + 1], values[right]);
    return (i + 1);
}// End of partition()
