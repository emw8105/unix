#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main() {
	int low=1, high=100;

	while (low <= high) {
		//compute midpoint
		int mid = (low + high)/2;
		//display it and ask the question
		fprintf(stderr, "mid: %d\n", mid);
		printf("%d (<,=,>)?\n", mid);
		fflush(stdout);
		char response[10];
		fgets(response, 10, stdin);

		//adjust the range based on the response
		if (response[0] == '<')
			high = mid-1;
		else if (response[0] == '>')
			low = mid+1;
		else if (response[0] == '=') {
			fputs("Great game!\n", stderr);
			break;
		} else
			fprintf (stderr, "Bad char %c\n", response);
	}
}

