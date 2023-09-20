#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

int x,y,z;
int zflag = 0;
int xyflag = 0;

void *add(void *ptr) {
	while(1) {
		if(!xyflag) // wait until x and y are ready
			;
		z = x+y;
		zflag = 1;	// indicate z is ready to be read
	}
}

int main() {
	
	pthread_t thread1;
	if(pthread_create(&thread1, NULL, add, NULL))
		exit(1);
	
	while (1) {
		printf("Enter 2 numbers:\n");
		scanf("%d%d", &x, &y);
		xyflag = 1;
		while(!zflag)
			;
		printf("result from add: %d\n\n", z);
		zflag = 0;
	}
}
