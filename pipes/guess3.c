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
		printf("Parent: mid: %d\n", mid);
		write(tochild[1], &mid, sizeof(int));

		char response;
		
		read(toparent[0], &response, 1);
		printf("Parent read: %c\n", response);

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

// Child thinks of a number. Parent probes and finds that number!
int child() {
	//use current time to come with a random seed
	srand(time(NULL));
	//get a random number 1 to 100
	int number = rand() % 100 + 1;
	printf("Child: Random number: %d\n", number);

	int received;
	//keep reading a number, respond with < or > or =
	while (read(tochild[0], &received, sizeof(int))> 0) {
		printf("child: got %d\n", received);
		if (received < number)
			write(toparent[1], ">", 1); //tell parent to go higher!
		else if (received > number)
			write(toparent[1], "<", 1); //tell parent to go lower!
		else {
			write(toparent[1], "=", 1); //tell parent it is perfect!
			break;
		}
	}
	puts("Child: done.");
}

int main() {
	
	pipe(tochild);
	printf("pipe #1: %d, %d\n", tochild[0], tochild[1]);

	pipe(toparent);
	printf("pipe #2: %d, %d\n", toparent[0], toparent[1]);

	//if (fork()) 
	//	parent();
	//else
	// child();

	fork() ? parent() : child();
}
