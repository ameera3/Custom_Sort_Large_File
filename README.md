# Custom_Sort_Large_File

## Usage:
To compile, type make. To run the program, type "sortme FileA File B". 

## Introduction.
The command line program named “sortme.cpp” takes in two parameters: an input filename and an output filename.

i.e. Running “sortme FileA FileB” will result in reading in FileA and output to FileB.

The input file specified by the input filename should be a large text file having many lines of text. Each line of the input 
file is unique. The sortme program will output the sorted lines to the new file specified by the output filename.

The sort algorithm should be based off the number of occurrences of the letter “s” on the line in ascending order. 
(That is, the line with the most number of “s” occurrences should appear at the end of the output file.)

Assume the input file is of 100x the amount of working memory available to your program. (That is, if the maximum amount 
of memory available to the process is 1GB, the file is 100GB in size. Simply put, assume you will not be able to store 
the entire contents of the file in memory.)

## Testing
You can test sortme on the file mylog.txt. This file has a line consisting of 80 's' characters, followed by a line 
consisting of 79 's' characters, all the way down to 1 's' character. The pattern continues for the characters, 'a'-'g'.

The output of sortme should first contain the lines of mylog.txt with the characters 'a' through 'g' in any order. It should 
then have the line consisting of 1 's' character, followed by the line consisting of 2 's' characters, all the way up to the
line containing 80 's' characters.

There is also a handy filesize program that lets you check the size of your files. You will have to compile it separately
with g++ -o filesize filesize.cpp. Typing "./filesize filename" outputs the size of the file.

Finally, there is also a handy bash script autoremove.sh that removes all your temporary scratch files. Remember to 
chmod u+x autoremove.sh and then type ./autoremove.sh to remove the temporary scratch files.
