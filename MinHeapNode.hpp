#ifndef MIN_HEAP_NODE_HPP
#define MIN_HEAP_NODE_HPP
using namespace std;

class MinHeapNode
{
	public:

		/* number of s's in line */    
		int sNum;

		/* index of array containing line information */
		int arrNum;

		/* fseek position of beginning of line */
		long posF;

		/* Constructor */

		MinHeapNode() :
			sNum(0), arrNum(0), posF(0) {}


};

#endif // MIN_HEAP_NODE_HPP



