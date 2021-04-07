//编写随机数，通过随机数设备读取随机数
#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>

using namespace std;

int main(){
	FILE * f = fopen("/dev/urandom","rb");
	int pwd_int = 0;
	char pwd_char[10];
	cout<<endl;
	fread(&pwd_int,sizeof(int),1,f);
	fread(pwd_char,sizeof(char),9,f);
	cout<<pwd_int<<endl;
	cout<<pwd_char<<endl;
	cout<<endl;
	return 0;
	
}
