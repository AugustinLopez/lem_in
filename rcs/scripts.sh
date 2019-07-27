./generator --big-superposition > test.txt
../lem-in a < test.txt
#../lem-in < test.txt | grep -E 'L1|L5-|L9-|#Here' | cut -f1 -d- | cat -n
