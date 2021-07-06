#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>       
#include <unistd.h>

int main(int argv,char * argc[]){
	int fd = open(argc[1],O_RDWR); 
	int len = lseek(fd,0,SEEK_END);
	lseek(fd,0,SEEK_CUR);
	lseek(fd,1000,SEEK_CUR);
	write(fd,"a",1);
	close(fd);
	printf("the len of file is %d",len);
	return 0;
}
