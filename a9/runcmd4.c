#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define MAXLEN 1000

//implement:   command1 = command2 

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

void runLoop(char *line) {
	char *command1 = strtok(line, "=");
	char *command2 = strtok(NULL, "\n");
	//create 2 pipes and reconfigure them
	//:q:then invoke processes!
	int tochild[2], toparent[2];
	pipe(tochild);
	pipe(toparent);

	if (fork()) { //parent!
		//reconfigure pipes
		dup2(toparent[0], 0);
		dup2(tochild[1], 1);
		close(toparent[0]); close(toparent[1]);
		close(tochild[0]); close(tochild[1]);
		//invoke command
		runCommand(command1);
	} else { // child!
		//reconfigure pipes 
		dup2(toparent[1], 1);
		dup2(tochild[0], 0);
		close(toparent[0]); close(toparent[1]);
		close(tochild[0]); close(tochild[1]);
		//invoke command
		runCommand(command2);
	}

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
			runLoop(buffer);
		wait(NULL);
	}
}

