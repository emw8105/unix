#include <stdlib.h>
#include <stdio.h>

int main() {
	// keep allocating bigger and bigger arrays!
	int *xp;
	long  n = 1;

	while(1) {
		xp = (int *) malloc (n * sizeof(int));
		if (!xp)
			break;
		printf("%ld 0x%x\n", n, xp);
		free(xp);
		n *= 2;
	}
}
