//Source: https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int counter = 0;
int n = 0;

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void *counting_loop()
{
     for(int i=0; i<n ; i++) {
	 	pthread_mutex_lock( &mutex1 );
	 	counter++; //mutex gaurantees that only one thread is executing this line at any time!
	 	pthread_mutex_unlock( &mutex1 );
	}
}

int main(int argc, char *argv[])
{
     pthread_t thread1, thread2;
     int  iret1, iret2;
	
	 n = atoi(argv[1]);
	 int num_threads = atoi(argv[2]);

	 pthread_t *threads = (pthread_t *) malloc(num_threads * sizeof(pthread_t));

    /* Create independent threads each of which will execute function */
	 for(int i=0; i<num_threads; i++)
     	pthread_create( &threads[i], NULL, counting_loop, NULL);

     /* Wait till threads are complete before main continues. Unless we  */
     /* wait we run the risk of executing an exit which will terminate   */
     /* the process and all threads before the threads have completed.   */

	 for(int i=0; i<num_threads; i++)
     	pthread_join(threads[i], NULL);

	 printf("%d * %d = %d\n", n, num_threads, counter);
     exit(0);
}

