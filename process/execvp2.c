#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


//Ask the user to input the command to run
//invoke execvp with that
int main()
{
	char buffer[20];
	printf("Enter the command: ");
	scanf("%s", buffer);
	//A null terminated array of character pointers 
	char *args[]={buffer,NULL}; 
	execvp(args[0],args);
      
    //All statements are ignored after execvp() 
    printf("I hope you won't see me!");
      
    return 0;
}
