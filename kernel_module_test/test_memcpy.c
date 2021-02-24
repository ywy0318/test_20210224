#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include <unistd.h>
//#define SIZEOFM 1024*1024*2
#define SIZEOFM 128
int main()
{
	char buf1[SIZEOFM] = {0};
	char buf[SIZEOFM] = {0};
	char *test = NULL;
	char *test1 = NULL;
	test = malloc(SIZEOFM);
	test1 = malloc(SIZEOFM);
	if((NULL == test)||(NULL == test1))
	{
		return -1;
	}
	while(1)
	{
		memcpy(buf,"12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678",SIZEOFM);
		usleep(1000);
		memcpy(buf1,buf,SIZEOFM);
		usleep(1000);
		memcpy(test1,buf,SIZEOFM);
	}
	return 0;
}