#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>       
#include <unistd.h>

int main(int argv,char * argc[]){
	//int fd = open(argc[1],O_RDWR); 
	struct stat buf;
	int check = stat(argc[1],&buf);
	if(check < 0)
	{
		printf("file get failure!\n");
		return -1;
	}	
	printf("the size of file is %d",buf.st_size);
	if(S_ISREG(buf.st_mode))
	{
		printf("改文件伪普通文件\n");
	}
	else
	{
		printf("改文件不是普通文件\n");
	}

	return 0;
}
