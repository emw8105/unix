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

struct Player {
	char name[MAXLEN];
	double balance;
} ;

//struct is like class - we can use an array of struct (we can use like an array of objects).
struct Player players[MAXPLAYERS];
int numPlayers = 0; //set when actual player data is loaded

//search the player names array and return the index if specified name is found
//return -1 otherwise.
int findIndex(char *name) {
        for(int i=0; i<numPlayers; i++)
            if(strcmp(name, players[i].name) == 0)
               return i;

        return -1;
}

// use binary data file gifts2.dat to read and store the results.

int main(int argc, char *argv[]) {
	if (argc > 2 && strcmp(argv[1], "new") == 0) {
		numPlayers = (argc-2)/2;
		int j = 2;
		for(int i = 0; i < numPlayers; i++) {
			strcpy(players[i].name, argv[j++]);
			players[i].balance = atof(argv[j++]);
		}
	}
	else {
		FILE *filep = fopen("gifts3.dat", "rb");
		while(fread(&players[numPlayers], sizeof(struct Player), 1, filep) == 1) {
			numPlayers++;
		}
		fclose(filep);

		int i = findIndex(argv[1]);
		if (i == -1) {
			printf("Player not found\n");
			return -1;
		}
		double payment = atof(argv[2]);
		players[i].balance -= payment;
		int numGifts = argc-3;
		payment /= numGifts;
		for (i = 0; i < numGifts; i++) {
			int recpInd = findIndex(argv[i+3]);
			players[recpInd].balance += payment;
		}
	}

	FILE *filep = fopen("gifts3.dat", "wb");
	for (int i = 0; i < numPlayers; i++) {
		fwrite(&players[i], sizeof(struct Player), 1, filep);
		printf("%10s: %6.2lf\n", players[i].name, players[i].balance);
	}
	fclose(filep);
	
	return 0;
}
