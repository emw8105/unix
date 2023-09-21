#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define MAXLEN 1000


void runCommand(char *cmd) {
	//tokenize, build arg list, invoke execvp()
	char *args[MAXLEN];
	int argc = 0;
	args[argc] = strtok(cmd, " \n");
	while (args[argc]) 
		args[++argc] = strtok(NULL, " \n");

	execvp(args[0], args);
	fprintf(stderr, "this is bad!\n");
	exit(1);
}

//read one line at a time, treat it as a command 
//run the command, then ask for the next command, so on.
int main() {
	char buffer[MAXLEN];
	while (1) {
		printf("Your wish is my command: ");
		fgets(buffer, MAXLEN, stdin);
		if (!fork())
			runCommand(buffer);
		wait(NULL);
	}
}

