#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{  
    int number = getpid();
    //generate multiplication table 1 to 10
    for(int i=1; i<=10; i++)
        printf("%d * %d = %d\n", number, i, number*i);

    return 0;
}
