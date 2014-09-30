#!/bin/bash

if [ "$#" -ne 3 ]; then
	echo "Usage: combine.sh INPUTFILE1 INPUTFILE2 OUTPUTFILE"
	exit
fi

cp $1 $3
cat $2 | awk '{print $1, 3.1415926535897932384626433832795-$2, $3}' >> $3