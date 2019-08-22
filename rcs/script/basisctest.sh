./generator --big-superposition > test.txt
ARG=$(../../lem-in a < test.txt| grep -E "#Here is|Step's"| rev | cut -d ' ' -f1| rev | tail -2)
RETURN=$(echo $?)
GENERATOR=$(echo $ARG | cut -d ' ' -f1)
SOLUTION=$(echo $ARG | cut -d ' ' -f2)
echo "Generator:   $GENERATOR" | cat -e
echo "My solution: $SOLUTION" | cat -e
DIFF=$(($GENERATOR - $SOLUTION))
