#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define LINESIZE 16

//use one command line argument
int main(int argc, char *argv[]) {
		if (argc < 2) {
				printf("Usage: diagonal2 <textstring>\n");
				return -1;
		}

		//create a file so that 16 rows of empty will appear with od -c command
		int fd = open("diagonal2.out", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
		char space_char = ' ';
		for(int line=0; line<LINESIZE*LINESIZE; line++) {
				for(int column=0; column<LINESIZE*LINESIZE; column++) {
						write(fd, &space_char, 1);
				}
		}

		int count = 1;
		int len = argc-1;
		
		// loops until there are no more words
		while(count<argc) {
			int n = strlen(argv[count]);
			int space = LINESIZE * LINESIZE * (count - 1);

			//go left to right
			if((count%2) == 1) {
				for(int i=0; i<n; i++) {
					lseek(fd, space + (LINESIZE+1)*i, SEEK_SET);
					write(fd, &argv[count][i], sizeof(char));
					//write(fd, &argv[count][i], sizeof(char)*(n-i));
				}
			}

			//go right to left
			else {
				for(int j=n-1; j>=0; j--) {
					lseek(fd, space + (LINESIZE)*(j+1)-(j+1), SEEK_SET);
					write(fd, &argv[count][j], sizeof(char));
					//write(fd, &argv[count][j], sizeof(char)*(n-j));
				}
			}
			count++;
		}
		close(fd);
		puts("diagonal2.out has been created. Use od -c diagonal2.out to see the contents.");
}
