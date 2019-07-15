/* Filename: MinHeapNode.hpp
 * Description: Implements a MinHeap node.
 */

#ifndef MIN_HEAP_NODE_HPP
#define MIN_HEAP_NODE_HPP
using namespace std;

/* Class Name: MinHeapNode
 * Instance Variables: sNum (number of s's in line represented by node)
                       arrNum (index of scratch file containing line info)
		       posF (fseek position of beginning of line)
 * Public Methods: Constructor
 */

class MinHeapNode
{
	public:

		/* number of s's in line */    
		int sNum;

		/* index of scratch file containing line information */
		int arrNum;

		/* fseek position of beginning of line */
		long posF;

		/* Constructor */
		MinHeapNode() :
			sNum(0), arrNum(0), posF(0) {}


};

#endif // MIN_HEAP_NODE_HPP



