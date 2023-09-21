#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define MAXLEN 1000

	//execvp(argv[1], argv+1);
	//execvp(argv[1], &argv[1]);
	//execvp(argv[0], ++argv);

void runCommand(char *cmd) {
	//tokenize, build arg list, invoke execvp()
	char *args[MAXLEN];
	int argc = 0;
	args[argc] = strtok(cmd, " \n");
	while (args[argc]) 
		args[++argc] = strtok(NULL, " \n");

	execvp(args[0], args);
}

//read one line treat it as a command
int main() {
	char buffer[MAXLEN];
	printf("Your wish is my command: ");
	fgets(buffer, MAXLEN, stdin);
	runCommand(buffer);
}
