#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXLEN 1000

char operators[100];
int fds[100][2];
int operatorCount=0;
int numPipes=0;

void child(char operator, int index) {
	//CODE HERE!
	//reference the pipes files
	
	printf("child process %d started\n", getpid());

	for(int i = 0; i < numPipes*2; i++) {
		close(fds[i][0]);
		close(fds[i][1]);
	}
	for(int i = 0; i < numPipes*2; i++) {
		if(i != index*2 && i != index * 2 + 1 ) {
			close(fds[i][0]);
			close(fds[i][1]);
		}
	}

	printf("necessary pipes closed\n");
	
	dup2(fds[index*2][0], STDIN_FILENO);
	close(fds[index*2][0]);

	dup2(fds[index*2+1][1], STDOUT_FILENO);
	close(fds[index*2+1][1]);

	printf("child process %d executing %c\n", getpid(), operator);

	switch(operator) {
		case '+':
			execl("./add", "add", NULL);
			break;
		case '-':
			execl("./subtract", "subtract", NULL);
			break;
		case '*':
			execl("./multiply", "multiply", NULL);
			break;
		case '/':
			execl("./divide", "divide", NULL);
			break;
		default:
			exit(1);
	}
	perror("execl failed");
	exit(1);
}
int main(int argc, char *argv[]) {
	char line[MAXLEN], *temp;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		exit(1);
	}

	FILE *dataFile = fopen(argv[1], "r");
	//read the first line - it contains the configuration
	fgets(line, MAXLEN, dataFile); 
	
	// sample content for line: a + b - c
	strtok(line, " \n"); //skip the symbol representing variable/parameter
	while (temp = strtok(NULL, " \n")) {
		operators[operatorCount] = temp[0];
		//printf("operator: %c\n", operators[operatorCount]);
		operatorCount++;
		strtok(NULL, " \n"); //skip the symbol representing variable/parameter
	}

	//create the necessary # of pipes
	numPipes = operatorCount * 2 + 1;

	//CODE HERE!
	//create that many pipes
	//create children
	//continue to read the input data file: while(scanf("%d", &value))
	
	int i;
	for(i=0; i < numPipes; i+=2) {
		pipe(fds[i]);
	}
	for(i = 0; i<operatorCount; i++) {
		if (!fork()) {
			child(operators[i], i*2);
			exit(0);
		}
	}

	printf("Parent process waiting for children to finish.\n");

	i=0;
	int values[100];
	while(fgets(line, MAXLEN, dataFile) != NULL) {
		temp = strtok(line, " \n");
		int j = 0;
		while(temp != NULL) {
			values[j] = atoi(temp);
			write(fds[j*2+1][i], &values[j], sizeof(int));
			j++;
			temp = strtok(NULL, " \n");
		}
		int result;
		read(fds[(operatorCount-1)*2][0], &result, sizeof(int));
		printf("%d\n", result);
	}

	for (i=0; i< numPipes; i++) {
		close(fds[i][1]);
		close(fds[i][0]);
	}

	fclose(dataFile);
	return 0;
}
