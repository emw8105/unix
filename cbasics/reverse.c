#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    for(int i=argc-1; i > 0; i--) {
	for(int j=strlen(argv[i])-1; j>=0; j--)
		putchar(argv[i][j]);
    	putchar(' ');    
    }
    printf("\n");
    return 0;
}
