#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int number = atoi(argv[1]);
	int maxCount = atoi(argv[2]);
	for(int i=1 ; i<=maxCount; i++)
		if (!fork()) {
			printf("%4d * %2d = %6d\n", number, i, number*i);
			break;
		}
}
