#!/bin/bash

MAX=0
MIN=0
ITERATIONS=0
FILE=worst.txt
SUM=0
i=0
TEST=$1
BAD=0
if [ !$1 ]
then
	TEST=100
fi
while [ $i -lt $TEST ]
do
	sleep 1
	./generator --big-superposition > iter.txt
	./symlemin a < iter.txt > /dev/null
	RETURN=$(echo $?)
	ARG=$(./symlemin a < iter.txt | grep -E "#Here is|Step's"| rev | cut -d ' ' -f1| rev | tail -2)
	GENERATOR=$(echo $ARG | cut -d ' ' -f1)
	SOLUTION=$(echo $ARG | cut -d ' ' -f2)
	if [ $RETURN -ne 0 ]
	then
		echo "Error!"
		echo $RETURN
		break
	fi
	DIFF=$(($SOLUTION - $GENERATOR))
	if [ $DIFF -gt 0 ]
	then
		if [ $DIFF -gt $MAX ]
		then
			MAX=$DIFF;
			echo 'hello'
			cat iter.txt > $FILE
		fi
		BAD=$(($BAD + 1))
	else
		if [ $MIN -gt $DIFF ]
		then
			MIN=$DIFF
		fi
	fi
	if [ 0 -gt $DIFF ]
	then
		echo $i ":" $DIFF "-" $MAX "(" $GENERATOR":" $SOLUTION ")"
	else	
		echo  $i ": " $DIFF "-" $MAX "(" $GENERATOR":" $SOLUTION ")"
	fi
	SUM=$(($SUM + $DIFF))
	ITERATIONS=$(($ITERATIONS + 1))
	i=$((i + 1))
done

echo "AVG: " $(($SUM / $ITERATIONS))
echo "MAX: " $MAX
echo "MIN: " $MIN
echo "BAD: " $BAD
