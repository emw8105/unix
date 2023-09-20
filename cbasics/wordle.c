#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    for(int i=1; i<argc; i++)
        if (strlen(argv[i]) != 5) {
		printf("Bad!\n");
		return 1;
	}

    printf("Good!\n");

    return 0;
}
