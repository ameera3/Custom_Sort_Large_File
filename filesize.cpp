/* Filename: filesize.cpp
 * Description: Returns the filesize of filename
 * Usage: ./filesize filename
 */
#include <stdio.h>

int main (int argc, char** argv)
{
	FILE * pFile;
	long size;

	pFile = fopen (argv[1],"rb");
	if (pFile==NULL) perror ("Error opening file");
	else
	{
		fseek (pFile, 0, SEEK_END);   // non-portable
		size=ftell (pFile);
		fclose (pFile);
		printf ("Size of file: %ld bytes.\n",size);
	}
	return 0;
}
