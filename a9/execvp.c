#include <stdio.h>
#include <unistd.h>

//execvp the command specified in the command line

int main(int argc, char *argv[]) {
	char *arguments[1000];

	char *command = argv[1];
	for(int i=1; i<argc; i++) 
		arguments[i-1] = argv[i];
	arguments[argc-1] = NULL;

	printf("Invoking: %s\n", command);
	printf("Arguments: ");
	for(int i=0; i<argc-1; i++) 
		printf("%s ", arguments[i]);
	puts("\nExecuting the command now.\n");

	execvp(command, arguments);
	fputs("I hope you don't see me!\n", stderr);
}
