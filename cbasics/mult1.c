#include <stdio.h>

int main()
{
    //get a number from the user
    int number = 0;
    printf("Enter number: ");
    scanf("%d", &number); // %f - float, %lf - double, %ld - long
    
    //generate multiplication table 1 to 10
    for(int i=1; i<=10; i++)
        printf("%d * %d = %d\n", number, i, number*i);

    return 0;
}
