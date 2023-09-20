#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#define TIME_ROUND 20

int score = 0;

int counter=0;

void alarm_received(int signo) {
	printf("Alarm received. Current score: %d\n", score);

	counter++;

	//re-register signal()
	signal(SIGALRM, alarm_received);

	//has it triggered 3 times?
	if (counter < 3) 
		alarm(TIME_ROUND);
	else
		exit(0);
}

int main() {

	srand(time(NULL) + getpid() + getuid());

	signal(SIGALRM, alarm_received);
	alarm(TIME_ROUND);

	while (1) {
		//generate 2 3-digit numbers
		//ask the user for total
		int num1 = rand() % 100;
		int num2 = rand() % 100;
		printf("%d + %d = ? ", num1, num2);

		int input=0;
		scanf("%d", &input);

		if (num1 + num2 == input) {
			score++;
			puts("Great!");
		} else
			puts("Wrong.");

		printf("Score: %d\n", score);
	}
}
