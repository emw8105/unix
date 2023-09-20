// C Program for Message Queue (Writer Process)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


#define MAX 100
  
// structure for message queue
struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;
  
int main(int argc, char *argv[])
{
    key_t key;
    int msgid;
  
    // ftok to generate unique key
    key = ftok(getenv("HOME"), 1);
  
  	//we will use client PID to create unique key
	int pid = getpid();
    message.mesg_type = 1;
	sprintf(message.mesg_text, "%d", pid);
  	
    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
  	printf("Send Key %d Msgid %d\n", key, msgid);

    // msgsnd to send message
    msgsnd(msgid, &message, sizeof(message), 0);
    // display the message
    printf("Data send is : %s\n", message.mesg_text);

	//unique key based on client pid
	int key2 = ftok(getenv("HOME"), pid);
    int msgid2 = msgget(key2, 0666 | IPC_CREAT);
  	printf("Recv Key %d Msgid %d\n", key2, msgid2);

    msgrcv(msgid2, &message, sizeof(message), 1, 0);
    printf("Data Received is : %s \n", message.mesg_text);

	//delete the message queue since we are done!
	//no need to leave the queues OPEN in the system.
    msgctl(msgid2, IPC_RMID, NULL);

    return 0;
}
