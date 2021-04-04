/*
编写客户端程序，在用户未指定服务器名时使用缺省服务器名称
*/
#include<iostream>
#include<cstdlib>
using namespace std;
int main(){
	char * server_name = getenv("SERVER_NAME");
	if(!server_name)
	//SERVER_NAME环境变量未设置，使用缺省值
		server_name = "server.yours.com";
	cout<<"accessing server"<<server_name<<endl;
	return 0;
}
