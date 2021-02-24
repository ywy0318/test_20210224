#include <stdio.h>
#include <pthread.h>
#include <unistd.h>//sleep()
#include <stdlib.h>//rand() 获取随机数
#include <string.h>//strerror()
 /*
  测试代码：演示没有加锁的情况，  线程内部对同一个全局变量进行操作，
  不同线程的执行情况(资源条件也有可能是不同的)是不同的，所消耗的时间也可能不一样。
 */
 
int num = 300;
int start = 1;//开始对num执行操作的标志
 
void* thread_a(void *arg)
{
	int tmp;
	while(start);//使得a线程、b线程同时开始操作num， 因为实在主线程创建的，先行创建的很有可能先执行
 
	tmp = num ;printf("a: read num\n");
	sleep(rand()%5);//do somethings
 
	tmp -= 50;printf("a: sub num 50\n");
	num = tmp;printf("a: update num \n");
	
	return (void*)0;
}
 
void* thread_b(void *arg)
{
	int tmp;
	while(start);
	
	tmp = num ;printf("b: read num\n");
	sleep(rand()%5);//do somethings
 
	tmp += 100;printf("b: add num 100\n");
	num = tmp;printf("b: update num  \n");
	
	return (void*)0;
}
 
int main(void)
{
	printf("before: num=%d\n", num);
	
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
 
	sleep(5);//确保a线程、b线程都已经创建并运行起来
	start = 0;//开始让a线程、b线程同时开始 对num进行操作
 
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
 
	return 0;
}