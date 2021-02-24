#include <stdio.h>
#include <unistd.h>//sleep()
#include <pthread.h>
 //gcc rwlock.c -o rwlock -pthread
pthread_rwlock_t g_rwlock;//读写锁
int start = 1;
 
void *read_thread(void *arg)//读线程
{
	int count = 3;
	while(start);
 
	pthread_rwlock_rdlock(&g_rwlock);//加上读锁
 
	while(count--)
	{
		printf("read: thread id=%lu\n", pthread_self());//pthread_self()获取自身的线程ID
		sleep(1);
	}
	
	pthread_rwlock_unlock(&g_rwlock);//解开读锁
	return NULL;
}
 
void *write_thread(void *arg)//写线程
{
	int count = 3;
	while(start);
	
	pthread_rwlock_wrlock(&g_rwlock);//加上写锁
 
	while(count--)
	{
		printf("write: thread id=%lu\n", pthread_self());
		sleep(1);
	}
 
	pthread_rwlock_unlock(&g_rwlock);//解开写锁
 
	return NULL;
}
 
int main(void)
{
	pthread_t tid_r, tid_w;
 
	pthread_rwlock_init(&g_rwlock, NULL);//初始化读写锁
 
	//创建读,写线程
	pthread_create(&tid_w, NULL, write_thread, NULL);
	pthread_create(&tid_r, NULL, read_thread, NULL);
 
	//确保所有线程都已经创建完毕并开始执行
	sleep(5);
	start = 0;
 
	//等待读、写线程退出
	pthread_join(tid_w, NULL);
	pthread_join(tid_r, NULL);
	
	pthread_rwlock_destroy(&g_rwlock);//销毁读写锁
 
	return 0;
}