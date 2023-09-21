#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

#define MAXPLAYERS 100
#define MAXLEN 100

char names[MAXPLAYERS][MAXLEN];
double balances[MAXPLAYERS];
int numPlayers = 0;

int findIndex(char *name) {
    for(int i=0; i<numPlayers; i++) {
        if(strcmp(name, names[i]) == 0)
            return i;
    }
    return -1;
}

// GIFTS1.C
int main(int argc, char *argv[])
{
    FILE *filep;
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
        filep = fopen("gifts1.txt", "r"); // open the file for reading
        numPlayers = 0;
        while (fscanf(filep, "%s %lf", names[numPlayers], &balances[numPlayers])==2) {
            // read in the values stored in the file at indexes determined by the incremental numPlayers
            numPlayers++;
        }
        fclose(filep);

        int i = findIndex(argv[1]);
        if (i == -1) {
            printf("Player not found\n");
            return 1;
        }
        double payment = atof(argv[2]);
        balances[i] -= payment;
        int numGifts = argc-3; // subtract the initial parameters, everyone else is a recipient of the gift
        payment /= numGifts; // split the gift amongst the recipients
        for(i = 0; i < numGifts; i++) {
            balances[findIndex(argv[i+3])] += payment;
        }
    }
    filep = fopen("gifts1.txt", "w");
    for (i = 0; i < numPlayers; i++) {
        // loop thru and write the data to both the console and the file
        fprintf(filep, "%s %lf\n", names[i], balances[i]);
        printf("%10s %6.2lf\n", names[i], balances[i]);
    }
    fclose(filep);

    return 0;
}

/* GIFTS2.C
  1 #include <fcntl.h>
  2 #include <sys/types.h>
  3 #include <sys/stat.h>
  4 #include <string.h>
  5 #include <stdio.h>
  6 #include <stdlib.h>
  7 #include <unistd.h>
  8
  9 //let us assume that there will not be more than 100 players
 10 #define MAXPLAYERS 100
 11 //let us assume that max length for any name is 100 characters
 12 #define MAXLEN 100
 13
 14 //arrays to store the player names and balances
 15 char names[MAXPLAYERS][MAXLEN];
 16 double balances[MAXPLAYERS];
 17 int numPlayers = 0; //set when actual player data is loaded
 18
 19 //search the player names array and return the index if specified name is fou    nd
 20 //return -1 otherwise.
 21 int findIndex(char *name) {
 22         for(int i=0; i<numPlayers; i++)
 23             if(strcmp(name, names[i]) == 0)
 24                return i;
 25
 26         return -1;
 27 }
 28
 29 // use binary data file gifts2.dat to read and store the results.
 30
 31 int main(int argc, char *argv[])
 32 {
 33     int fd;
 34     int i;
 35     if(argc > 2 && strcmp(argv[1], "new") == 0) {
 36         // if first word is new, user wants to create a new game
 37         numPlayers = (argc-2)/2;
 38         int j = 2;
 39         for (i = 0; i < numPlayers; i++) {
 40             strcpy(names[i], argv[j++]);
 41             balances[i] = atof(argv[j++]);
 42         }
 43     }
 44     else {
 45     // game has already started, therefore file already has data, so read fil    e data
 46         fd = open("gifts2.dat", O_RDONLY); // open the file for reading
 47         if (fd == -1) {
 48             perror("Error opening file");
 49         }
 50         numPlayers = 0;
 51         while(read(fd, names[numPlayers], sizeof(names[numPlayers])) > 0 &&
 52         read(fd, &balances[numPlayers], sizeof(double)) > 0) {
 53             numPlayers++;
 54         }
 55         close(fd);
 56
 57         int i = findIndex(argv[1]);
 58         if (i == -1) {
 59             printf("Player not found\n");
 60         }
 61         double payment = atof(argv[2]);
 62         balances[i] -= payment;
 63         int numGifts = argc-3; // subtract the initial parameters, everyone e    lse is a recipient of the gift
 64         payment /= numGifts; // split the gift amongst the recipients
 65         for(i = 0; i < numGifts; i++) {
 66             int recpInd = findIndex(argv[i+3]);
 67             balances[recpInd] += payment;
 68         }
 69     }
 70     fd = open("gifts2.dat", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
 71     for (i = 0; i < numPlayers; i++) {
 72         write(fd, &names[i], sizeof(names[i]));
 73         write(fd, &balances[i], sizeof(balances[i]));
 74         printf("%10s: %6.2lf\n", names[i], balances[i]);
 75     }
 76     close(fd);
 77
 78     return 0;
 79
 80     //write(fd, balances, sizeof(double));
 81     //close(fd);
 82 }

*/

