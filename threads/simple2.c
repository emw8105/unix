//Source: https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int limit=0;

//return type and parameter type dictated by thread creation mechanism
//void * means pointer to memory, but we have no idea what data type it is pointing to.
void *go_sleep( void *ptr )
{
	puts("Going to sleep...");
	sleep(100);
}

int main(int argc, char *argv[])
{
     pthread_t thread1, thread2;
     int  iret1, iret2;

    /* Create independent threads each of which will execute function */

     iret1 = pthread_create(&thread1, NULL, go_sleep, NULL);
     iret2 = pthread_create(&thread2, NULL, go_sleep, NULL);
     printf("Thread 1 returns: %d\n",iret1);
     printf("Thread 2 returns: %d\n",iret2);

     /* Wait till threads are complete before main continues. Unless we  */
     /* wait we run the risk of executing an exit which will terminate   */
     /* the process and all threads before the threads have completed.   */

     pthread_join(thread1, NULL);
     pthread_join(thread2, NULL); 

     exit(0);
}

