#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int numChildren = atoi(argv[1]);
	
	int i=0;
	for(i=0 ; i<numChildren; i++)
		if (!fork())
			break;

	printf("Hello from %d (i=%d)! My parent is %d.\n", getpid(), i, getppid());

	char buffer[10];
	fgets(buffer,10, stdin);
	printf("%d: %s\n",i, buffer);
}
