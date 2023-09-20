#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main() {
	int low=1, high=100;

	while (low <= high) {
		int mid = (low + high)/2;
		printf("Is it %d (<,>,=)? ", mid);

		char response = getchar();
		getchar(); //to remove \n from input buffer
		//scanf("%c", &response);

		if (response == '<')
			high = mid-1;
		else if (response == '>')
			low = mid+1;
		else if (response == '=') {
			puts("Great game!");
			break;
		} else
			printf ("Bad char %c", response);
	}
}
