#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *fib( void *ptr )
{
	int n = (int) ptr;

	//check whether n is 0 or 1
	//return that value
	//if not, create 2 threads: pass n-1 and n-2 respectively
	//get the results and add them and return it!
	if (n < 2) 
		return (void *) n;

     pthread_t thread1, thread2;

     pthread_create(&thread1, NULL, fib, (void *) (n-1));
     pthread_create(&thread2, NULL, fib, (void *) (n-2));

	 char *ptr1, *ptr2;
     pthread_join(thread1, &ptr1);
     pthread_join(thread2, &ptr2); 
	 int total = (int) ptr1 + (int) ptr2;
	 return (void *) total;
}

int main(int argc, char *argv[])
{
     pthread_t thread1;

	int n = atoi(argv[1]); 

     pthread_create(&thread1, NULL, fib, (void *) n);

	 void *ptr;
     pthread_join(thread1, &ptr); 
	 printf("%d\n", (int) ptr);
     exit(0);
}


