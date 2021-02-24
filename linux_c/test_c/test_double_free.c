	#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void test_signal()
{
	int *p =NULL;
	int i = 10;
	p =(int*)malloc(sizeof(100)*1024);
	if(p!=NULL)
	{
		printf("malloc success\n");
		memset(p,0,1024);
		printf("memset success\n");	
	}
	else
	{
		printf("malloc failed\n");	
	}
	printf("before first free\n");	
	free(p);
	printf("after first free\n");	
	printf("before second free\n");	
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
	free(p);
	printf("after second free\n");	

}
int main()
{
	test_signal();
	printf("finished...main...\n");
}

