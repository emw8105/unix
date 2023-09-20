#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	int value = fork();

	printf("fork() return value: %d\n", value);
	printf("Hello from %d! My parent is %d.\n", getpid(), getppid());
	wait(NULL);
}
