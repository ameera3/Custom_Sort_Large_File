/* 
 * Filename: sortme.cpp
 * Usage: ./sortme FileA FileB
 * Description: The command line program named “sortme.cpp” takes in two 
 *              parameters: an input filename and an output filename
 *		i.e. Running “sortme FileA FileB” will result in reading 
 *		in FileA and output to FileB.
 *
 *              The input file specified by the input filename should be 
 *              a large text file having many lines of text. Each line of 
 *		the input file is unique. The sortme program will output 
 *		the sorted lines to the new file specified by the output 
 *		filename.
 *
 *              The sort algorithm is based off the number of occurrences 
 *              of the letter “s” on the line in ascending order. (That 
 *              is, the line with the most number of “s” occurrences 
 *              appears at the end of the output file.)
 *
 *              The input file is assumed to be 100x the amount of working 
 *              memory available to your program. (That is, if the maximum 
 *              amount of memory available to the process is 1GB, the file 
 *              is 100GB in size. Simply put, assume the entire contents 
 *              of the file cannot be stored in memory.)
 */

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

/* Returns the filesize of filename */
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
// to be 1, 2, 3, ... , k
void kWayMerge(const char *outFile, const char* inFile, int n, int k)
{
	// array of k file pointers
	FILE* scratch[k];

        // open the k files to be merged
	for (int i = 0; i < k; i++)
	{
		char fileName[4];

		// convert i to string 
		snprintf(fileName, sizeof(fileName), "%d", i);

		// Open output files in read mode. 
		scratch[i] = fopen(fileName, "r");
	}

	// original input file
        FILE* origin = fopen(inFile, "rb");

	// final output file
	FILE *out = fopen(outFile, "w");

	// Create a min heap with k heap nodes. Every heap node 
	// has first element of scratch output file 
	MinHeapNode* hpArray = new MinHeapNode[k];
	int i;
	for (i = 0; i < k; i++)
	{
		/* Read in the number of s characters and the
		 * position of the beginning of the line in the
		 * original input file to the min heap node.
		 * Break if output file is empty.  
		 * Index i is number of input files
		 */
		if (fscanf(scratch[i], "%d %lu", &hpArray[i].sNum, 
		    &hpArray[i].posF) != 2) {
			break;
                }

		// Index of scratch output file
		hpArray[i].arrNum = i;  
	}

	// Create the heap
	MinHeap* hp = new MinHeap(hpArray, i);  

	int count = 0;
	char* line = nullptr;
	size_t len = 0;

	// Get the root from the min 
	// heap and replace it with next element. 
	// run till all filled input files reach EOF 
	while (count != i)
	{
		/* Get the root from the min heap, and read in the position 
		   of the corresponding line in the original text file. Fseek 
		   to that position, get the line from the original text file, 
		   and write it to the output file.
		*/   
		MinHeapNode root = hp->getRoot();
		long fPos = root.posF;
		fseek (origin, fPos, SEEK_SET);
		getline(&line, &len, origin);
		fprintf(out, "%s", line);

		// Find the next element that will replace current 
		// root of heap. The next element belongs to same 
		// input file as the current min element. 
		if (fscanf(scratch[root.arrNum], "%d %lu", &root.sNum, 
					&root.posF) != 2 )
		{
			root.sNum = INT_MAX;
			count++;
		}

		// Replace root with next element of input file 
		hp->replaceRoot(root);
	}

	// no memory leaks here
        free(line);
        delete[] hpArray;	
	delete hp;

	// close input and output files 
	for (int i = 0; i < k; i++)
		fclose(scratch[i]);

	fclose(out);
	fclose(origin);
	
}

/* Merges two subarrays of arr[]. 
 * First subarray is arr[l..m] 
 * Second subarray is arr[m+1..r]
 */
void merge(std::pair<int, long> arr[], int l, int m, int r)
{
	int i, j, k;
	
	// size of left subarray
	int n1 = m - l + 1;

	// size of right subarray
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
		// sort according to the number of "s" characters
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

	// no memory leaks here
        delete[] L;
	delete[] R;
}

/* Recursive mergeSort algorithm for array
 * l is for left index and r is right index of the 
 * sub-array of arr to be sorted 
 */
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

/* Counts the number of "s" characters in a line and
 * returns a pair consisting of the number of "s"
 * characters in the line along with the position of
 * the beginning of the line in the original input file.
 */
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
// and divide them among the output files 
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
			// position of the beginning of the line
			// in the original input file
			position = ftell(in);
                        
                        // if we reach EOF in the original input
			// file, then break
			if (getline(&line, &len, in) == -1)
			{
				moreInput = false;
				break;
			}

			// process the line and store the pair
			// consisting of its number of s characters
			// and its position in the array
			std::pair<int, long> sNumfPos = process(line, position);
			arr[i] = sNumfPos;
		}

		// sort array using merge sort 
		mergeSort(arr, 0, i - 1);

		// write the records to the appropriate scratch output file 
		// can't assume that the loop runs to run_size 
		// since the last run's length may be less than run_size 
		for (int j = 0; j < i; j++)
			fprintf(out[nextOutputFile], "%d %lu ", arr[j].first, 
					arr[j].second);
                
		// move to the next scratch output file when you have filled 
		// the current one
		nextOutputFile++;
	}

	// no memory leaks here
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
	kWayMerge(outFile, inFile, runSize, partitions);
}

// Main Driver
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
