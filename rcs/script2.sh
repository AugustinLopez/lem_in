#!/bin/bash

MAX=0
MIN=0
ITERATIONS=0
FILE=worst.txt
SUM=0
i=1
MEM=0
while [ $i -lt 100 ]
do
	sleep 1
	./generator --big-superposition > test.txt
	ARG=$(../lem-in a < test.txt| grep -E "#Here is|Step's"| rev | cut -d ' ' -f1| rev | tail -2)
	RETURN=$(echo $?)
	GENERATOR=$(echo $ARG | cut -d ' ' -f1)
	SOLUTION=$(echo $ARG | cut -d ' ' -f2)
	if [ $RETURN -ne 0 ]
	then
		echo "Error!"
		break
	fi
	DIFF=$(($SOLUTION - $GENERATOR))
	if [ $DIFF -gt 0 ]
	then
		if [ $DIFF -gt $MAX ]
		then
			MAX=$DIFF;
			cat test.txt > $FILE
		fi
	else
		if [ $MIN -gt $DIFF ]
		then
			MIN=$DIFF
		fi
	fi
	echo $i ":" $DIFF "-" $MAX "(" $GENERATOR":" $SOLUTION ")"
	SUM=$(($SUM + $DIFF))
	ITERATIONS=$(($ITERATIONS + 1))
	i=$((i + 1))
done

echo "AVG: " $(($SUM / $ITERATIONS))
echo "MAX: " $MAX
echo "MIN: " $MIN
