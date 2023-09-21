/* make up unique pipename for client
 * send it to the server (public pipe)
 * get another unique pipename from the server
 * repeat
 * 	read a line including starred word from the client pipe
 *  display that line to the user 
 *  check whether game is over?
 *  get the user's guess letter
 *  send to the server using server pipe
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>


#define MAXLEN 1000

int main(int argc, char *argv[]) {

    int sockfd = 0, n = 0;
    char recvBuff[1024];
    struct sockaddr_in serv_addr; 

    if(argc != 3)
    {
        printf("\n Usage: %s <ip of server> <port #> \n",argv[0]);
        return 1;
    } 

    memset(recvBuff, '0',sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
	int port = atoi(argv[2]);
    serv_addr.sin_port = htons(port); 

    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 
	//loop:
	//  read user input
	//  send it to server
	//  get the quote
	//  display
	//while (fgets(line, MAXLEN, clientfp)) {
	
	while((n = read(sockfd, recvBuff, sizeof(recvBuff))) > 0) {
		if (recvBuff[0] == '(') {
			char *cptr = strchr(recvBuff, '\n');
			printf("%s", recvBuff);
			char guess[10];
			//fgets(guess, sizeof(guess), stdin); //scanf?
			scanf("%s", guess);
			sprintf(recvBuff, "%s", guess);
			write(sockfd, guess, strlen(guess)+1);
			fflush(stdout);

			// send that letter to server
			//fprintf(serverfp, "%c\n", guess[0]);
			//fflush(serverfp);
			// if line starts with "The word is"
		} else if(recvBuff[0] == 'T') {
			printf(recvBuff);
			break;	
		}
		else {
			printf(recvBuff);
			char errorCheck = '*';
			sprintf(recvBuff, "%c", errorCheck);
			write(sockfd, recvBuff, strlen(recvBuff)+1);
			fflush(stdout);
		}
		
	}
	//fclose(clientfp);
	//unlink(clientfifo);
	
	close(sockfd);	
	return 0;
}
