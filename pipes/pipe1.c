#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
	int fds[2] = {0, 0};
	pipe(fds);
	printf("read: %d write: %d\n", fds[0], fds[1]);
	
	char buffer[100];
	printf("Enter line: ");
	fgets(buffer, 100, stdin);

	//write to pipe
	write(fds[1], buffer, strlen(buffer)+1);
	
	//read from pipe and output
	char receive[100];
	read(fds[0], receive, 100);
	puts(receive);
}
