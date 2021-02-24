#include<stdlib.h>
#include<stdio.h>
#include<mcheck.h>
/*
#include<mcheck.h>
//mtrace用于开启内存使用记录,muntrace用于取消内存使用记录;
//内存使用情况记录到一个文件,值由环境变量:MALLOC_TRACE决定;
void mtrace(void);
void muntrace(void);

*/

int main(int argc,char**argv)
{
	mtrace();
	char *p=malloc(100);
	free(p);
	p=malloc(1000);
	muntrace();
	return 0;
}






































