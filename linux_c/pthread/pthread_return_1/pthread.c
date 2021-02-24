#include <stdio.h>
#include <pthread.h>
#include <string.h>//strerror()
 //gcc pthread.c -o pthread -lpthread
//线程返回字符串,主线程等待线程返回字符串
void* thread(void *arg)
{
	printf("arg=%s\n", (char*)arg);
	return "world";
}
 
 
int main(void)
{
	pthread_t tid;
	int retval;
	void *retp;
 
	retval = pthread_create( &tid, NULL, thread, "hello");//创建线程
	if(retval)
	{
		fprintf(stderr, "create thread error = %s\n", strerror(retval));
		return -1;
	}
 
 
	retval = pthread_join(tid, &retp);//wait
	if(retval)
	{
		fprintf(stderr, "join thread error = %s\n", strerror(retval));
		return -1;
	}
 
	printf("join success, retp=%s\n", (char *)retp);
 
	return 0;
}