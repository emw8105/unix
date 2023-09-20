#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	if (fork()) {
		; //parent ends immediately!
	} else {
		while (1) {
			int x;
			if (scanf("%d", &x) == 1)
				printf("child: %d\n", x);
			else {
				printf("cannot read input.\n");
				return -1;
			}
		}
	}
}
