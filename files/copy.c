#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFSIZE 100000
char buf[BUFFSIZE];
int main(int argc, char *argv[]) {
	int length = atoi(argv[1]);
	int n = 0;

	while ((n = read(0, buf, length)) > 0)
		write(1, buf, n);
	}

