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

int main(int argc, char *argv[]) {	

	FILE *filep;
	int i;
	if(argc > 2 && strcmp(argv[1], "new") == 0) {
		//if first word is new, user wants to create a new game
		numPlayers = (argc-2)/2;
		int j = 2;
		for (i = 0; i < numPlayers; i++) {
			strcpy(names[i], argv[j++]);
			balances[i] = atof(argv[j++]);
		}
	}
	else {	
		// game has already started, therefore file already has data, so read file 
		filep = fopen("gifts1.txt", "r"); // open the file for reading
		numPlayers = 0;
		while (fscanf(filep, "%s %lf", names[numPlayers], &balances[numPlayers])==2) {
			// read in the values stored in the file at indexes determined by the incremental numPlayers
			numPlayers++;
		}
		fclose(filep);
		// one fscanf reads nothing, loop will stop, values will be in arrays and numPlayers will be initialized
		
		// determine how much the player is giving with argv[2]

		// find the index of argv[1] in the name array with findIndex
			// subtract the give amount in the same index from the balance array
			i = findIndex(argv[1]);
			if (i == -1) {
				printf("Player not found\n");
			}
			double payment = atof(argv[2]);
			balances[i] -= payment;

			// divide argv[2] by (argc-3) to get the amount of names that the payment is being divied up between, not just every player
			int numGifts = (argc-3);
			payment /= numGifts;
			// loop through values of argv and keep searching for that name with findIndex
				// when a player's index is found from their name, add the give amount to their index in the balance array
			for(i = 0; i < numGifts; i++) {
				balances[findIndex(argv[i+3])] += payment;
			}
		}
		filep = fopen("gifts1.txt", "w");
		for (i = 0; i < numPlayers; i++) {
			// loop thru and write the data to both the console and the file
			fprintf(filep, "%s %lf\n", names[i], balances[i]);
			printf("%10s: %6.2lf\n", names[i], balances[i]);
		}
		fclose(filep);
		return 0;
	}
