#!/bin/bash

echo "Use 'time'? (y\n)"
read input
if [ "$input" == "y" ]
	then
    TIME='time -p'
fi
echo "Use 'tail'? (y\n)"
read input
if [ "$input" == "y" ]
	then
    TAIL='| tail'
fi
echo "Press 's' to test with stdout"
echo "      'f' to test with file out"
echo "      'n' to test with noout"
echo "      'a' to test with all type out"
read input
if [ "$input" == "s" ]
	then
    OUT='stdout'
fi
if [ "$input" == "f" ]
	then
    OUT='file'
fi
if [ "$input" == "n" ]
	then
    OUT='noout'
fi
for f in bin/*$OUT*.run
do 
echo "$f" :
$TIME "$f" $TAIL
echo ""
done
