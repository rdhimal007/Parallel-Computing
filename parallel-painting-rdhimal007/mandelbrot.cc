#include <iostream>
#include <fstream>
#include <complex>
#include <vector>
#include <cstdlib> // For atoi and atof
#include <cmath> // For sin function
#include <string>

#include <iostream>
#include <omp.h> // OpenMP header
// Image dimensions constants.
const int WIDTH = 1920;
const int HEIGHT = 1080;

// Parses command line arguments to customize the Mandelbrot set generation.
void parseArguments(int argc, char *argv[], int &max_iter, double &center_x, double &center_y, double &zoom, std::string &filename) {
    // Initialize with default values.
    filename = "mandelbrot.pnm"; // Default output filename.
    max_iter = 1000;             // Default maximum iterations for depth.
    center_x = -0.75;            // Default X coordinate of the center.
    center_y = 0.0;              // Default Y coordinate of the center.
    zoom = 1.0;                  // Default zoom level.

    // Loop through arguments to set parameters.
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        // Filename argument.
        if (arg == "-f" && i + 1 < argc) {
            filename = argv[++i];
            // Append ".pnm" if the filename doesn't end with it.
            if (filename.size() < 4 || filename.substr(filename.size() - 4) != ".pnm") {
                filename += ".pnm";
            }
        }
        // Maximum iterations argument.
        else if (arg == "-i" && i + 1 < argc) {
            max_iter = std::stoi(argv[++i]);
        }
        // Center X coordinate argument.
        else if (arg == "-x" && i + 1 < argc) {
            center_x = atof(argv[++i]);
        }
        // Center Y coordinate argument.
        else if (arg == "-y" && i + 1 < argc) {
            center_y = atof(argv[++i]);
        }
        // Zoom level argument.
        else if (arg == "-z" && i + 1 < argc) {
            zoom = atof(argv[++i]);
        }
    }
}

// Computes the Mandelbrot set for a given point.
int computeMandelbrot(double real, double imag, int max_iter) {
    std::complex<double> c(real, imag); // Complex number for the current point.
    std::complex<double> z(0, 0);       // Initial complex number for iterations.
    int n = 0;

    // Iterate until |z| > 2 (escapes) or max iterations reached.
    while (abs(z) <= 2.0 && n < max_iter) {
        z = z*z + c;
        ++n;
    }

    return n; // Returns the iteration count.
}

// Maps the iteration count to an RGB color.
void mapColor(int iter, int max_iter, int &r, int &g, int &b) {
    // Set color to black if within the Mandelbrot set.
    if (iter == max_iter) {
        r = g = b = 0;
    } else {
        // Color based on iteration count using a sine function for a smooth gradient.
        double frequency = 0.1;
        r = static_cast<int>(sin(frequency * iter + 0) * 127 + 128);
        g = static_cast<int>(sin(frequency * iter + 2) * 127 + 128);
        b = static_cast<int>(sin(frequency * iter + 4) * 127 + 128);
    }
}

// Main function: generates the Mandelbrot set and writes to a file.
int main(int argc, char* argv[]) {
    // Parameters to be set by command-line arguments.
    int max_iter;
    double center_x, center_y, zoom;
    std::string filename;

    // Parse command-line arguments.
    parseArguments(argc, argv, max_iter, center_x, center_y, zoom, filename);

    // Calculate scale and translation based on zoom and center.
    double scale = 4.0 / (WIDTH * zoom);
    double move_x = center_x - WIDTH / 2.0 * scale;
    double move_y = center_y - HEIGHT / 2.0 * scale;

    // Initialize color matrices.
    std::vector<std::vector<int> > red(HEIGHT, std::vector<int>(WIDTH));
    std::vector<std::vector<int> > green(HEIGHT, std::vector<int>(WIDTH));
    std::vector<std::vector<int> > blue(HEIGHT, std::vector<int>(WIDTH));
    double start_time = omp_get_wtime();

    #pragma omp parallel for collapse(2) schedule(dynamic)
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            double real = x * scale + move_x;
            double imag = y * scale + move_y;
            int r, g, b;
            mapColor(computeMandelbrot(real, imag, max_iter), max_iter, r, g, b);
            red[y][x] = r;
            green[y][x] = g;
            blue[y][x] = b;
        }
    }
    // End timing here
    double end_time = omp_get_wtime();
    std::cout << "Execution time: " << end_time - start_time << " seconds." << std::endl;

    // Write the image to a PNM file.
    std::ofstream imageFile(filename);
    imageFile << "P3\n" << WIDTH << " " << HEIGHT << "\n255\n";
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            imageFile << red[y][x] << " " << green[y][x] << " " << blue[y][x] << "\n";
        }
    }

    // Close file and print execution details.
    imageFile.close();

    return 0;
}
