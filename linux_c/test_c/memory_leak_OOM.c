#include<stdlib.h>
#include<stdio.h>
#include<mcheck.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/syscall.h>
/*
#include<mcheck.h>
//mtrace用于开启内存使用记录,muntrace用于取消内存使用记录;
//内存使用情况记录到一个文件,值由环境变量:MALLOC_TRACE决定;
void mtrace(void);
void muntrace(void);
mtrace函数是通过修改malloc_hook等内存操作接口的回调来实现记录内存使用的,
如果取得内存分配函数的调用地址,gcc有一个内置的函数,用于返回本函数将要返回的地址;
内置返回地址函数:
void* __builtin_return_address(unsigned int level);
返回的是处于level级堆栈的地址;level为0表示本函数返回的地址,为1表示本函数的上一个函数
返回的地址;
内置函数返回的是本函数返回的地址,是函数调用的下一条语句,所以使用ret-1来记录函数被
调用地址;
*/
//addr2line -f -e memory_leak_OOM -a 0x4006ea 将地址转换为代码位置：
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






