/* GIFTS3.C
  1 #include <fcntl.h>
  2 #include <sys/types.h>
  3 #include <sys/stat.h>
  4 #include <string.h>
  5 #include <stdio.h>
  6 #include <stdlib.h>
  7 #include <unistd.h>
  8
  9 //let us assume that there will not be more than 100 players
 10 #define MAXPLAYERS 100
 11 //let us assume that max length for any name is 100 characters
 12 #define MAXLEN 100
 13
 14 struct Player {
 15     char name[MAXLEN];
 16     double balance;
 17 } ;
 18
 19 //struct is like class - we can use an array of struct (we can use like an ar    ray of objects).
 20 struct Player players[MAXPLAYERS];
 21 int numPlayers = 0; //set when actual player data is loaded
 22
 23 //search the player names array and return the index if specified name is fou    nd
 24 //return -1 otherwise.
 25 int findIndex(char *name) {
 26         for(int i=0; i<numPlayers; i++)
 27             if(strcmp(name, players[i].name) == 0)
 28                return i;
 29
 30         return -1;
 31 }
 32
 33 // use binary data file gifts2.dat to read and store the results.
 34
 35 int main(int argc, char *argv[]) {
 36     if (argc > 2 && strcmp(argv[1], "new") == 0) {
 37         numPlayers = (argc-2)/2;
 38         int j = 2;
 39         for(int i = 0; i < numPlayers; i++) {
 40             strcpy(players[i].name, argv[j++]);
 41             players[i].balance = atof(argv[j++]);
 42         }
 43     }
 44     else {
 45         FILE *filep = fopen("gifts3.dat", "rb");
 46         while(fread(&players[numPlayers], sizeof(struct Player), 1, filep) ==     1) {
 47             numPlayers++;
 48         }
 49         fclose(filep);
 50
 51         int i = findIndex(argv[1]);
 52         if (i == -1) {
 53             printf("Player not found\n");
 54             return -1;
 55         }
 56         double payment = atof(argv[2]);
 57         players[i].balance -= payment;
 58         int numGifts = argc-3;
 59         payment /= numGifts;
 60         for (i = 0; i < numGifts; i++) {
 61             int recpInd = findIndex(argv[i+3]);
 62             players[recpInd].balance += payment;
 63         }
 64     }
 65
 66     FILE *filep = fopen("gifts3.dat", "wb");
 67     for (int i = 0; i < numPlayers; i++) {
 68         fwrite(&players[i], sizeof(struct Player), 1, filep);
 69         printf("%10s: %6.2lf\n", players[i].name, players[i].balance);
 70     }
 71     fclose(filep);
 72
 73     return 0;
 74 }

*/

/* PROMPT:
A bunch of friends are coming together to play a game like Monopoly. They all start with the specified initial balance. As the game proceeds, in each transaction, one player divides a specific amount of money equally and gives it to specific folks. After each transaction, output the current balance for each palyer.

We will develop 3 versions of the program, but their functionality will be exactly same. They should keep track of the balance amounts for each player, using text or binary files. Program will be run to setup once, then for each transaction, using command line parameters as shown below. Use a text or binary file to keep track of the names and current balances. No need to worry about negative balances, etc. Commands are in BOLD. We attach a special meaning to "new" when it appears as the first parameter - that means a fresh start - new set of friends with new balances. Format the output nicely using format string in printf(). Use 2 decimal places for points, just like real money.

gifts1 new Jey 100 John 200 Nhut 300 Miguel 400

Jey: 100.00
John: 200.00
Nhut: 300.00
Miguel: 400.00



gifts1 Jey 100 John Miguel

Jey:   0.00
John: 250.00
Nhut: 300.00
Miguel: 450.00



gifts1 Nhut 150 Jey John Miguel

Jey:  50.00
John: 300.00
Nhut: 150.00
Miguel: 500.00



gifts1 John 300 Nhut

Jey:  50.00
John:   0.00
Nhut: 450.00
Miguel: 500.00



gifts1 Miguel 200.50 Jey John

Jey: 150.25
John: 100.25
Nhut: 450.00
Miguel: 299.50

(Same commands should work for gifts2 and gifts3 as well). Here is the starter code:
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

#define MAXPLAYERS 100
#define MAXLEN 100

char names[MAXPLAYERS][MAXLEN];
double balances[MAXPLAYERS];
int numPlayers = 0;

int findIndex(char *name) {
    for(int i=0; i<numPlayers; i++) {
        if(strcmp(name, names[i]) == 0)
            return i;

    return -1;
    }
}
int main(int argc, char *argv[]) {
// code here
FILE = *filep = fopen("gifts1.txt", "w");
int n = 5; // assumed amount of players
fprintf(filep, "%s %lf\n", names[0], balances[0]);
close(filep);

gifts1.c - use fopen(), fscanf() and fprintf(). Use text data file gifts1.txt
*/
