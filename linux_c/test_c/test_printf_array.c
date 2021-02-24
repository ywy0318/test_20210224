#include "string.h"
#include "stdlib.h"


void test_printf_array()
{
	int array[32]={0};
	int i = 0 ;
	for(i = 0 ;i < 32 ;i++)
	{
		array[i] = 0;
		//printf("array[%d]=%d\n",i,array[i]);
	}
	printf("memset\n");
	for(i = 0 ;i < 32 ;i++)
	{
		if(i%2==0)
		{
			array[i] = 0;
		}
		else
		{
			array[i] = 1;
		}
		printf("array[%d]=%d\n",i,array[i]);
	}
	printf("init\n");
	printf("chn=%x\n",array);

	memset(array,0,sizeof(array));
	printf("memset_1\n");
	for(i = 0 ;i < 32 ;i++)
	{
		array[i] = 0;
		//printf("array[%d]=%d\n",i,array[i]);
	}
	
	printf("memset_2\n");
	for(i = 0 ;i < 32 ;i++)
	{
		if(i%2==0)
		{
			array[i] = 1;
		}
		else
		{
			array[i] = 0;
		}
		printf("array[%d]=%d\n",i,array[i]);
	}
	printf("init\n");
	printf("chn=%x\n",array);

	
}





int main()
{
	test_printf_array();
	printf("finish...\n");
}


















