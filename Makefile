# Change the CXX variable assignment at your own risk.
CXX ?= g++ 
CXXFLAGS=-std=c++11 -g -Wall -O2
LDFLAGS=-g

all: sortme 

sortme: MinHeap.o

MinHeap.o: MinHeap.hpp MinHeapNode.hpp

clean:
	rm -f sortme MinHeap *.o core* *~


