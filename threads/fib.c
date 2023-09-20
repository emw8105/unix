#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

//fib sequence:
//0 --> 1
//1 --> 1
//2 --> 2
//3 --> 3
//4 --> 5
//5 --> 8
//fib(0) = 1, fib(1) = 1
//fib(n) = fib(n-1) + fib(n-2)

void *fib(void *ptr)
{
	int n = (int) ptr;
	if (n < 2)
		return (void *) 1;
	
	//create 2 threads to compute fib(n-1) and fib(n-2) respectively
	//then add them and return the total

	pthread_t thread2;
	if(pthread_create(&thread2, NULL, fib, (void *) n-1))
		exit(1);
	
	pthread_t thread3;
	if(pthread_create(&thread3, NULL, fib, (void *) n-2))
		exit(1);
	
	void *ptr1, *ptr2;
	pthread_join(thread2, &ptr1);
	pthread_join(thread3, &ptr2);
	int total = (int)ptr1 + (int)ptr2;
	return (void *) total;

}

int main(int argc, char *argv[])
{
	printf("int %d int * %d\n", sizeof(int), sizeof(int *));
	//get n as the argument, compute & output fib(n)
	int target = atoi(argv[1]);

     pthread_t thread1;
     if (pthread_create(&thread1, NULL, fib, (void *) target))
     	exit(1);
		
	 void *ptr;
     pthread_join(thread1, &ptr);
	 printf("Return value %d\n", (int) ptr);

    exit(0);
}

