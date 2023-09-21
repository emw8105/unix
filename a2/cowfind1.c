#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXLEN 1000000
char input[MAXLEN];

int main() {
	scanf("%s", input);

	int counter = 0;
	for(int i = 0; i < strlen(input)-1; i++){
		if(input[i] == '(' && input[i+1] == '('){
			for(int j = i+1; j < strlen(input)-1; j++){
				if(input[j] == ')' && input[j+1] == ')'){
					counter++;
				}
			}
		}
	}
	printf("%i\n", counter);
}
