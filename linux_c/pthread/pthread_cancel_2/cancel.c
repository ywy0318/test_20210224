#include <stdio.h>
#include <pthread.h>
#include <unistd.h>//sleep()
 //设置线程不可以取消
 //gcc cancel.c -o cancel -pthread
void* thread( void* arg)
{
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);//设置线程不可以取消
	int i;
	
	for(i=0; i<10; i++)
	{
		printf("i=%d\n", i);
		sleep(1);
	}
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