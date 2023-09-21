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

/* When numThreads is 16, following is the tree of threads that are created:
0
1   2
3 4 5 6
7 8 9 10 11 12 13 14
15

create children first...

hash = jenkins_one_at_a_time_hash(actual file data assigned to this thread)

There are 3 types of threads: 
- threads with 0 children

- threads with 1 child
get result from child1 --> child1hash
char results[100];
sprintf(results, "%u%u", hash, child1hash);

- threads with 2 children
get result from child2 --> child2hash
sprintf(results, "%u%u%u", hash, child1hash, child2hash);

hash = jenkins_one_at_a_time_hash(results, strlen(results));

return hash!
*/

void *child( void *ptr )
{
	uint32_t n = (uint32_t) ptr;

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
	uint32_t total = 1 + (uint32_t) ptr1 + (uint32_t) ptr2;
	 printf("Thread %d total %d\n", n, total);
	 return (void *) total;
}

int main(int argc, char *argv[])
{
     pthread_t thread1;

	 numThreads = atoi(argv[1]); 

	 uint32_t n = 0;
     pthread_create(&thread1, NULL, child, (void *) n);

	 void *ptr;
     pthread_join(thread1, &ptr); 
	 printf("%u\n", (uint32_t) ptr);
     exit(0);
}


