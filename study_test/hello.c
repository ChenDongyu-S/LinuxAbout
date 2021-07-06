#include<stdio.h>
#include<stdlib.h>

int main(int argc, char * argv[] ){
	int i =0;
	for(i = 0; i < argc; i++){
		printf("this is no.%d\n",i);
		printf("%s\n",argv[i]);
	}
	printf("%s\n",argv[0]);
	printf("%s\n",argv[1]);  
	printf("hello world\n");
	return 0;
}
