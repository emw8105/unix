fib.c - multi-threaded Fibonacci computation program for reference
htree.c - startup file
htree2.c - with additional code to compute hash with just 1 thread, fails for tc4 due to read() limitation?
htree3.c - introduced loop to keep reading until the whole file is read, then do hashing
tree.c - tree structure of threads to meet our needs
tree2.c - perfected the data types for our use.

Testcases: input, output & verbose files:
tc1, hash_tc1, hash_tc1_4_verbose, hash_tc1_8_verbose
tc2, hash_tc2
tc3, hash_tc3
tc4, hash_tc4


Combine the functionalities of htree3.c and tree2.c
