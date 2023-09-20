// C Program for Message Queue (Writer Process)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>

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
  
    message.mesg_type = 1;
    
	message.mesg_text[0] = NULL;
	for(int i=1; i<argc; i++) 
		strcat(message.mesg_text, argv[i]);
  	
    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
  	printf("Key %d Msgid %d\n", key, msgid);

    // msgsnd to send message
    msgsnd(msgid, &message, sizeof(message), 0);
    // display the message
    printf("Data send is : %s\n", message.mesg_text);

    return 0;
}
