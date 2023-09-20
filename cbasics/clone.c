#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXLEN 1000
char name[MAXLEN];
void shortName(char *nameptr) {
	putchar(toupper(*nameptr++));
	while (*nameptr) {	// position to skip
		nameptr++;	// skip
		if (*nameptr) {	// check before printing
			putchar(tolower(*nameptr++));
		}
	}
	putchar('\n');
}

int main() {
	scanf("%s", name);	// fgets(name, MAXLEN, stdin); puts '\n'

	shortName(name);
	shortName(name+1);
}
