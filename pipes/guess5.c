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

	//child does not need pipe fds any more! Let us clean up
	//before invoking the new process.
	close(tochild[0]);
	close(tochild[1]);
	close(toparent[0]);
	close(toparent[1]);

	execl("./user", "user", NULL);
	fputs("I hope you do not see me!", stderr);
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
