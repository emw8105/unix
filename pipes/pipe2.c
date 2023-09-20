#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
	int fds[2] = {0, 0};
	pipe(fds);
	printf("read: %d write: %d\n", fds[0], fds[1]);
	
	if(fork()) { // parent
		char buffer[100];
		printf("Parent: Enter line: ");
		fgets(buffer, 100, stdin);

		//write to pipe
		write(fds[1], buffer, strlen(buffer)+1);
		wait(NULL);
	} else { // child
		//read from pipe and output
		char receive[100];
		read(fds[0], receive, 100);
		printf("Child got: %s\n", receive);
	}
}
