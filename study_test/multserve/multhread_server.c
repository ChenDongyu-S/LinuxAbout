#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>       
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include "wrap.h"


#define PROT 7776 

typedef struct INFO
{
    int cfd;
    int dex;
    pthread_t mythread;
    struct sockaddr_in client;
}INFO;

void threadhandler(void * arg)
{
    INFO *p = (INFO*)arg;

    int cfd = p->cfd;
    pthread_t threadID = p->mythread;
    struct sockaddr_in client;
    memcpy(&client,&p->client,sizeof(client));
    
    printf("线程编号：[%d]\n",p->dex);
    
    char sIP[16];
    memset(&sIP,0x00,sizeof(sIP));

    char buf[1024];
    int n = 0;
    while(1)
    {
        memset(buf,0x00,sizeof(buf));
        n = Read(cfd,buf,sizeof(buf));
        if(n <= 0)
        {
            printf("read error or fd closed!,n=[%d]\n",n);
            Close(cfd);
            p->cfd = -1;
            pthread_exit(NULL);
        }
        printf(buf);
        int i = 0;
        for(;i<n;++i)
        {
            buf[i] = toupper(buf[i]);
        }
        Write(cfd,buf,n);
    }
    Close(cfd);
    p->cfd = -1;
}



INFO inThread[1024];

void infoInit()
{
    int i = 0;
    for(;i < 1024; ++i)
    {
        inThread[i].cfd = -1;
    }

}

int findIdex()
{
    int i = 0;
    for(;i < 1024; ++i)
    {
        if(inThread[i].cfd == -1)
        {
            return i;
        }
    }
    return -1;
}
int main()
{
    int lfd = Socket(AF_INET,SOCK_STREAM,NULL);
    //设置端口复用
    int opt = 1;
    setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(int));

    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(PROT);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    
    Bind(lfd,(struct sockaddr*)&serv,sizeof(serv));
    
    Listen(lfd,128);

    infoInit();

    pthread_t mypthread;
    int cfd;
    int idx;
    struct sockaddr_in client;
    int ret;
    socklen_t client_len = sizeof(client);
    while(1)
    {
        //接受一个链接
        cfd = Accept(lfd,(struct sockaddr*)&client,&client_len);
        //寻找数组中的空闲位置,把接受到的链接存进去
        idx = findIdex();
        if(idx == -1)
        {
            printf("队列已满，正在重试！\n");
            close(cfd);
            continue;
        }
        inThread[idx].cfd = cfd;
        inThread[idx].dex = idx;
        memcpy(&inThread[idx].client,&client,client_len);
        
        //创建子线程收发
        ret = pthread_create(&inThread[idx].mythread,NULL,&threadhandler,&inThread[idx]);
        if(ret != 0)
        {
            printf("create error[%s]\n",strerror(ret));
            exit(-1);
        }

        //设置线程分离属性
        pthread_detach(inThread[idx].mythread);


    }
    close(lfd);
    return 0;
}