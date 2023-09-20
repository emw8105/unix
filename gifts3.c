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
	//code here!
	FILE *filep = fopen("gifts3.dat", "wb");
	int n = 5; //let us assume players
	fwrite(players, sizeof(struct Player), 5, filep);
	fclose(filep);
}
