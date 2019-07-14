# Custom_Sort_Large_File

## Usage.
To compile, type make. To run the program, type "./sortme FileA File B". 

## Introduction.
The command line program named “sortme.cpp” takes in two parameters: an input filename and an output filename.

i.e. Running “sortme FileA FileB” will result in reading in FileA and output to FileB.

The input file specified by the input filename should be a large text file having many lines of text. Each line of the input 
file is unique. The sortme program will output the sorted lines to the new file specified by the output filename.

The sort algorithm is based off the number of occurrences of the letter “s” on the line in ascending order. 
(That is, the line with the most number of “s” occurrences appears at the end of the output file.)

The input file is assumed to be 100x the amount of working memory available to your program. (That is, if the maximum amount 
of memory available to the process is 1GB, the file is 100GB in size. Simply put, assume the entire contents of the file cannot be stored in memory.)

## Algorithm.

Dynamically allocate an array that has size 1% of the size of the original input file. For each line in the original text file, store in the array the number of "s" characters in that line as well as the position in the file where the line begins. When the array is full, sort it using merge sort according to the number of "s" characters. Next, write the sorted array to a scratch file. Repeat this process until each line of the original text file has been processed. There are 110 scratch files just in case.

Finally, use a min heap to perform a k-way merge, where k is the number of scratch files to be merged. Create a min heap with k heap nodes. Every heap node contains the first element of its corresponding scratch file. Get the root from the min heap, and read in the position of the corresponding line in the original text file. Fseek to that position, get the line from the original text file, and write it to the output file. Replace the root of the min heap with the next element and reheapify. Repeat until all scratch files reach EOF.

## Testing.
You can test sortme on the file mylog.txt. This file has a line consisting of 80 "s" characters, followed by a line 
consisting of 79 "s" characters, all the way down to 1 "s" character. The pattern continues for the characters, "a"-"g".

The output of sortme should first contain the lines of mylog.txt with the characters "a" through "g" in any order. It should 
then have the line consisting of 1 "s" character, followed by the line consisting of 2 "s" characters, all the way up to the
line containing 80 "s" characters.

There is also a handy filesize program that lets you check the size of your files. You will have to compile it separately
with g++ -o filesize filesize.cpp. Typing "./filesize filename" outputs the size of the file in bytes.

Finally, there is also a handy bash script autoremove.sh that removes all your temporary scratch files. Remember to 
chmod u+x autoremove.sh and then type ./autoremove.sh to remove the temporary scratch files.
