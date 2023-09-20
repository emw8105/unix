#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int tochild[2], toparent[2];

// both parent and child  become new programs!

int parent() {
	close(1);
	dup(tochild[1]);

	close(0);
	dup(toparent[0]);

	close(tochild[0]); close(tochild[1]);
	close(toparent[0]); close(toparent[1]);

	execl("./computer", "computer", NULL);
	fputs("I hope you do not see this one either!", stderr);

}

int child() {
	close(0);
	dup(tochild[0]);
	close(1);
	dup(toparent[1]);

	close(tochild[0]); close(tochild[1]);
	close(toparent[0]); close(toparent[1]);

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
