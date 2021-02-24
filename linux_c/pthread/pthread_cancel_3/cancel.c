#include <stdio.h>
#include <pthread.h>
#include <unistd.h>//sleep()
 //测试代码3：pthread_cleanup_push()与pthread_cleanup_pop()
 //gcc cancel.c -o cancel -pthread
void clearup(void *arg)
{
	printf("arg=%s\n", (char*) arg);
}
 
void* thread( void* arg)
{
	int i;
	pthread_cleanup_push(clearup, "1,保存数据!");
	pthread_cleanup_push(clearup, "2,释放资源!");
 
	for(i=0; i<10; i++)
	{
		printf("i=%d\n", i);
		sleep(1);
	}
 
	pthread_cleanup_pop(1);
	pthread_cleanup_pop(1);
 
	return NULL;
}
 
int main(int argc, char *argv[])
{
	pthread_t tid;
 
	pthread_create(&tid, NULL, thread, NULL);
 
	getchar();
	pthread_cancel(tid);
	
	pthread_join(tid, NULL);
	printf("cancel %lu\n", tid);
	return 0;
}