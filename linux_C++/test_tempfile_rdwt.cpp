
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<unistd.h>
using namespace std;

int WriteToTempFile(char* buffer, size_t length){
	//创建临时文件
	char temp_filename[] = "/tmp/temp.file.XXXXXX";
	int fd = mkstemp(temp_filename);
	
	//取消文件链接，不显示该临时文件
	//关闭文件描述符后，临时文件会被删除
	unlink(temp_filename);
	write(fd,&length,sizeof(length));
	write(fd,buffer,length);
	//返回临时文件的文件描述符
	return fd;
}
char* ReadFromTempFile(int fd, size_t* length){
	//定位到文件开头
	lseek(fd,0,SEEK_SET);
	//读取数据
	read(fd,length,sizeof(length));
	char * buffer = new char[*length];
	read(fd,buffer,*length);
	//关闭文件描述符
	close(fd);
	return buffer;
}


int main(){
	char buff[] = "test temporary file write and read";
	int fd = WriteToTempFile(buff,strlen(buff));
	size_t len = 0;
	cout<<endl;
	char * result = ReadFromTempFile(fd,&len);
	cout<<result<<endl;
	cout<<endl;
	return 0;
}
