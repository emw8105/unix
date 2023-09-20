#include <stdio.h>
#include <unistd.h>

int main() {
	int p = fork();
	int n;
	printf("Enter value: ");
	scanf("%d", &n);
	printf("n = %d\n", n);
	if (p)
		wait(NULL);
}
