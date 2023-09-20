#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

// fds: parent to child
// newfds: child to parent
int tochild[2], toparent[2];

int parent() {
	int low=1, high=100;

	while (low <= high) {
		//compute midpoint, send it to child and wait for response.
		int mid = (low + high)/2;
		printf("mid: %d\n", mid);
		write(tochild[1], &mid, sizeof(int));

		char response;
		//scanf("%c", &response);
		read(toparent[0], &response, 1);

		if (response == '<')
			high = mid-1;
		else if (response == '>')
			low = mid+1;
		else if (response == '=') {
			puts("Great game!");
			break;
		} else
			printf ("Bad char %c", response);
	}
}

int child() {
	//replace standard input with pipe input
	close(0);
	dup(tochild[0]);
	//replace standard output with pipe output
	close(1);
	dup(toparent[1]);

	//use current time to come with a random seed
	srand(time(NULL));
	//get a random number 1 to 100
	int number = rand() % 100 + 1;
	fprintf(stderr, "Random number: %d\n", number);

	int received;
	//keep reading a number, respond with < or > or =
	while (read(0, &received, sizeof(int))> 0) {
		if (received < number)
			write(1, ">", 1); //tell parent to go higher!
		else if (received > number)
			write(1, "<", 1); //tell parent to go lower!
		else {
			write(1, "=", 1); //tell parent it is perfect!
			break;
		}
	}
	fputs("Child: done.\n", stderr);
}

int main() {
	pipe(tochild);
	printf("pipe #1: %d, %d\n", tochild[0], tochild[1]);

	pipe(toparent);
	printf("pipe #2: %d, %d\n", toparent[0], toparent[1]);

	if (fork() > 0) 
		parent();
	else
		child();
}
/*
//create 2nd pipe - use it for child writing & parent reading 
//child writes "xyz" - see whether the parent is able to read and print it
int main() {

	if (fork() > 0) {
		//parent writes first, then waits to read.
		write(fds[1], "abc", 4);

		char readback[4];
		read(newfds[0], readback, 4);
		puts(readback);

		printf("Parent %d done.\n", getpid());
	} else {
		//child process - reads first, then writes.
		char readback[4];
		read(fds[0], readback, 4);
		puts(readback);
		write(newfds[1], "xyz", 4);

		printf("Child %d done.\n", getpid());
	}

}
*/
