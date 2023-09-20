#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//for each line of input, add all the numbers in it and output it.
int main(int argc, char *argv[])
{
    char buffer[100]; // "10 20 30 40"
    while (fgets(buffer, 100, stdin)) {
    	int total = 0;
	//start the tokenizer & get first token
	char *token = strtok(buffer, " \n");
	while (token) {
        	total += atoi(token);
		//get the next token
		token = strtok(NULL, " \n");
	}
	printf("Total: %d\n", total);
    }
    return 0;
}
