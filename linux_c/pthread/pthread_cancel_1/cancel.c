#include <stdio.h>
#include <pthread.h>
#include <unistd.h>//sleep()
 //gcc cancel.c -o cancel -pthread
 //取消线程，pthread_cancel()
void* thread( void* arg)
{
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