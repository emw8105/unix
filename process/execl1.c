#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	//replace current process with new program
    execl("child", "child");
      
    //All statements are ignored after successful execl() 
    printf("You don't want to see me!\n");
      
    return 0;
}
