//临时文件的读写操作
//使用临时文件注意事项
/*
mkstemp()
	linux中临时文件通过mkstemp()创建，该函数只有一个参数：char* template
	需要注意的是：这个字符串要以XXXXXX结尾。mkstemp()函数会用随机产生的字符串替换XXXXXX，保证了文件名的一致性
	值得一提的是，之所以使用随机数来生成临时文件是为了防止其他用户或程序调用该临时文件，此做法在程序中返回的是一个文件描述符，除开这个文件描述符以外，不能对临时文件进行操作。

unlink()
	临时文件使用完成之后应该立即删除，否则临时文件目录会塞满垃圾。
	由于mkstemp函数创建的零食文件不能自动删除，所以执行完mkstemp函数后要调用unlink函数，unlink函数删除文件的目录入口，但临时文件还可以通过文件描述符进行访问，直到最后一个打开的进程关闭文件操作符，或者程序退出后临时文件被自动彻底的删除。
*/
//
//
//

#include<iostream>
#include<cstdlib>
#include<cstring>
#include<unistd.h>

int WirteToTempFile(char* buffer, size_t length){
	//创建临时文件
	char file_name[] = "/tmp/temp.file.XXXXXX";
	int fd = mkstemp(temp_filename);
	
	//取消文件链接，不显示该临时文件
	//关闭文件描述符后，临时文件会被删除
	unlink(temp_filename);
	write(fd,&length,sizeof(length));
	write(fd,buffer,length);
	//返回临时文件的文件描述符
	return fd;
}
char* ReadFromTempFile(int fd, size_t length){
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


















