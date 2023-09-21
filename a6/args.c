#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
	for(int i=1; i<argc; i++) {
		int n = strlen(argv[i]);
		printf("%d %s\n", n, argv[i]);
	}
}
