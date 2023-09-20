#include <stdio.h>
#include <stdlib.h>

//command line arguments
int main(int argc, char *argv[])
{
    int number = atoi(argv[1]);   
    //generate multiplication table 1 to 10
    for(int i=1; i<=10; i++)
        printf("%d * %d = %d\n", number, i, number*i);

    return 0;
}
