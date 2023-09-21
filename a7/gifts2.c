#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//let us assume that there will not be more than 100 players
#define MAXPLAYERS 100
//let us assume that max length for any name is 100 characters
#define MAXLEN 100

//arrays to store the player names and balances
char names[MAXPLAYERS][MAXLEN];
double balances[MAXPLAYERS];
int numPlayers = 0; //set when actual player data is loaded

//search the player names array and return the index if specified name is found
//return -1 otherwise.
int findIndex(char *name) {
        for(int i=0; i<numPlayers; i++)
            if(strcmp(name, names[i]) == 0)
               return i;

        return -1;
}

// use binary data file gifts2.dat to read and store the results.

int main(int argc, char *argv[])
{	
	int fd;
	int i;
	if(argc > 2 && strcmp(argv[1], "new") == 0) {
		// if first word is new, user wants to create a new game
		numPlayers = (argc-2)/2;
		int j = 2;
		for (i = 0; i < numPlayers; i++) {
			strcpy(names[i], argv[j++]);
			balances[i] = atof(argv[j++]);
		}
	}
	else {
	// game has already started, therefore file already has data, so read file data
		fd = open("gifts2.dat", O_RDONLY); // open the file for reading
		if (fd == -1) {
			perror("Error opening file");
		}
		numPlayers = 0;
		while(read(fd, names[numPlayers], sizeof(names[numPlayers])) > 0 &&
		read(fd, &balances[numPlayers], sizeof(double)) > 0) {
			numPlayers++;
		}
		close(fd);
		
		int i = findIndex(argv[1]);
		if (i == -1) {
			printf("Player not found\n");
		}
		double payment = atof(argv[2]);
		balances[i] -= payment;
		int numGifts = argc-3; // subtract the initial parameters, everyone else is a recipient of the gift
		payment /= numGifts; // split the gift amongst the recipients
		for(i = 0; i < numGifts; i++) {
			int recpInd = findIndex(argv[i+3]);
			balances[recpInd] += payment;
		}
	}
	fd = open("gifts2.dat", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	for (i = 0; i < numPlayers; i++) {
		write(fd, &names[i], sizeof(names[i]));
		write(fd, &balances[i], sizeof(balances[i]));
		printf("%10s: %6.2lf\n", names[i], balances[i]);
	}
	close(fd);

	return 0;

	//write(fd, balances, sizeof(double));
	//close(fd);
}
