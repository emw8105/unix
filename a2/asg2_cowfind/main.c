// in class activity, check whether all arguments are of length 5

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXLEN 1000000

char input[MAXLEN];

int main()
{
    scanf("%s", input);


    //cowfind1 : brute force method - O(N^2)
    // loop through contents of input string
    // if 2 open parenthesis are found, loop through the remaining indexes
    // if another pair of closed parenthesis is found, add 1 to counter
    // one end of array is reached, continue from original index and loop for 2 open parenthesis
    // output counter at the end
    /*int counter = 0;
    for(int i = 0; i < strlen(input)-1; i++)
    {
        if(input[i] == '(' && input[i+1] == '(')
        {
            for(int j = i+1; j < strlen(input)-1; j++)
            {
                if(input[j] == ')' && input[j+1] == ')')
                {
                    counter++;
                }
            }
        }
    }*/

    //cowfind2 : efficient method - O(N)
    // keep a counter of the amount of double open parenthesis
    // when finding a double close parenthesis, multiply it by the # of open parenthesis
    int numOpen = 0;
    int counter = 0;
    for(int i = 0; i < strlen(input)-1; i++) {
        if(input[i] == '(' && input[i+1] == '(') {
            numOpen++;
        }
        else if(input[i] == ')' && input[i+1] == ')') {
            counter += numOpen;
        }
    }

    printf("%i\n", counter);
}
