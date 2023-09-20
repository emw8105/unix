//Source: https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int counter = 0;
int n = 0;

//mutual exclusion lock  - binary semaphore 

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void *counting_loop()
{
    for(int i=0; i<n ; i++) {
		//serialize access to avoid race condition
		pthread_mutex_lock( &mutex1 );
	 	counter++;
		pthread_mutex_unlock( &mutex1 );
	}
}

int main(int argc, char *argv[])
{
     pthread_t thread1, thread2;
     int  iret1, iret2;
	
	 n = atoi(argv[1]);

    /* Create independent threads each of which will execute function */

     iret1 = pthread_create( &thread1, NULL, counting_loop, NULL);
     iret2 = pthread_create( &thread2, NULL, counting_loop, NULL);
     printf("Thread 1 returns: %d\n",iret1);
     printf("Thread 2 returns: %d\n",iret2);

     /* Wait till threads are complete before main continues. Unless we  */
     /* wait we run the risk of executing an exit which will terminate   */
     /* the process and all threads before the threads have completed.   */

     pthread_join( thread1, NULL);
     pthread_join( thread2, NULL); 

	 printf("%d * 2 = %d\n", n, counter);
     exit(0);
}

