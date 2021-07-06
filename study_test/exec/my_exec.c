#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>       
#include <unistd.h>

int main(int argv,char * argc[])
{
	int i = 0;
	for(i = 0; i < argv; ++i)
	{
		printf("[%d][%s]",i,argc[i]);
	}
	return 0;
}
