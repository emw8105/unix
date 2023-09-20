#include <stdio.h>
#include <unistd.h>

int main() {
	int low=1, high=100;

	while (low <= high) {
		int mid = (low + high)/2;
		printf("Is it %d (<,>,=)? ", mid);

		char response[11];
		//read one line
		fgets(response, 11, stdin);

		if (response[0] == '<')
			high = mid-1;
		else if (response[0] == '>')
			low = mid+1;
		else if (response[0] == '=') {
			puts("Great game!");
			break;
		} else
			printf("Bad input %s\n", response);
	}
}
