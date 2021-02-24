#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void fun(int x)
{
	static int a = 0;
	static int b = 0;
	a = x;
	a++;
	printf("a= %d \n",a);
}
void main()
{
	int i =0;
	for(i = 10;i > 0; i--)
	{
		fun(i);
	}
	while(1);

}
