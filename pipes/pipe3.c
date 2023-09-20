#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
	
	// create all the pipes BEFORE forking
	int tochild[2] = {0, 0};
	int toparent[2] = {0, 0};
	pipe(tochild);
	pipe(toparent);
	printf("tochild read: %d write: %d\n", tochild[0], tochild[1]);
	printf("toparent read: %d write: %d\n", toparent[0], toparent[1]);
	if(fork()) { // parent
		
		// cleanup
		close(tochild[0]);
		close(toparent[1]);

		char buffer[100];
		printf("Parent: Enter line: ");
		fgets(buffer, 100, stdin);

		//get a line from user, write to child, get the response, and print
		write(tochild[1], buffer, strlen(buffer)+1);
		read(toparent[0], buffer, 100);
		printf("Parent got: %s\n", buffer);
		wait(NULL);
	} else { // child
		
		// cleanup
		close(tochild[1]);
		close(toparent[0]);
		
		// read from parent, output, modify the content and send it back to parent
		char receive[100];
		read(tochild[0], receive, 100);
		printf("Child got: %s\n", receive);
		// do something and send response back to parent	
		int n = strlen(receive);
		for(int i=0; i<n; i++) {
			receive[i]++;
		}
		write(toparent[1], receive, n+1);
	}
}
