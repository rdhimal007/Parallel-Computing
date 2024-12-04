# Makefile for QuickSort with Threads

# Compiler settings - Can change to your preferred compiler (e.g., g++, clang++)
CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2 -pthread

# Target executable name
TARGET = threads

# Source files
SRC = threads.cc

# Build rule
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Clean rule
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: clean
