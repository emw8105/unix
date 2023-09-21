#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXLEN 1000000
char input[MAXLEN];

int main() {
	scanf("%s", input);

	int numOpen = 0;
	int counter = 0;
	for(int i = 0; i < strlen(input)-1; i++) {
		if(input[i] == '(' && input[i+1] == '(') {
			numOpen++;
		}
		else if(input[i] == ')' && input[i+1] == ')') {
			counter += numOpen;
		}
	}
	printf("%i\n", counter);
}
