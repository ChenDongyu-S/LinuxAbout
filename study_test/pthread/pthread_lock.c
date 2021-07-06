#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<pthread.h>

int number = 0;

void mythread(void *arg)
{
	int i = 0;
	for(;i < 50000;++i)
	{
		int n = number;
		++n;
		number = n;
	}
	printf("[%d]",number);
}

int main()
{


	pthread_t thread1;
	int ret = pthread_create(&thread1,NULL,mythread,NULL);
	if(ret != 0)
	{
		printf("pthread_creat error : [&s]\n",strerror(ret));
		return -1;
	}
	pthread_t thread2;

	ret = pthread_create(&thread2,NULL,mythread,NULL);
	if(ret != 0)
	{
		printf("pthread_creat error : [&s]\n",strerror(ret));
		return -1;
	}
	printf("this is main thread!pid[%d]treadid[%d]\n",getpid(),pthread_self());
	sleep(1);
	return 0;
}
