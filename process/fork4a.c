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

	int value=0;
	scanf("%d", &value);
	printf("%d: %d\n", i, value * value);
}
