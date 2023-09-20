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

	printf("How many numbers? ");
	scanf("%d", &n);
	
	// write to text file
	int *numbers = (int *) malloc(n * sizeof(int));
	printf("Enter number:\n");
	for(int i = 0; i <n; i++) {
		scanf("%d", &numbers[i]);
	}
	FILE *fp = fopen("array.txt", "w");
	for(int i =0; i<n; i++)
		fprintf(fp, "%d ", numbers[i]);
	fclose(fp);
	
	// write to binary file using C library functions
	FILE *bfp = fopen("array.out", "wb");
	fwrite(&n, sizeof(int), 1, bfp); //write array size first
	fwrite(numbers, sizeof(int), n, bfp); // dump array contents
	fclose(bfp);
}
