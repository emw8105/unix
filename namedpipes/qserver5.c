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

		//wait for clients' requests
		while (fgets(line, MAXLEN, fp)) {

			char *cptr = strchr(line, '\n');
			if (cptr) 
				*cptr = '\0';
	
			//create a child to work with this client
			if (fork() == 0) {
				FILE *clientfp = fopen(line, "w");
				//create and send new server fifo to the client
				//for private one-on-one communcations
				char serverfifo[MAXLEN];
				sprintf(serverfifo, "/tmp/%s-%d", getenv("USER"), getpid());
				mkfifo(serverfifo, 0600);
				chmod(serverfifo, 0622);

				fprintf(clientfp, "%s\n", serverfifo);
				fflush(clientfp);

				FILE *serverfp = fopen(serverfifo, "r");
				/*
				 while (fscanf(serverfp, "%d", &requestNum)) {
					//client is asking for specific quote# - send that quote!
					fprintf(clientfp, "%s", quotes[requestNum]);
					fflush(clientfp);
					printf("%d: %s\n", requestNum, quotes[requestNum]);
				} */

				int fromQuote=0,toQuote=0;
				while (fgets(line, MAXLEN, serverfp)) {
					int n = sscanf(line, "%d-%d", &fromQuote, &toQuote);
					//avoid out-of-bound quote requests
					if (fromQuote < 0)
						fromQuote = -fromQuote;
					if (toQuote < 0)
						toQuote = -toQuote;

					fromQuote %= numQuotes;
					toQuote %= numQuotes;

					if (n == 1)
						toQuote = fromQuote;
					if (n > 0) {
						for(int index=fromQuote; index<=toQuote; index++)  {
							fprintf(clientfp, "%s", quotes[index]);
							printf("%d: %s\n", index, quotes[index]);
						}
						fflush(clientfp);
					}
				}

				exit(0);
			}
		}
		fclose(fp);
	}
}
