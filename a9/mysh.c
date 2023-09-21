#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

//read all the quotes from quotes.txt
//when client asks for a motivational quote, select one randomly and send it out.

#define MAXQUOTES 10000
#define MAXLEN 1000
char *quotes[MAXQUOTES];
int numQuotes=0;
char commands[MAXLEN][MAXLEN];
int numCommands=0;
int pipes[2*MAXLEN][2];
int numPipes = 0;


//runs a simple command
//cmdname arg1 arg2 arg3 ...
void runCommand(char *command) {
	//split and assemble the arguments and invoke execvp()
	//use strtok(..)
	int numArgs = 0;
	char *arg = strtok(command, " \t\n");
	while(arg != NULL) {
		strcpy(commands[numArgs], arg);
		numArgs++;
		arg = strtok(NULL, " \t\n");
	}
	strcpy(commands[numArgs], "");

	if(execvp(commands[0],(char *const *) commands) < 0) {
		perror("execvp error");
		exit(1);
	}
}

//cmd0 | cmd1 | cmd2 | cmd3 | cmd4 
void child(int i) {
	//rewire pipes to 0 and 1 
	//close unnecessary pipes
	//run ith command
	if (i==0) {
		dup2(pipes[i][1], 1); // maybe pipes instead of fds
	} else if(i == numPipes) {
		dup2(pipes[i][0], 0);
	} else {
		dup2(pipes[i-1][0], 0);
		dup2(pipes[i][1], 1);
	}
	// for loop to close unnecessary pipes
	for(int j = 0; j < numPipes; j++) {
		if(j != i-1 && j != i) {
			close(pipes[j][0]);
			close(pipes[j][1]);
		}
	}
	runCommand(commands[i]);
}

void processLine(char *line) {
	char *pipePtr = strchr(line, '|');
	char *equalPtr = strchr(line, '=');
	if (pipePtr) { //not NULL
		//command has several sub-commands connected with pipes
		//setup commands array
		//setup pipes array
		char *token = strtok(line, "|");
		int i = 0;
		while(token != NULL) {
			commands[i][0] = token;
			i++;
			token = strtok(NULL, "|");
		}
		numCommands = i;
		numPipes = numCommands-1;
		for(int i = 0; i < numCommands-1; i++)
			pipe(pipes[i]);
		
		//create children --> invoke child(i) in a loop
		//cmd0 | cmd1 | cmd2 | cmd3 | cmd4 
		for(int i = 0; i < numCommands-1; i++) {
			if (fork()==0)
				child(i);
		}
		//child(numCommands-1); //take the place of last child
		for(int i = 0; i < numPipes; i++) {
		close(pipes[i][0]);
		close(pipes[i][1]);
		}
	// wait for children to finish?
	} else if (equalPtr) {
		//command has = operator, so 2 commands --> 2 processes
    } else {
		//it is a simple command, no pipe or = character
	}
	runCommand(line);

	exit(0);
}

int main() {
	// load up all the quotes from quotes.txt
	char line[MAXLEN];
	FILE *fp = fopen("quotes.txt", "r");
	if(!fp) {
		puts("quotes.txt cannot be opened for reading.");
		exit(1);
	}
	int i=0;
	while(fgets(line, MAXLEN, fp)) {
		quotes[i] = (char *) malloc(strlen(line)+1);
		i++;
	}
	numQuotes = i;
	
	// infinite loop to serve the customer
	while (1) {
		//output a random quote to stderr
		fputs(quotes[rand()%numQuotes], stderr);
		fprintf(stderr, "# ");
		//get the user input
		fgets(line, 1000, stdin);

		//spawn a child for taking care of it
		if (fork() == 0) 
			processLine(line);

		//wait the child to finish the job!
		int x=0;
		wait(&x);
	}
}
