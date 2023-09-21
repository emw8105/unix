#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdbool.h>

//read all the quotes from quotes.txt
//when client asks for a motivational quote, select one randomly and send it out.

#define MAXWORDS 100000
#define MAXLEN 1000

char *words[MAXWORDS];
int numWords=0;

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
						
				//srand(getpid() + time(NULL) + getuid());	
				FILE *clientfp = fopen(line, "w");
				
		
				char* randWord = words[rand()*numWords];
				
				printf("%s\n", randWord);
				int wordLen = strlen(randWord);
				char display[MAXLEN];
				int i = 0;
				for (i=0; i < wordLen; i++) {
					display[i] = '*';
				}


				// create and send new server fifo to the client
				// and for private one on one communications
				char serverfifo[MAXLEN];
				sprintf(serverfifo, "/tmp/%s-%d", getenv("USER"), getppid());
				mkfifo(serverfifo, 0600);
				chmod(serverfifo, 0622);

				fprintf(clientfp, "%s\n", serverfifo);
				fflush(clientfp);

				FILE *serverfp = fopen(serverfifo, "r");

				int hidden = wordLen; // set to word length
				char guess = ' ';
				int misses = 0;
				printf("%s\n", randWord);
				while(hidden > 0) {

					// client requests a specific character	
					fprintf(clientfp, "(Guess) Enter a letter in word %s >\n", display);
					fflush(clientfp);
					// do a wait here or something idk?

					fgets(line, MAXLEN, serverfp);
					char *cptr = strchr(line, '\n');
					if(cptr)
						*cptr = '\0';
					guess = line[0];

					bool found = false;
         			for(int i=0; i<wordLen; i++)            
		 				if (guess == randWord[i]) {
                    		found = true;
                    		if (guess == display[i]) {
								fprintf(clientfp, "%s is already in the word.\n", guess);
								fflush(clientfp);
								break;
	                    	} else {
	                        	//good guess!
		                    	display[i] = guess;
		                    	hidden--;
		                    }
		                }
			        if (!found) {
			        	misses++;
				 	}   
				}
				fprintf(clientfp, "The word is %s. You missed %d times", randWord, misses);
				fflush(clientfp);
				unlink(serverfifo);
			}
		}
		fclose(fp);
	}
}
