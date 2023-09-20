#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>

int main() {
	pid_t childpid;
	if (childpid = fork()) {
		//parent to terminate the child before quitting
		kill(childpid, SIGKILL);
	} else {
		while (1)  //child: infinite loop
			;
	}
}
