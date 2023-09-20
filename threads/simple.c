//Source: https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int limit=0; //global variable - accessible to all threads!

//return type and parameter type dictated by thread creation mechanism
//void * means pointer to memory, but we have no idea what data type it is pointing to.
void *print_mathtable( void *ptr )
{
     int *valuep;
     valuep = (int *) ptr; //assume that pointer is pointing to int 
	 int value = *valuep; //get that integer value
	 //use it to create multiplication table
     for(int i=2; i<=limit; i++)
	 	printf("%d * %d = %d\n", i , value , i * value);
}

int main(int argc, char *argv[])
{
     pthread_t thread1, thread2;

	limit = atoi(argv[1]); //math table upper limit

    /* Create independent threads each of which will execute function */

	//first thread: multiplier is 2
	 int value1 = 2;
     int iret1 = pthread_create(&thread1, NULL, print_mathtable, (void *) &value1);
     printf("Thread 1 returns: %d\n",iret1);

	//second thread: multiplier is 3
	 int value2 = 3;
     int iret2 = pthread_create(&thread2, NULL, print_mathtable, (void *) &value2);
     printf("Thread 2 returns: %d\n",iret2);

     /* Wait till threads are complete before main continues. Unless we  */
     /* wait we run the risk of executing an exit which will terminate   */
     /* the process and all threads before the threads have completed.   */

     pthread_join(thread1, NULL);
     pthread_join(thread2, NULL); 

     exit(0);
}

