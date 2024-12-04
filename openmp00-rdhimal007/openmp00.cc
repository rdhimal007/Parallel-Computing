/*
	<Roshan Dhimal>
	<Git and Github>
	<02/13/2024>
    <Time: 14:00>
	I certify that this is my work and, where appropriate, an extension of the starter code
	provided for the assignment. 
*/
#include <iostream>
#include <omp.h>
using namespace std;

int main() {
    // Set the number of threads
    omp_set_num_threads(4);
    
    // Parallel region begins here
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        // TODO: Each thread should print "Hello, World!" followed by its thread number
        #pragma omp critical
        {
        cout << "Hello, World! " << thread_id << endl;
        }
    }
    
    return 0;
}