#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *fib( void *ptr )
{
	int n = * (int *) ptr;

	//check whether n is 0 or 1
	//return that value
	//if not, create 2 threads: pass n-1 and n-2 respectively
	//get the results and add them and return it!
	if (n < 2) {
		int *nptr = (int *) malloc(sizeof(int));
		*nptr = n;
		return (void *) nptr;
	}

     pthread_t thread1, thread2;

	 int *n1ptr = (int *) malloc(sizeof(int));
	 int *n2ptr = (int *) malloc(sizeof(int));
	 *n1ptr = n-1;
	 *n2ptr = n-2;
     pthread_create(&thread1, NULL, fib, (void *) n1ptr);
     pthread_create(&thread2, NULL, fib, (void *) n2ptr);

	 int *ptr1, *ptr2;
     pthread_join(thread1, (void *)&ptr1);
     pthread_join(thread2, (void *)&ptr2);
	 int *totalptr = (int *) malloc(sizeof(int));
	 *totalptr = *ptr1 + *ptr2;
	 return (void *) totalptr;
}

int main(int argc, char *argv[])
{
     pthread_t thread1;

	int n = atoi(argv[1]); 

     pthread_create(&thread1, NULL, fib, (void *) &n);

	 void *ptr;
     pthread_join(thread1, &ptr); 
	 printf("%d\n", * (int *) ptr);
     exit(0);
}


