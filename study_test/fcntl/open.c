#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>       
#include <unistd.h>

int main(int argv,char * argc[]){
	int fd = open(argc[1],O_RDWR | O_CREAT,0777);
	if(fd < 0)
	{
		printf("文件打开失败！");
		return -1;
	}
	write(fd,"hello world!",strlen("hello world"));
	lseek(fd,0,SEEK_SET);
	
	char buf[64];
	memset(buf,0x00,sizeof(buf));
	read(fd,buf,sizeof(buf));
	printf("文件中的内容是：%s",buf);
	close(fd);
	return 0;
}
