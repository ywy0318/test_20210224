#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<math.h>
void test_pow()
{
	int i = 0;
	int j = 0;
	unsigned int num = 0;
	int temp = 0;
	for(i = 1;i < 16;i++)
	{
		num = 0;
		for(j = 0;j < i;j++)
		{
			temp = pow(2,j);
			num +=temp;
		}
		printf("%d--%d\n",i,num);	
	}
}

int main()
{
	//test_pow();
	//test_bcpm();
	while(1)
	{
		printf("main finished....\n");	
	}
	
}
