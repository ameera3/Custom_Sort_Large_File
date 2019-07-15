#!/bin/bash
# Filename: autoremove.sh
# Description: Removes the temporary scratch files 
#              created by sortme.
# Usage: ./autoremove.sh

for i in {0..109}
do
	rm $i
done


