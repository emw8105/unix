#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	int maxDepth = atoi(argv[1]);
	
	int i=0;
	for(i=0 ; i<maxDepth; i++)
		if (fork() && fork())
			break;
	printf("Hello from %d (i=%d)! My parent is %d.\n", getpid(), i, getppid());
	wait(NULL);
	wait(NULL);
}
