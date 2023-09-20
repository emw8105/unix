#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int counter = 0;

//indicates whether the race is ON!
int flag = 0;

//when SIGUSR1 is received, this function is invoked.
void sig_start(int signo) {
	counter = 0;
	flag = 1; //start the race!
}

//when SIGUSR2 is received, this function is invoked.
void sig_stop(int signo) {
	flag = 0; //stop the race!
}

int main() {
	while (1) {
		signal(SIGUSR1, sig_start);
		signal(SIGUSR2, sig_stop);

		//waiting for the race to begin
		while (flag == 0) // same as (!flag) -- if (flag does not contain anything)
			;


		while (flag == 1) // (flag) -- if (flag has something)
			counter++;

		//race is over, print the counter & get ready for next race...
		printf("%d\n", counter);
	}
}

