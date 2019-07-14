#include<bits/stdc++.h>
#include <iostream>
#include <string.h>
#include "MinHeap.hpp"

// argv index of input file
#define IN_IDX 1 

// argv index of output file
#define OUT_IDX 2

// expected number of arguments
#define EXPECTED_ARGS 3

// number of partitions
#define PARTITIONS 110

// memory ratio
#define MEM_RATIO 100

using namespace std;

long filesize(const char* filename)
{
	FILE * pFile;
	long size;

	pFile = fopen (filename,"rb");
	if (pFile==NULL) perror ("Error opening file");
	else
	{
		fseek (pFile, 0, SEEK_END);   // non-portable
		size=ftell (pFile);
		fclose (pFile);
	}
	return size;
}

// Merges k sorted files. Names of files are assumed 
// to be 1, 2, 3, ... k 
void mergeFiles(const char *outFile, const char* inFile, int n, int k)
{
	FILE* in[k];
	for (int i = 0; i < k; i++)
	{
		char fileName[4];

		// convert i to string 
		snprintf(fileName, sizeof(fileName), "%d", i);

		// Open output files in read mode. 
		in[i] = fopen(fileName, "r");
	}

        FILE* origin = fopen(inFile, "rb");

	// FINAL OUTPUT FILE 
	FILE *out = fopen(outFile, "w");

	// Create a min heap with k heap nodes. Every heap node 
	// has first element of scratch output file 
	MinHeapNode* harr = new MinHeapNode[k];
	int i;
	for (i = 0; i < k; i++)
	{
		// break if output file is empty and 
		// index i will be no. of input files 
		if (fscanf(in[i], "%d %lu", &harr[i].sNum, &harr[i].posF) != 2)
			break;

		harr[i].arrNum = i; // Index of scratch output file 
	}
	MinHeap* hp = new MinHeap(harr, i); // Create the heap 

	int count = 0;
	char* line = nullptr;
	size_t len = 0;

	// Now one by one get the minimum element from min 
	// heap and replace it with next element. 
	// run till all filled input files reach EOF 
	while (count != i)
	{
		// Get the minimum element and store it in output file 
		MinHeapNode root = hp->getRoot();
		long fPos = root.posF;
		fseek (origin, fPos, SEEK_SET);
		getline(&line, &len, origin);
		fprintf(out, "%s", line);

		// Find the next element that will replace current 
		// root of heap. The next element belongs to same 
		// input file as the current min element. 
		if (fscanf(in[root.arrNum], "%d %lu", &root.sNum, &root.posF) != 2 )
		{
			root.sNum = INT_MAX;
			count++;
		}

		// Replace root with next element of input file 
		hp->replaceRoot(root);
	}

        free(line);
        delete[] harr;	

	delete hp;

	// close input and output files 
	for (int i = 0; i < k; i++)
		fclose(in[i]);

	fclose(out);
	fclose(origin);
	
}



// Merges two subarrays of arr[]. 
// First subarray is arr[l..m] 
// Second subarray is arr[m+1..r] 
void merge(std::pair<int, long> arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* dynamically allocate temp arrays */
        std::pair<int, long>* L = new std::pair<int, long>[n1];
	std::pair<int, long>* R = new std::pair<int, long>[n2];

	/* Copy data to temp arrays L[] and R[] */
	for(i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for(j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < n1 && j < n2)
	{
		if (L[i].first <= R[j].first)
			arr[k++] = L[i++];
		else
			arr[k++] = R[j++];
	}

	/* Copy the remaining elements of L[], if there 
	   are any */

	while (i < n1)
		arr[k++] = L[i++];

	/* Copy the remaining elements of R[], if there 
	   are any */
	while(j < n2)
		arr[k++] = R[j++];

        delete[] L;
	delete[] R;
}

/* l is for left index and r is right index of the 
   sub-array of arr to be sorted */
void mergeSort(std::pair<int, long> arr[], int l, int r)
{
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for 
		// large l and h 
		int m = l + (r - l) / 2;

		// Sort first and second halves 
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

std::pair<int, long> process(char * line, long position)
{
	unsigned int length = strlen(line);
	unsigned int i;
	int count = 0;
	for(i = 0; i < length; ++i) {
		if( line[i] == 's' ) {
			++count;
		}	
	}
	return std::make_pair(count, position);
}    

// Using a merge-sort algorithm, create the partitions 
// and divide them evenly among the output files 
void createPartitions(const char* inFile, int runSize, int partitions)
{
	// For big input file 
	FILE *in = fopen(inFile, "rb");

	// output scratch files 
	FILE* out[partitions];
	char fileName[4];
	for (int i = 0; i < partitions; i++)
	{
		// convert i to string 
		snprintf(fileName, sizeof(fileName), "%d", i);

		// Open output files in write mode. 
		out[i] = fopen(fileName, "w");
	}

	// number of entries in our soon to be dynamically
	// allocated array
        int numEntries = runSize/sizeof(std::pair<int, long>);

	// allocate a dynamic array large enough 
	// to accommodate partitions of size runSize 
	std::pair<int, long>* arr = new std::pair<int, long>[numEntries];

	bool moreInput = true;
	int nextOutputFile = 0;
	char* line = nullptr;
	size_t len = 0;
	long position;
	int i;

	while (moreInput)
	{
		// write run_size elements into arr from input file 
		for (i = 0; i < numEntries; i++)
		{
			position = ftell(in);

			if (getline(&line, &len, in) == -1)
			{
				moreInput = false;
				break;
			}

			std::pair<int, long> sNumfPos = process(line, position);
			arr[i] = sNumfPos;
		}

		// sort array using merge sort 
		mergeSort(arr, 0, i - 1);

		// write the records to the appropriate scratch output file 
		// can't assume that the loop runs to run_size 
		// since the last run's length may be less than run_size 
		for (int j = 0; j < i; j++)
			fprintf(out[nextOutputFile], "%d %lu ", arr[j].first, arr[j].second);

		nextOutputFile++;
	}

	free(line);
        delete[] arr;

	// close input and output files 
	for (int i = 0; i < partitions; i++)
		fclose(out[i]);

	fclose(in);

}

// For sorting data stored on disk 
void customSort(const char* inFile, const char* outFile,
		int partitions, long runSize)
{

	// read the input file, create the partitions, 
	// and assign the partitions to the temporary output files 
	createPartitions(inFile, runSize, partitions);

	// Merge the temporary output files using K-way merging 
	mergeFiles(outFile, inFile, runSize, partitions);
}

int main(int argc, char** argv) {

	//Check for Arguments
	if (argc != EXPECTED_ARGS){
		cout << "This program requires 3 arguments!" << endl;
		return -1;
	}

	long fSize = filesize(argv[IN_IDX]);
	long runSize = fSize / MEM_RATIO;
	cout << "Filesize is: " << fSize << " bytes." << endl;
	cout << "Runsize is: " << runSize << " bytes." << endl;
	customSort(argv[IN_IDX], argv[OUT_IDX], PARTITIONS, runSize);
}    	    
