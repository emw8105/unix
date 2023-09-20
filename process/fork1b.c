#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	//returns child's PID for the parent, 0 for the new child
	if (fork())
		//this is parent process!
		printf("Parent: ");
	else
		//this is child process
		printf("Child: ");

	printf("Hello from %d! My parent is %d.\n", getpid(), getppid());
	//wait(NULL);
}
