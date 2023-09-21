#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main() {
	//use current time to come with a random seed
	srand(time(NULL));
	//get a random number 1 to 100
	int number = rand() % 100 + 1;
	fprintf(stderr, "Random number: %d\n", number);

	int received;
	char line[100], response = ' ';

	while (response != '=') {
		fgets(line, 100, stdin);
		sscanf(line, "%d", &received);
	//keep reading a number, respond with < or > or =
	//while (read(0, &received, sizeof(int))> 0) {
		if (received < number)
			response = '>';
		else if (received > number)
			response = '<';
		else 
			response = '=';
		printf("%c\n", response);
		fflush(stdout);
		fprintf(stderr, "%c\n", response);
	}
	fputs("Child: done.\n",stderr);
}
