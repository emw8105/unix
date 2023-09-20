#include <stdio.h>
#include <unistd.h>

int main() {
	fork();
	fork();
	printf("Hello from %d! My parent is %d.\n", getpid(), getppid());
}
