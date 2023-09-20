#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{  
    srand(time(NULL));
    int number = rand() % 1000 + 1;
    //generate multiplication table 1 to 10
    for(int i=1; i<=10; i++)
        printf("%d * %d = %d\n", number, i, number*i);

    return 0;
}
