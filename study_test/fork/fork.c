#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>       
#include <unistd.h>

int main(int argv,char * argc[])
{
	printf("this is a simple program\n");
	pid_t pid = fork();
	if(pid < 0)
	{
		printf("创建失败！");
		return -1;
	}
	//father进程	
	else if(pid > 0)
	{
		printf("father:pid == [%d]\n",getpid());	
	}	
	else if(pid == 0)
	{
		printf("child:pid == [%d]\n",getpid());	
	}
	printf("this is the end of the program\n");

	return 0;
}
