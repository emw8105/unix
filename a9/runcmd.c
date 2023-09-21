#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	//write one line exec...() 
	execvp(argv[1], argv+1);
	execvp(argv[1], &argv[1]);
	execvp(argv[0], ++argv);
}
