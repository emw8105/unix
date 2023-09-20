#include <stdio.h>
#include <stdlib.h>

// atoi(argv[1]) + atoi(argv[2]) + .... + atoi(argv[argc-1])
int main(int argc, char *argv[])
{
    int total = 0;
    for(int i=1; i<argc; i++)
        total += atoi(argv[i]);

    printf("Total: %d\n", total);

    return 0;
}
