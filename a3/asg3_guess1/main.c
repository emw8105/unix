#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{

    /* //guess1.c - user thinks of number and computer guesses
    char input;
    int upper = 100;
    int lower = 0;
    int interval = 50;
    int guess = (upper+lower)/2;

    while(input != '=') {
        printf("How about %d (<, =, >)? ", guess);
        scanf("%s", &input);

        if (input == '=') {
            printf("It was a good game!\n");
            break;
        }
        else if(input == '<') {
            upper -= interval;
        }
        else if(input == '>') {
            lower += interval;
        }
        guess = (upper+lower)/2;
        if (interval != 1)
            interval /= 2;
        else
            interval = 1;
    }
    */

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
            printf("You got it in %d tries! \n", numGuesses);
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
