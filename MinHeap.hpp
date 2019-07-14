
#ifndef MIN_HEAP_HPP
#define MIN_HEAP_HPP

#include "MinHeapNode.hpp"

// A class for Min Heap 
class MinHeap
{
    MinHeapNode* heapArray; // pointer to array representation of heap 
    int heapSize;           // size of heap 

    public:

	// Constructor  
	MinHeap(MinHeapNode a[], int size);

	// Heapify a subtree with root at given index j 
	void minHeapify(int j);

	// Get index of left child of node at index j 
	int left(int j);

	// Get index of right child of node at index j 
	int right(int j);

	// Get Root 
	MinHeapNode getRoot();

	// Replace root with new node n and heapify() new root 
	void replaceRoot(MinHeapNode n);

	void exchange(MinHeapNode* a, MinHeapNode* b);
};

#endif // MIN_HEAP_H
