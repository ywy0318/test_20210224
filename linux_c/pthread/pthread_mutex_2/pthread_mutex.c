#include <stdio.h>
#include <pthread.h>
#include <unistd.h>//sleep()
#include <stdlib.h>//rand()
#include <string.h>//strerror()
 //加锁，确保操作的执行顺序(或者说操作的原子性)，即同一时间只有一方能够操作，操作完才轮到下一个
 //gcc pthread_mutex.c -o pthread_mutex -pthread
pthread_mutex_t g_mutex;//锁变量
int num = 300;
int start = 1;
 
void* thread_a(void *arg)
{
	int tmp;
	while(start);
	
	pthread_mutex_lock(&g_mutex);操作前加锁
	tmp = num ;printf("a: read num\n");
	sleep(rand()%5);//do somethings
 
	tmp -= 50;printf("a: sub num 50\n");
	num = tmp;printf("a: update num \n");
	pthread_mutex_unlock(&g_mutex);//操作后解锁
	
	return (void*)0;
}
 
void* thread_b(void *arg)
{
	int tmp;
	while(start);
	
	pthread_mutex_lock(&g_mutex);操作前加锁
	tmp = num ;printf("b: read num\n");
	sleep(rand()%5);//do somethings
 
	tmp += 100;printf("b: add num 100\n");
	num = tmp;printf("b: update num  \n");
	pthread_mutex_unlock(&g_mutex);//操作后解锁
	
	return (void*)0;
}
 
int main(void)
{
	printf("before: num=%d\n", num);
	
	pthread_mutex_init(&g_mutex, NULL);//初始化锁
	pthread_t tid_a, tid_b;
	int retval;
 
	retval = pthread_create( &tid_a, NULL, thread_a, NULL);//创建线程a
	if(retval)
	{
		fprintf(stderr, "create thread error = %s\n", strerror(retval));
		return -1;
	}
 
	retval = pthread_create( &tid_b, NULL, thread_b, NULL);//创建线程b
	if(retval)
	{
		fprintf(stderr, "create thread error = %s\n", strerror(retval));
		return -1;
	}
 
	sleep(5);
	start = 0;
 
	retval = pthread_join(tid_a,NULL );//等待线程a
	if(retval)
	{
		fprintf(stderr, "join thread error = %s\n", strerror(retval));
		return -1;
	}
 
	retval = pthread_join(tid_b,NULL);//等待线程b
	if(retval)
	{
		fprintf(stderr, "join thread error = %s\n", strerror(retval));
		return -1;
	}
 
	printf("after: num=%d\n", num);
	pthread_mutex_destroy(&g_mutex);//销毁互斥锁
	
	return 0;
}