.PHONY: all clean strong_Scaling weak_Scaling

all: openmp02

openmp02: openmp02.cc
	g++ -fopenmp openmp02.cc -o openmp02

strong_Scaling:
	bash strong_Scaling.sh

weak_Scaling:
	bash weak_Scaling.sh

clean:
	rm -f openmp02
