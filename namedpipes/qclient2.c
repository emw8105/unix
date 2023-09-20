//Usage: quoteclient <server-fifo-filename>
//
//create own named pipe (fifo) and set permissions
//send this fifo name to server
//open own named pipe
//read the quote and display

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
	FILE *quotefp = fopen(clientfifo, "r");
	//read the quote!
	char buffer[MAXLEN] = "";
	fgets(buffer, MAXLEN, quotefp);
	puts(buffer);
	fclose(quotefp);

	unlink(clientfifo);
}
