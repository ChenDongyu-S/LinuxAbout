#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <ctype.h>
#include <signal.h>
#include <sys/wait.h>
#include "wrap.h"

void waithandle()
{
	pid_t wpid;
	while(1)
	{
		wpid = waitpid(-1,NULL,WNOHANG);
		if(wpid > 0)
		{
			printf("child exit pid=[%d]\n",wpid);
		}
		else if(wpid == 0 || wpid == -1)
		{
			break;
		}
	}
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
	serv.sin_port = htons(7777);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	Bind(lfd,(struct sockaddr*)&serv,sizeof(serv));
	
	//设置监听
	Listen(lfd,128);

	//阻塞child信号，防止信号还没注册完成，子线程就结束了
	sigset_t mask;
	sigemptyset(&mask);
	sigaddset(&mask,SIGCHLD);
	sigprocmask(SIG_BLOCK,&mask,NULL);

	pid_t pid;
	int cfd;
	while(1)
	{
		//接收新的链接
		cfd = Accept(lfd,NULL,NULL);
		
		pid = fork();
		if(pid < 0)
		{
			perror("fork error!");
			exit(-1);
		}
		if(pid > 0)
		{
			//关闭通信文件描述符 
			close(cfd);
			//创建信号回收子进程
			struct sigaction act;
			act.sa_handler = waithandle;
			act.sa_flags = 0;
			sigemptyset(&act.sa_mask);
			sigaction(SIGCHLD,&act,NULL);

			sigprocmask(SIG_UNBLOCK,&mask,NULL);
		}
		if(pid == 0)
		{
			//在主进程中依旧保持监听，需要结束掉刚连接上的连接，这是因为该链接需要在子进程中执行
			//在子进程中需要关闭监听
			close(lfd);
			int n;
			char buf[1024];
			while(1)
			{
				n = Read(cfd,buf,sizeof(buf));
				if(n < 0)
				{
					printf("read error or client closed!,n == [%d]\n",n);
					break;
				}
				printf("[prot]---->:n==[%d],buf=[%s]\n",n,buf);
				int i = 0;
				for(;i < n;++i)
				{
					buf[i] = toupper(buf[i]);
				}
				Write(cfd,buf,n);
			}
			close(cfd);
			exit(0);
		}
	}
	close(lfd);
	return 0;
}
