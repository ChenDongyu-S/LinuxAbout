#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <ctype.h>
#include <pthread.h>
#include "wrap.h"

//防止多个线程公用cfd的情况
struct INFO
{
	int cfd = -1;
	pthread_t threadID;
	struct sockaddr_in client;
	//复用，使用cfd作为标识
	
};

void *thread_work(void *arg)
{
	int cfd = *(int *)arg;
	while(1)
	{
		//read数据
		int n;
		char buf[1024];
		while(1)
		{
			memset(buf,0x00,sizeof(buf));
			n = Read(cfd,buf,sizeof(buf));
			if(n < 0)
			{
				printf("read error or client closed! n[%d]",n);
				break;
			}
			printf("n==[%d],buf==[%s]",n,buf);
			int i = 0;
	
			for(;i < n;++i)
			{
				buf[i] = toupper(buf[i]);
			}
			Write(cfd,buf,n);
		}
	}
	close(cfd);
	arg = -1;
	pthread_exit(NULL);
}

int main()
{
	//创建socket
	int lfd = Socket(AF_INET,SOCK_STREAM,0);
	//绑定
	//先创建sockaddr结构体
	struct sockaddr_in serv;
	bzero(&serv,sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_port = htons(7776);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	Bind(lfd,(struct sockaddr*)&serv,sizeof(serv));
	
	//设置监听
	Listen(lfd,128);
	
	struct INFO info[100];
	while(1)
	{	
		int i = 0;
		for(;i < 100; ++i)
		{
			if(info[i].cfd == -1) break;
		}
		
		//接受新的链接
		info[i].cfd = Accept(lfd,NULL,NULL);
		//创建子线程
		pthread_create(&(info[i].threadID),NULL,thread_work,&(info[i].cfd));

		//设置子线程未分离属性
		pthread_detach(&info[i].threadID);
	}
	//闭监听文件描述符
	close(lfd);
	return 0;
}
