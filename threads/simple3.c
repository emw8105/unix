#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *function_for_thread( void *ptr )
{
	return (void *) 10;
}

int main(int argc, char *argv[])
{
     pthread_t thread1;

     if (pthread_create(&thread1, NULL, function_for_thread, NULL))
     	exit(1);

	 void *ptr;
     pthread_join(thread1, &ptr);
	 printf("Return value %d\n", (int) ptr);

     exit(0);
}

