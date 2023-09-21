#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	srand(time(NULL) + getpid());

// randompwd <minLen> <maxLen> <minLower> <minUpper><minDigits> <minSpecial>
    // ex: randompwd 8 10 2 2 2 2

    // comment this out for using command line as variable inputs
/*
    int minLen = 8;
    int maxLen = 10;
    int minLower = 2;
    int minUpper = 2;
    int minDigits = 2;
    int minSpecial = 2;
*/

    // comment this out for just entering preset values into C
    char *a = argv[1];
    char *b = argv[2];
    char *c = argv[3];
    char *d = argv[4];
    char *e = argv[5];
    char *f = argv[6];

	int minLen = atoi(a);
    int maxLen = atoi(b);
    int minLower = atoi(c);
    int minUpper = atoi(d);
    int minDigits = atoi(e);
    int minSpecial = atoi(f);
    
    if (minLen < (minLower+minUpper+minDigits+minSpecial))
    {
        minLen = minLower+minUpper+minDigits+minSpecial;
    }

    int randLen = (rand() % (maxLen - minLen + 1)) + minLen;

    char password[randLen];
    char charList[100] = 
"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789@#$%^&*+:;";
    int randCharType;
    int randCharIndex;
	int i = 0;
    for (i = 0; i < randLen; i++)
    {
        int minValsLeft = minLower + minUpper + minDigits + minSpecial;
        if (minValsLeft == randLen-i)
        {
            randCharType = -1;
            while (randCharType == -1)
            {
                int randMinChoice = rand() % 4;
                switch(randMinChoice)
                {
                case 0:
                    if (minLower != 0)
                    {
                        randCharType = 0;
                    }
                    break;
                case 1:
                    if (minUpper != 0)
                    {
                        randCharType = 1;
                    }
                    break;
                case 2:
                    if(minDigits != 0)
                    {
                        randCharType = 2;
                    }
                    break;
                case 3:
                    if(minSpecial != 0)
                    {
                        randCharType = 3;
                    }
                    break;
                }
            }
        }
        else
        {
            randCharType = rand() % 4;
        }

        // based on randomized char type
        if(randCharType == 0)   // lowercase letters
        {
            randCharIndex = rand() % 26;
            //strncat(password, &charList[randCharIndex], 1);
            if (minLower > 0) {
                minLower--;
            }
        }
        else if (randCharType == 1)   // uppercase letters
        {
            randCharIndex = (rand() % 26) + 26;
            if (minUpper > 0) {
                minUpper--;
            }
        }
        else if (randCharType == 2)   // digits
        {
            randCharIndex = (rand() % 10) + 52;
            if (minDigits > 0) {
                minDigits--;
            }
        }
        else if (randCharType == 3)   // special chars
        {
            randCharIndex = (rand() % 10) + 62;
            if (minSpecial > 0) {
                minSpecial--;
            }
        }
        password[i] = charList[randCharIndex];
    }
    password[randLen] = '\0';
    printf("%s\n", password);

    return 0;
}
