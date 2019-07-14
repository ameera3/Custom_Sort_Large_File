#include "MinHeap.hpp"
#include "MinHeapNode.hpp"

// Constructor: Builds a heap from a given array a[] 
// of given size 
MinHeap::MinHeap(MinHeapNode a[], int size)
{
	heapSize = size;
	heapArray = a; // store address of array 
	int i = (heapSize - 1) / 2;
	while (i >= 0)
	{
		minHeapify(i);
		i--;
	}
}

// A recursive method to heapify a subtree with root 
// at given index. This method assumes that the 
// subtrees are already heapified 
void MinHeap::minHeapify(int j)
{
	int l = left(j);
	int r = right(j);
	int smallest = j;
	if (l < heapSize && heapArray[l].sNum < heapArray[j].sNum)
		smallest = l;
	if (r < heapSize && heapArray[r].sNum < heapArray[smallest].sNum)
		smallest = r;
	if (smallest != j)
	{
		exchange(&heapArray[j], &heapArray[smallest]);
		minHeapify(smallest);
	}
}

int MinHeap::left(int j) 
{ 
	return (2 * j + 1); 
}

int MinHeap::right(int j) 
{ 
	return (2 * j + 2); 
}

MinHeapNode MinHeap::getRoot() 
{ 
	return heapArray[0]; 
}

void MinHeap::replaceRoot(MinHeapNode n)
{
	heapArray[0] = n;
	minHeapify(0);
}

void MinHeap::exchange(MinHeapNode* a, MinHeapNode* b) 
{
	MinHeapNode temp = *a;
	*a = *b;
	*b = temp;
}

