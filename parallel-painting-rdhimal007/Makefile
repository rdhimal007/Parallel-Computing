# Makefile for Mandelbrot set generation
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Target executable name
TARGET = mandelbrot

# Source files
SOURCES = mandelbrot.cc

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# To start over from scratch
clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
