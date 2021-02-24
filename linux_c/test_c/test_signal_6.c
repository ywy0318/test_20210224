	#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void test_signal()
{
	int *p =NULL;
	int i = 0;
	p =(int*)malloc(sizeof(100)*1024);
	if(p!=NULL)
	{
		printf("malloc success\n");
		memset(p,0,1024*10);
		printf("memset success\n");	
	}
	else
	{
		printf("malloc failed\n");	
	}
	printf("before free\n");	
	free(p);
	while(1)
	{
		if(i<10)
		{
			printf("test_signal...i=%d\n",i);
			i++;
		}
		else
		{
			break;
		}	
	}
}
int main()
{
	test_signal();
	printf("finished...main...\n");
}
