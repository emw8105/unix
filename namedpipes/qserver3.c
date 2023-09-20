#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

//read all the quotes from quotes.txt
//when client asks for a motivational quote, select one randomly and send it out.

#define MAXQUOTES 10000
#define MAXLEN 1000

char *quotes[MAXQUOTES];
int numQuotes=0;

int main() {
	char line[MAXLEN];

	FILE *fp = fopen("quotes.txt", "r");
	if (!fp) {
		puts("quotes.txt cannot be opened for reading.");
		exit(1);
	}
	int i=0;

	//read one line at a time, allocate memory, then copy the line into array
	while (fgets(line, MAXLEN, fp)) {
		quotes[i] = (char *) malloc (strlen(line)+1);
		strcpy(quotes[i], line);
		i++;
	}
	numQuotes = i;
	printf("%d quotes were read.\n", numQuotes);

	srand(getpid() + time(NULL) + getuid());
	// puts(quotes[rand() % numQuotes]);
	
	//create a named pipes to read client's requests
	char filename[MAXLEN];
	sprintf(filename, "/tmp/%s-%d", getenv("USER"), getpid());
	mkfifo(filename, 0600);
	chmod(filename, 0622);
	printf("Send your requests to %s\n", filename);

	while (1) {
		FILE *fp = fopen(filename, "r");
		if (!fp) {
			printf("FIFO %s cannot be opened for reading.\n", filename);
			exit(2);
		}
		printf("Opened %s to read...\n", filename);
		while (fgets(line, MAXLEN, fp)) {

			// "fifoname 5\n" --> "fifoname" and 5
			// "fifoname\n" --> "fifoname" and 1
			char *clientfifo = strtok(line, " \n");
			char *temp = strtok(NULL, " \n");
			// did client send #?
			int clientQuotes = 1;
			if (temp)
				clientQuotes = atoi(temp);

			char *cptr = strchr(line, '\n');
			if (cptr) 
				*cptr = '\0';
	
			int quoteNumber = rand() % numQuotes;
			//create a child to send the response.
			if (fork() == 0) {
				FILE *clientfp = fopen(line, "w");
				printf("%s: ", line);
				if (clientfp) {
					//send as many quotes as requested.
					for(int i=0; i<clientQuotes; i++) {
						printf("%s", quotes[quoteNumber]);
						fputs(quotes[quoteNumber], clientfp);
						quoteNumber = rand() % numQuotes;
					}
					fclose(clientfp);
				}
				putchar('\n');
				exit(0);
			}
		}
		fclose(fp);
	}
}
