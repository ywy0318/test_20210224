#include<stdlib.h>
#include<stdio.h>
#include<mcheck.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/syscall.h>
/*
#include<mcheck.h>
//mtrace���ڿ����ڴ�ʹ�ü�¼,muntrace����ȡ���ڴ�ʹ�ü�¼;
//�ڴ�ʹ�������¼��һ���ļ�,ֵ�ɻ�������:MALLOC_TRACE����;
void mtrace(void);
void muntrace(void);
mtrace������ͨ���޸�malloc_hook���ڴ�����ӿڵĻص���ʵ�ּ�¼�ڴ�ʹ�õ�,
���ȡ���ڴ���亯���ĵ��õ�ַ,gcc��һ�����õĺ���,���ڷ��ر�������Ҫ���صĵ�ַ;
���÷��ص�ַ����:
void* __builtin_return_address(unsigned int level);
���ص��Ǵ���level����ջ�ĵ�ַ;levelΪ0��ʾ���������صĵ�ַ,Ϊ1��ʾ����������һ������
���صĵ�ַ;
���ú������ص��Ǳ��������صĵ�ַ,�Ǻ������õ���һ�����,����ʹ��ret-1����¼������
���õ�ַ;
*/
//addr2line -f -e memory_leak_OOM -a 0x4006ea ����ַת��Ϊ����λ�ã�
void test__builtin_return_address()
{
	void *ret = __builtin_return_address(0);
	printf("%p\n",ret-1);
	void *caller = __builtin_return_address(0);
	printf("%p\n",caller-1);
}
void test_mtrace()
{
	mtrace();
	char *p=malloc(100);
	free(p);
	p=malloc(1000);
	muntrace();
}

void test_memory_leak()
{
	char *p[1024];
	int i=0;	
	while(i<1024)
	{
		p[i]=(char*)malloc(1024*1024*2);
		i++;
		sleep(2);
		printf("%d\n",i);
	}
}
int main(int argc,char**argv)
{	
    printf("threadFunc is %d\n",  syscall(SYS_gettid));
	//test__builtin_return_address();
	//test_mtrace();
	test_memory_leak();
	return 0;
}






































