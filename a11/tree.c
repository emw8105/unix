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
	int n = (int) ptr;

    pthread_t thread1, thread2;
	bool child1 = false, child2 = false;
	 if (2*n+1 < numThreads) {
     	pthread_create(&thread1, NULL, child, (void *) (2*n+1));
		child1 = true;
	 	if (2*n+2 < numThreads) {
     		pthread_create(&thread2, NULL, child, (void *) (2*n+2));
			child2 = true;
		}
	}
	 char *ptr1 = NULL, *ptr2 = NULL;
	 if (child1)
     	pthread_join(thread1, &ptr1);
	 if (child2)
     	pthread_join(thread2, &ptr2); 
	 	int total = 1 + (int) ptr1 + (int) ptr2;
	 printf("Thread %d total %d\n", n, total);
	 return (void *) total;
}

int main(int argc, char *argv[])
{
     pthread_t thread1;

	 numThreads = atoi(argv[1]); 

	 int n = 0;
     pthread_create(&thread1, NULL, child, (void *) n);

	 void *ptr;
     pthread_join(thread1, &ptr); 
	 printf("%d\n", (int) ptr);
     exit(0);
}


