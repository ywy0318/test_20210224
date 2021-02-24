#include <stdio.h>
#include <pthread.h>
#include <unistd.h>//sleep()
 /*
 测试代码：资源条件count开始还没有满足，子线程进入睡眠，等待资源满足。主线程改变资源使得条件满足。
 gcc cond.c -o cond -pthread
 */
pthread_mutex_t g_mutex;//互斥锁变量
pthread_cond_t g_cond;//条件变量
int count = 0;//资源条件
 
void *child_thread(void *arg)
{
 
	pthread_mutex_lock(&g_mutex);//加互斥锁
 
	printf("thread id = %lu ==〉start\n", pthread_self());
	
	while(1)
	{
		printf("in while 1\n");
 
		if(count >= 100)//资源条件满足
		{
			sleep(1);
			count -= 100;
			break;
		}
		else //资源条件不满足
		{
			//等待条件满足，（解开互斥锁，使得线程睡眠，等收到条件满足的信号，再加上互斥锁）
			pthread_cond_wait(&g_cond, &g_mutex);
		}
 
		printf("in while 2\n");
		
	}
 
	pthread_mutex_unlock(&g_mutex);//解开互斥锁
 
	printf("thread id = %lu ==>exit\n", pthread_self());
 
	return NULL;
}
 
 
int main(void)
{
	pthread_t tid;
 
	pthread_mutex_init(&g_mutex, NULL);//初始化互斥锁
	pthread_cond_init(&g_cond, NULL);//初始化条件变量
 
	pthread_create(&tid, NULL, child_thread, NULL);//创建子线程
 
	sleep(1);//确保子线程创建并运行
 
	//加上互斥锁,此处因为子线程已经加锁而被阻塞，
	//等到子线程因为资源条件不足而进入睡眠并解开互斥锁，才能加锁
	pthread_mutex_lock(&g_mutex);
 
	printf("main start input\n");
	scanf("%d", &count);//用来改变资源条件
 
	pthread_mutex_unlock(&g_mutex);//解开互斥锁
	
	if(count>=100)//如果资源条件满足
	{
		pthread_cond_signal(&g_cond);//发送信号，关心此条件变量的线程就会被唤醒
	}
	
	pthread_join(tid, NULL);//等待子进程退出
	
	pthread_mutex_destroy(&g_mutex);//销毁互斥锁
	pthread_cond_destroy(&g_cond);//销毁条件变量
	
	printf("cunt=%d\n", count);
	return 0;
}