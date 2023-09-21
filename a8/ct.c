#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

#define MAXLEN 1000
#define MAXOPER 100

int values[2*MAXOPER+1];
int flags[2*MAXOPER+1];

int operators[MAXOPER];

//equivalent of child(i)
void *child(void *ptr) {
	int i = (int) *ptr; //read from 2*i, read from 2*i+1, write to 2*i+2
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
		flags[2*i] = 0; 	//ready for next data
		flags[2*i+1] = 0; 	//ready for next data
		flags[2*i+2] = 1; 	//output ready


	}
}

int main() {

     pthread_t thread1;
     if (pthread_create(&thread1, NULL, add, NULL))
     	exit(1);

	while (1) {
		printf("Enter 2 numbers:\n");
		scanf("%d%d", &x, &y);
		xyflag = 1;
		while (!zflag) 
			;
		printf("result from add: %d\n\n", z);
		zflag=0;
	}
}


char operators[100];
int fds[100][2];
int operatorCount=0;
int numPipes=0;

void child(int index) {
	//CODE HERE!
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
	//create that many pipes using for loop
	
	//create children using another for loop
	
	//continue to read the input data file: while (fscanf(dataFile, "%d", &value)  > 0)
	//if one int can be read, go ahead and read the remaining data for that line.
}

