#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>

//read all the words from dictionary.txt
//when client asks for a motivational quote, select one randomly and send it out.

#define MAXWORDS 100000
#define MAXLEN 1000

char *words[MAXWORDS];
int numWords=0;

void pexit(char *errmsg) {
	fprintf(stderr, "%s\n", errmsg);
	exit(1);
}

int main() {
	char line[MAXLEN];

	FILE *fp = fopen("dictionary.txt", "r");
	if (!fp) {
		puts("dictionary.txt cannot be opened for reading.");
		exit(1);
	}
	int i=0;

	//read one line at a time, allocate memory, then copy the line into array
	while (fgets(line, MAXLEN, fp)) {
		char *cptr = strchr(line, '\n');
		if (cptr)
			*cptr = '\0';
		words[i] = (char *) malloc (strlen(line)+1);
		strcpy(words[i], line);
		i++;
	}

	numWords = i;
	printf("%d words were read.\n", numWords);

	srand(getpid() + time(NULL) + getuid());
	
	int listenfd = 0, connfd = 0;
	struct sockaddr_in serv_addr;

	char buffer[1025];
	time_t ticks;

	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		pexit("socket() error.");
	
	memset(&serv_addr, '0', sizeof(serv_addr));
	memset(buffer, '0', sizeof(buffer));
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int port = 4999;
	do{	
		port++;
		serv_addr.sin_port = htons(port);
	} while (bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0);
	printf("bind succeeds for port #%d\n", port);

	if(listen(listenfd, 10) < 0)
		pexit("listen() error.");
	
	int counter = 0;
	while(1)
	{
		connfd = accept(listenfd, (struct sockaddr*) NULL, NULL);
		counter++;
		printf("connected to client %d.\n", counter);
		if(fork() > 0)
			continue;
		srand(getpid() + time(NULL) + getuid());
		int n;
		
		// do something based on buffer and send that instead?
		// simply increment each character:
		// replace with hangman functionality?
			//for(int i = 0; i < n; i++)
				//buffer[i]++;
			//write(connfd, buffer, n);
			
		char *randWord = words[abs(rand() * rand())%numWords];
		int wordLen = strlen(randWord);
				
		char display[MAXLEN];
		for(i = 0; i < wordLen; i++)
			display[i] = '*';

		int unexposed = wordLen;
		char guess = ' ';
		int misses = 0;

		printf("%s\n\n",randWord);
		
		char extraRead[10];
		while (unexposed > 0) {
			// send client a prompt with the word to guess
			//fprintf(clientfp, "(Guess) Enter a letter in word %s > \n", display);
			sprintf(line, "(Guess) Enter a letter in word %s > ", display);
			write(connfd, line, strlen(line)+1);
			//fflush(clientfp);
			fflush(stdout);
				
			// scan guess from client
			//fgets(line, MAXLEN, serverfp);
				
			read(connfd, line, sizeof(line));
			guess = line[0];
				
			//char *cptr = strchr(line, '\n');
			//if(cptr)
			//	*cptr = '\0';

			bool found = false;
			// loop thru the random word
			for(i = 0; i < wordLen; i++)
				if (guess == randWord[i]) {
					found = true;
					if (guess == display[i]){
						//fprintf(clientfp, "\t%c is arleady in the word.\n", guess);
						//fflush(clientfp);
						sprintf(line, "\t%c is already in the word.\n", guess);
						write(connfd, line, strlen(line)+1);
						fflush(stdout);
						read(connfd, extraRead, sizeof(extraRead));
						break;
					} else {
						//good guess!
						display[i] = guess;
						unexposed--;
					}
				}
			if(!found) {
				sprintf(line, "\t%c is not in the word.\n", guess);
				write(connfd, line, strlen(line));
				fflush(stdout);
				misses++;	
				read(connfd, extraRead, sizeof(extraRead));
			}
		}
		//fprintf(clientfp, "The word is %s. You missed %d time\n", randWord, misses);
		//fflush(clientfp);
		sprintf(line, "The word is %s. You missed %d times\n", randWord, misses);
		write(connfd, line, strlen(line)+1);
		fflush(stdout);
			
		printf("served client %d.\n", counter);
		close(connfd);
		exit(0);
	}	
	fclose(fp);
}
