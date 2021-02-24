#include<stdio.h>
#include<string.h> 
#include<unistd.h>
#include<stdlib.h>
int a;
static int b = 10;
int main()
{
	char test[20]="abcdefghijklmnopqr";

	char *p;
	int c = 1;//stack
	
	printf("&a=%p,&b=%p,&c=%p,p=%p,test=%p,test+1=%p ---\n",&a,&b,&c,p,test,(test+1));
	a = 10;
	
	printf("&a=%p,&b=%p,&c=%p,p=%p ---\n",&a,&b,&c,p);
	p=(char*) malloc(sizeof(char)*20);//heap
	printf("&a=%p,&b=%p,&c=%p,p=%p,p+1=%p ---\n",&a,&b,&c,p,(p+1));//.so
	(test+1) = ((void *)0);
	//memset((test+1),0,1);
	//free((p+1));
	printf("memcpy before\n");
	memcpy(p,test,strlen(test));
	printf("memcpy after\n");

	printf("&a=%p,&b=%p,&c=%p,p=%p ---\n",&a,&b,&c,p);
	//printf("&a=%p,&b=%p,&c=%p,p=%p ---\n",&a,&b,&c,p);
	
	while(1);
	return 0;
}
