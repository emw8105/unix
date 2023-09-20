#include <stdio.h>
#include <stdlib.h>
#include "const.h"


int main() {
	int **array = (int **) malloc(10 * sizeof(int *));
	for(int i=0; i<10; i++) {
		array[i] = (int *) malloc(100*sizeof(int));
	}
	for(int i=0; i<10; i++) {
		free(array[i]);
	}
	free(array);

}
