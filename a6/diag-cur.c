#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define LINESIZE 16

//use one command line argument
int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: diagonal <textstring>\n");
		return -1;
	}
	
	//create a file so that 16 rows of empty will appear with od -c command
	int fd = open("diagonal.out", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	char space = ' ';
	for(int line=0; line<LINESIZE; line++)
		for(int column=0; column<LINESIZE; column++)
			write(fd, &space, 1);

	//Each line of od outputs 16 characters 
	//So, to make the output diagonal, we will use 0, 17, 34, ....
	
	int n = strlen(argv[1]);
	lseek(fd, (LINESIZE+1), SEEK_SET);
	for(int i=0; i<n; i++) {
		write(fd, &argv[1][i], 1);
		lseek(fd, (LINESIZE+1)*i, SEEK_CUR);
	}
	close(fd);
	puts("diagonal.out has been created. Use od -c diagonal.out to see the contents.");
}
