#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char str1[100], str2[200];
    fgets(str1, 100, stdin);
    fgets(str2, 100, stdin);

    // remove whitespaces and convert all characters to lowercase in str1
    int i = 0, j = 0;
    while(str1[i] != '\0') {
        if(!isspace(str1[i])) {
            str1[j] = tolower(str1[i]);
            j++; // if the value is not a whitespace, convert to lowercase and save back into the array
        }
        i++; // if the index has a whitespace, skip this index
    }
    str1[j] = '\0'; // put null terminator at the end so strcmp knows where to stop

    // remove whitespaces and convert all characters to lowercase in str2
    i = 0, j = 0;
    while(str2[i] != '\0') {
        if(!isspace(str2[i])) {
            str2[j] = tolower(str2[i]);
            j++; // if the value is not a whitespace, convert to lowercase and save back into the array
        }
        i++; // if the index has a whitespace, skip this index
    }
    str2[j] = '\0'; // put null terminator at the end so strcmp knows where to stop

    // use strcmp to compare the reduced strings and determine if they are the same
    printf("%s\n", str1);
    printf("%s\n", str2);

    if (strcmp(str1, str2) == 0) {
        printf("Both strings are same!\n");
    }
    else {
        printf("Both strings are different!\n");
    }

    return 0;
}
