// C Program for Message Queue (Reader Process)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

// structure for message queue
struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;
  
int main()
{
	key_t key;
	int msgid;

    // ftok to generate unique key - main server
    key = ftok(getenv("HOME"), 1);
  
  	int counter=0;

    	// msgget creates a message queue and returns identifier
    	msgid = msgget(key, 0666 | IPC_CREAT);
  		printf("Key %d Msgid %d\n", key, msgid);

	while (1) {

    	// msgrcv to receive message
    	msgrcv(msgid, &message, sizeof(message), 1, 0);
    	// to destroy the message queue
    	//msgctl(msgid, IPC_RMID, NULL);
		counter++;

  		if (fork())  //parent goes to while loop
			continue;

    	// display the message
    	printf("Data Received is : %s \n", message.mesg_text);
		int clientPid = atoi(message.mesg_text);

		//use clientPid to come up with key & msgid to respond
		int key2 = ftok(getenv("HOME"), clientPid);
    	int msgid2 = msgget(key2, 0666 | IPC_CREAT);
		sprintf(message.mesg_text, "%d %d", counter, getpid());
    	msgsnd(msgid2, &message, sizeof(message), 0);
    	printf("Data Sent is : %s\n", message.mesg_text);

		exit(0); //child server exits, after the work.
  	} 
  
    return 0;
}
