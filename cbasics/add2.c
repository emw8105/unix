#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int total = 0, value=0;
    while (scanf("%d", &value)) { //as long as valid inputs are coming!
        total += value;
	printf("Total so far: %d\n", total);
    }
    return 0;
}
