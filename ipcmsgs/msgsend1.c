// C Program for Message Queue (Writer Process)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#define MAX 100
  
// structure for message queue: type and variable defined together!
struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;
  
int main()
{
    key_t key;
    int msgid;
  
    // ftok to generate unique key from home directory path name and project id number
    key = ftok(getenv("HOME"), 1);
  
    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
  	printf("Key %d Msgid %d\n", key, msgid);

    message.mesg_type = 1;
    printf("Write Data : ");
    fgets(message.mesg_text,MAX,stdin);
  
    // msgsnd to send message
    // display the message
    printf("Data send is : %s (%d) \n", message.mesg_text, 
    		msgsnd(msgid, &message, sizeof(message), 0));
  
    return 0;
}
