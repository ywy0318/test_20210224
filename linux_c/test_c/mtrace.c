#include<stdlib.h>
#include<stdio.h>
#include<mcheck.h>
/*
#include<mcheck.h>
//mtrace���ڿ����ڴ�ʹ�ü�¼,muntrace����ȡ���ڴ�ʹ�ü�¼;
//�ڴ�ʹ�������¼��һ���ļ�,ֵ�ɻ�������:MALLOC_TRACE����;
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






































