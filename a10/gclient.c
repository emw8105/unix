/* make up unique pipename for client
 * send it to the server (public pipe)
 * get another unique pipename from the server
 * repeat
 * 	read a line including starred word from the client pipe
 *  display that line to the user 
 *  check whether game is over?
 *  get the user's guess letter
 *  send to the server using server pipe
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAXLEN 1000

int main(int argc, char *argv[]) {	
	if (argc !=2) {
		puts("Usage: qclient <server-fifo-name>");
		exit(1);
	}

	// argv[1] is the server fifo name

    char clientfifo[MAXLEN];
	sprintf(clientfifo, "/tmp/%s-%d", getenv("USER"), getpid());
	mkfifo(clientfifo, 0600);
	chmod(clientfifo, 0622);
	
	//open argv[1] for writing, send clientfifo
	FILE *fp = fopen(argv[1], "w");

	//fputs(clientfifo, fp);
	//add \n after clientfifo to avoid potential race conditions in server
	fprintf(fp, "%s\n", clientfifo);
	fclose(fp);

	//open clientfifo for reading and read the quote & print in the screen - improve your life! :-)
	FILE *clientfp = fopen(clientfifo, "r");
	//read the new server-fifo, then open it for writing! as serverfp
	char serverfifo[MAXLEN];
	//fgets(serverfifo, clientfp); -- fscanf() is better! No need to worry about \n
	fscanf(clientfp, "%s", serverfifo);
	char line[MAXLEN];
	fgets(line, MAXLEN, clientfp); //get rid of \n

	FILE *serverfp = fopen(serverfifo, "w");
	//loop:
	//  read user input
	//  send it to server
	//  get the quote
	//  display
	while (fgets(line, MAXLEN, clientfp)) {
		if (line[0] == '(') {
			char *cptr = strchr(line, '\n');
			if(cptr)
				*cptr = '\0';
			printf("%s", line);
			char buffer[10];
			scanf("%s", &buffer);

			// send that letter to server
			fprintf(serverfp, "%c\n", buffer[0]);
			fflush(serverfp);
			continue;
		} else {
			printf("%s", line);
		}
		// if line starts with "The word is"
		if(line[0] == 'Y') {
			break;
		}
	}

	fclose(clientfp);
	unlink(clientfifo);
}
