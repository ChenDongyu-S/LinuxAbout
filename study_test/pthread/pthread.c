#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<pthread.h>

void mythread(void *arg)
{
	int * n = (int *)arg;
	printf("this is [%d] thread!\n",*n);
}

int main()
{
	pthread_t thread[5];
	int i = 0;
	int arr[5];
	
	int n = 5;
	for(;i < 5;++i)
	{
		arr[i] = i;	
		int ret = pthread_create(&thread[i],NULL,mythread,&arr[i]);
		if(ret != 0)
		{
			printf("pthread_creat error : [&s]\n",strerror(ret));
			return -1;
		}
	}
	printf("this is main thread!pid[%d]treadid[%d]\n",getpid(),pthread_self());
	sleep(1);
	return 0;
}
