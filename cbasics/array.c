#include <stdio.h>
#include <stdlib.h>
#include "const.h"


int main() {
	char *line = malloc(MAXLEN);
	
	printf("Input: ");
	scanf("%s", line);
	puts(line);

	free(line);
}
