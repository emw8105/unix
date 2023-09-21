#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int fds[3][2];

void child() {
	//do the reconfiguration & cleanup
	//invoke add
	dup2(fds[0][0], 0);
	dup2(fds[1][0], 3);
	dup2(fds[2][1], 1);
	
	close(fds[0][0]); close(fds[0][1]);
	close(fds[1][0]); close(fds[1][1]);
	close(fds[2][0]); close(fds[2][1]);

	execl("add", "add", "-v", NULL);
	fprintf(stderr, "I hope you won't see me!\n");
	exit(1);
}

int main() {
	dup(0); //3 will be duplicate of 0, it will not be part of any pipes
	pipe(fds[0]); //to send 1st parameter to child
	pipe(fds[1]); //to send 2nd parameter to child
	pipe(fds[2]); //to read result from child

	if (!fork()) 
		child();

	//optional cleanup
	close(fds[0][0]);
	close(fds[1][0]);
	close(fds[2][1]);

	//parent is in charge of getting user inputs 
	//and sending them to child, read result
	while (1) {
		printf("Enter 2 numbers:\n");
		int x, y, z;
		scanf("%d%d", &x, &y);
		write(fds[0][1], &x, sizeof(int));
		write(fds[1][1], &y, sizeof(int));
		read(fds[2][0], &z, sizeof(int));
		// z = x + y;
		printf("result from add: %d\n\n", z);
	}
}
