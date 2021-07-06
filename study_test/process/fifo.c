#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include<sys/mman.h>
#include<error.h>
#include <sys/stat.h>
#include <fcntl.h>       
#include <unistd.h>

int main(int argv,char * argc[])
{
	printf("this is a simple program\n");
	int fd = open("./temp",O_RDWR);
	if(fd < 0)
	{
		printf("文件打开失败！");
		return -1;
	}
	int len = lseek(fd,0,SEEK_END);
	void * addr = mmap(NULL,len,PROT_READ | PROT_WRITE,MAP_PRIVATE,fd,0);
	if(addr == MAP_FAILED)
	{
		perror("map error");
		return -1;
	}
	close(fd);
	pid_t pid = fork();
	if(pid < 0)
	{
		printf("创建失败！");
		return -1;
	}
	//father进程	
	else if(pid > 0)
	{
		memcpy(addr,"holle world",strlen("holle world"));
		wait(NULL);	
	}	
	else if(pid == 0)
	{
		sleep(1);
		char * p =(char*) addr;
		printf("%s",p);	
	}
	printf("this is the end of the program\n");

	return 0;
}
