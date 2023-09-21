#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <inttypes.h>  
#include <stdint.h>  
#include <errno.h>   
#include <fcntl.h>     
#include <unistd.h>    
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

int numThreads = 0;

/*
0
1 2
3 4 5 6
7 ..   14
15
*/

void *child( void *ptr )
{
	uint32_t n = *(uint32_t *) ptr;

    pthread_t thread1, thread2;

	bool child1 = false, child2 = false;
	 uint32_t *twonplus1 = malloc(sizeof(uint32_t));
	 uint32_t *twonplus2 = malloc(sizeof(uint32_t));
	 *twonplus1 = 2*n+1;
	 *twonplus2 = 2*n+2;

	 if (2*n+1 < numThreads) {
     	pthread_create(&thread1, NULL, child, (void *) twonplus1);
		child1 = true;
	 	if (2*n+2 < numThreads) {
     		pthread_create(&thread2, NULL, child, (void *) twonplus2);
			child2 = true;
		}
	}
	 uint32_t *ptr1 = malloc(sizeof(uint32_t));
	 uint32_t *ptr2 = malloc(sizeof(uint32_t));
	 *ptr1 = *ptr2 = 0;

	 if (child1)
     	pthread_join(thread1, (void *) &ptr1);
	 if (child2)
     	pthread_join(thread2, (void *) &ptr2); 

	 uint32_t *totalptr = (uint32_t *) malloc(sizeof(uint32_t));
	 *totalptr = 1 + *ptr1 + *ptr2;
	 printf("Thread %d total %d\n", n, *totalptr);
	 return (void *) totalptr;
}

int main(int argc, char *argv[])
{
     pthread_t thread1;

	 numThreads = atoi(argv[1]); 

	 uint32_t n = 0;
     pthread_create(&thread1, NULL, child, (void *) &n);

	 void *ptr;
     pthread_join(thread1, &ptr); 
	 printf("%u\n", *(uint32_t *) ptr);
     exit(0);
}


