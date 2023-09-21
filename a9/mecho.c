#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

//Usage: mecho -s 10 -n 10 17
//       mecho -s <starting value> -n <count> multiplier
int main(char argc, char *argv[]) {
	char ch;
	long startingValue=0, repeatCount=1000, multiplier=1, inputValue=0;

	while ((ch = getopt(argc, argv, ":s:n:")) != -1) {
		switch(ch) {
			case 's': startingValue = atoi(optarg);
						break;
			case 'n': repeatCount = atoi(optarg);
						break;
			case '?':
				fprintf(stderr, "Unrecognized option: -%c\n", optopt);
				exit(1);

			default:
				fprintf(stderr, "mecho -s <starting value> -n <count> multiplier\n");
				exit(2);
		}
	}
	if (optind < argc) 
		multiplier = atol(argv[optind]);
	else {
		fprintf(stderr, "mecho -s <starting value> -n <count> multiplier\n");
		exit(3);
	}

	if (startingValue) {
		printf("%ld\n", startingValue);
		fprintf(stderr, "%ld\n", startingValue);
		fflush(stdout);
	}

	for(int i=0; i<repeatCount; i++) 
		if (scanf("%ld", &inputValue) == 1) {
			printf("%ld\n", inputValue * multiplier);
			fprintf(stderr, "%ld\n", inputValue * multiplier);
			fflush(stdout);
		}
}
