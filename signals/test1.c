#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	fork();
	fork();
	fork();
	fork();
	while (1) 
		;
}
