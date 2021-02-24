#include <stdio.h>
#include <pthread.h>
#include <unistd.h>//sleep()
 /*
 测试代码8：设置为清除(出栈)但是不执行。(ctrl+c中断也不会执行)
 gcc cancel.c -o cancel -pthread 
 */
void clearup(void *arg)
{
	printf("arg=%s\n", (char*) arg);
}
 
void* thread( void* arg)
{
	int i;
	pthread_cleanup_push(clearup, "1,保存数据!");
	pthread_cleanup_push(clearup, "2,释放资源!");
 
	for(i=0; i<5; i++)
	{
		printf("i=%d\n", i);
		sleep(1);
	}
 
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
 
	return NULL;
}
 
int main(int argc, char *argv[])
{
	pthread_t tid;
 
	pthread_create(&tid, NULL, thread, NULL);
 
	pthread_join(tid, NULL);
	printf("cancel %lu\n", tid);
	return 0;
}