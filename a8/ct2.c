#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define MAXLEN 1000
#define MAXOPER 100

int values[2*MAXOPER+1];
int flags[2*MAXOPER+1];

char operators[MAXOPER];
int operatorCount=0;

//equivalent of child(i)
void *child(void *ptr) {
	int i = (int) ptr; //read from 2*i, read from 2*i+1, write to 2*i+2
	while (1) {
		while (!flags[2*i]) //data ready?
			;
		while (!flags[2*i+1]) //data ready?
			;
		while (flags[2*i+2]) //ok to output?
			;
		if (operators[i] == '+')
			values[2*i+2] = values[2*i] + values[2*i+1];
		else if (operators[i] == '-')
			values[2*i+2] = values[2*i] - values[2*i+1];
		else if (operators[i] == '*')
			values[2*i+2] = values[2*i] * values[2*i+1];
		else if (operators[i] == '/')
			values[2*i+2] = values[2*i] / values[2*i+1];
		flags[2*i] = 0; //ready for next data
		flags[2*i+1] = 0; //ready for next data
		flags[2*i+2] = 1; //output ready
	}
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
	for(int i=0; i<numPipes; i++)
		pipe(fds[i]);

	//setup the configuration with necessary # of children
	for(int i=0; i<operatorCount; i++) {
     	pthread_t thread1;
     	if (pthread_create(&thread1, NULL, child, (void *) i))
     		exit(1);
	}

	//continue to read the data from the file & pump data into pipes
	int x;
	while (fscanf(dataFile, "%d", &x) > 0) {
		while (flags[0]) ;
		values[0] = x;
		flags[0] = 1;
		//let us assume that line has that many pieces of data
		for(int i=0; i<operatorCount; i++) {
			fscanf(dataFile, "%d", &x);
			while (flags[2*i+1]) ;
			values[2*i+1] = x;
			flags[2*i+1] = 1;
		}
		while (!flags[2*operatorCount]) ;
		x = values[2*operatorCount];
		flags[2*operatorCount] = 0;
		printf("%d\n", x);
	}
}

