/*
经典linux环境变量
	UESR：你的用户户名
	HOME：你的主目录
	PATH：分号分隔的Linux查找命令的目录列表

shell处理
	shell编程时查看环境变量：echo $USER
	设置新的环境变量：EDITOR = emacs;
	export EDITOR
	export EDITOR = emacs
	
环境变量内部定义格式：VARIABLE= value
	使用getenv()函数返回环境变量的值
	使用全局变量environ处理环境变量
*/
#include<iostream>
using namespace std;

extern char ** environ;
int main(){
	char ** var;
	for(var = environ;*var != NULL;++var){
		cout<<*var<<endl;
	}
	return 0;
}
