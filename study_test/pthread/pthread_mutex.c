#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<pthread.h>

int number = 0;
pthread_mutex_t mutex;

void mythread(void *arg)
{
	int i = 0;
	for(;i < 50000;++i)
	{
		//枷锁
		pthread_mutex_lock(&mutex);
		int n = number;
		++n;
		number = n;
		pthread_mutex_unlock(&mutex);
	}
	printf("[%d]",number);
}

int main()
{

	//锁的初始化
	pthread_mutex_init(&mutex,NULL);


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
	
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	
	//释放锁
	pthread_mutex_destory(mutex);
	
	printf("this is main thread!pid[%d]treadid[%d]\n",getpid(),pthread_self());
	

	sleep(1);
	return 0;
}
