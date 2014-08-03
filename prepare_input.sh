#!/bin/bash

# Oh, dear user,
# beware this is my first bash script at all.
# If you find this to be unportable, curse me not,
# for I am running this under MinGW which is punishment enough.

fname="input.txt"

rm $fname

for i in {1..100};
do
	fni="ccin"$i".txt"
	fullfni="ccin_coords/"$fni
	if [ -f $fullfni ];
	then
		echo $i >> $fname
		echo `grep "^$i " ccin_coords/radius.txt | cut -f 2 -d " "` >> $fname
		cat $fullfni >> $fname
		printf '\n' >> $fname
	fi
done
