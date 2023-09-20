#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

//thread converts ptr to int, multiplies by 10 and returns it.
void *function_for_thread( void *ptr )
{
	int value = (int)ptr;
	return (void *) (value * 10);
}

int main(int argc, char *argv[])
{
	//get # of threads from the argument
	int n = atoi(argv[1]);
	//allocate memory to keep track of n threads
    pthread_t *threads = (pthread_t *) malloc (n * sizeof(pthread_t));

	//create n threads
	for(int i=0; i<n; i++)  
     if (pthread_create(&threads[i], NULL, function_for_thread, (void *) i)) {
	 	fprintf(stderr, "Thread creation failed for %d\n", i);
     	exit(1);
	 }

	void *ptr;

	//let us collect all the return values from threads
	for(int i=n-1; i>=0; i--) {
     	pthread_join(threads[i], &ptr);
	 	printf("Return value %d\n", (int) ptr);
	}

    exit(0);
}

