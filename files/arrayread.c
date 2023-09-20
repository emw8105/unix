// ask the user for full name, age, gpa
// dump everything into a binary file
// dump everything into a text file too

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {
	int n = 0;
	FILE *bfp = fopen("array.out", "rb");
	fread(&n, sizeof(int), 1, bfp);
	int *numbers = (int *) malloc(n*sizeof(int));
	fwrite(numbers, sizeof(int), n, bfp); // dump array contents
	fclose(bfp);

	for(int i=0; i<n; i++) {
		printf("%d", numbers[i]);
	}
	putchar('\n');
}
