#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

//thread converts ptr to int, multiplies by 10 and returns it.
void *function_for_thread( void *ptr )
{
	//get user input to value and return value
	//int value = (int)ptr;
	//return (void *) (value * 10);
	int value = 0;
	scanf("%d", &value);
	return (void *) value;
}

int main(int argc, char *argv[])
{
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
	int total=0;
	for(int i=0; i<n; i++) {
     	pthread_join(threads[i], &ptr);
		//total all return values
		total += (int) ptr;
	 	printf("Return value %d, total %d\n", (int) ptr, total);
	}
	printf("Final total: %d\n", total);
	
    exit(0);
}

