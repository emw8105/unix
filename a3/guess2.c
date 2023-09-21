#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{ 
    // guess2.c - computer thinks of number and computer guesses
    srand(time(NULL));

    int guess;
    int numGuesses = 0;
    int randNum = 1 + rand() % 100;
    printf("Ok, I am ready!\n");
    while(free) {
        printf("Enter your guess: ");
        scanf("%d", &guess);
        numGuesses++;
        if (randNum == guess) {
            printf("You got it in %d tries! ", numGuesses);
            break;
        }
        else if (randNum > guess) {
            printf("Go higher!\n");
        }
        else {  // randNum < guess
            printf("Go lower\n");
        }
    }

    return 0;
}

