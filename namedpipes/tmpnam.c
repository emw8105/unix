#include <stdio.h>
#include <stdlib.h>

int main() {
	puts(tmpnam(NULL));
	char buffer[100] = "/tmp/veerasamXXXXXX";
	mkstemp(buffer);
	puts(buffer);
}
