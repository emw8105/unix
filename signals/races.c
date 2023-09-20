#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int counter = 0;

int flag = 0;

void sig_start(int signo) {
	counter = 0;
	flag = 1;
	signal(SIGUSR1, sig_start);
}

void sig_stop(int signo) {
	flag = 0;
	signal(SIGUSR2, sig_stop);
}

int main(int argc, char *argv[]) {
	int i;
	//create specified # of tasks
	for(i=1; i<atoi(argv[1]); i++)
		if (fork() == 0)
			break;

	signal(SIGUSR1, sig_start);
	signal(SIGUSR2, sig_stop);

	while (1) {
		while (!flag)
			; // sleep(1);
		while (flag)
			counter++;
		printf("%d: %d\n", i, counter);
	}
}

