/*
 * Filename: MinHeap.hpp
 * Description: Implements a min heap.
 */

#ifndef MIN_HEAP_HPP
#define MIN_HEAP_HPP

#include "MinHeapNode.hpp"

/* Class Name: MinHeap
 * Instance Variables: heapArray (pointer to array representation of heap)
 *                     heapSize (number of nodes in the heap)
 * Description: Implements a min heap.
 * Public Methods: Constructor, minHeapify, left, right, getRoot, 
                   replaceRoot, exchange, destructor.
 */
class MinHeap
{
    MinHeapNode* heapArray; // pointer to array representation of heap 
    int heapSize;           // number of nodes in the heap

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

	// swaps two min heap nodes
	void exchange(MinHeapNode* a, MinHeapNode* b);

	// destructor
	~MinHeap();
};

#endif // MIN_HEAP_H
