#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAXLEN 1000

//execvp the command user inputs after the program prompts

int main() {
	char *arguments[MAXLEN], line[MAXLEN];

	printf("Enter your command: ");
	fgets(line, MAXLEN, stdin);

	char *command = strtok(line, " \n");
	arguments[0] = command;

	int i=1;
	//keep getting tokens (individual words)
	while ((arguments[i] = strtok(NULL, " \n")) != NULL)
		i++;

	printf("Invoking: %s\n", command);
	printf("Arguments: ");
	for(int j=0; j<i; j++) 
		printf("%s ", arguments[j]);
	puts("\nExecuting the command now.\n");

	execvp(command, arguments);
	fputs("I hope you don't see me!\n", stderr);
}
