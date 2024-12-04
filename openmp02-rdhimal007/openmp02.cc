/*
	<Roshan Dhimal>
	<Git and Github>
	<02/22/2024>
    <Time: 14:00>
	I certify that this is my work and, where appropriate, an extension of the starter code
	provided for the assignment. 
*/

#include <omp.h>
#include <iostream>
#include <cmath>

double f(double x) {
    return std::sin(x); // Example function to integrate
}

double trapezoidal_rule(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));

    // TODO: Use OpenMP to parallelize this loop with proper scheduling

    #pragma omp parallel for schedule(static) reduction(+:sum)
    for (int i = 1; i < n; ++i) {
        sum += f(a + i * h);
    }

    return h * sum;
}

int main() {
    double a = 0;       // Lower bound of integration
    double b = M_PI;    // Upper bound of integration
    int n = 1e6;        // Number of trapezoids

    double integral = trapezoidal_rule(a, b, n);
    std::cout << "Integral: " << integral << std::endl;

    return 0;
}