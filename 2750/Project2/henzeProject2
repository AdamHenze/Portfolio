#!/bin/bash
#!ADAM HENZE/PROJECT2/CS2750
#!FILE OPERATIONS AND EXPRESSIONS FOR DATA MANIPULATION

file="$@"

if [ -f $file ]
then 
#!on good file run...
echo "File exists"
#!make copy of data source
echo "writing source copy"
#!cleanup commas
sed "s/,/ /g" $file > srccpy.txt
sed -i "s/\\$//g" srccpy.txt

#!move1
echo 'writing move 1'
sed '1 i Name Phone Jan Feb Mar' srccpy.txt > move1.txt
#! move2
echo 'writing move 2'
sed 's/Hauschild/Housechild/g' srccpy.txt > move2.txt
#!move3
echo "Writing move 3"
cat srccpy.txt | grep "(916)" | awk '{print $1 " " $2}' > move3.txt
#!move4
echo "Writing move 4"
cat srccpy.txt | grep -i "^M" | awk '{print $1}' > move4.txt
cat srccpy.txt | grep -i "^R" | awk '{print $1}' >> move4.txt
#!move5
echo "Writing move 5"
cat srccpy.txt |  awk '{if($4>=500 || $5>=500 || $6>=500 )print($1 " " $2 " " $3)}' > move5.txt

#!on bad file do not run
else
echo 'File does not exist'
fi

rm srccpy.txt
echo 'Done'

