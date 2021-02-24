#include "thread_pool.h"
 
void *mytask(void *arg)//任务
{
	type_t n = (type_t)arg;
 
	printf("[%u][%s] ==> job will be done in %lu sec...\n",
		(unsigned)pthread_self(), __FUNCTION__, n);//__FUNCTION__:宏-〉函数名
 
	sleep(n);//do somethings
 
	printf("[%u][%s] ==> job done!\n",
		(unsigned)pthread_self(), __FUNCTION__);
 
	return NULL;
}
 
void *count_time(void *arg)//计时函数
{
	int i = 0;
	while(1)
	{
		sleep(1);
		printf("sec: %d\n", ++i);
	}
}
 
int main(void)
{
	pthread_t a;
	pthread_create(&a, NULL, count_time, NULL);//创建子线程用来计时
 
	// 1, 初始化线程池
	thread_pool *pool = malloc(sizeof(thread_pool));
	init_pool(pool, 2);//创建2条线程
 
	// 2, 添加3个任务
	printf("throwing 3 tasks...\n");
	add_task(pool, mytask, (void *)((type_t)rand()%10));
	add_task(pool, mytask, (void *)((type_t)rand()%10));
	add_task(pool, mytask, (void *)((type_t)rand()%10));
 
	// 3, 查看当前的线程数目
	printf("current thread number: %d\n",remove_thread(pool, 0));
	
	sleep(9);//延时等待
 
	// 4, 添加2个任务
	printf("throwing another 2 tasks...\n");
	add_task(pool, mytask, (void *)((type_t)rand()%10));
	add_task(pool, mytask, (void *)((type_t)rand()%10));
 
	// 5, 添加线程
	add_thread(pool, 2);
	printf("add 2 thread \n");
	sleep(5);
 
	// 6, 移除线程
	printf("remove 3 threads from the pool, "
	       "current thread number: %d\n",
			remove_thread(pool, 3));
 
	// 7, 销毁线程池
	destroy_pool(pool);
	
	//释放内存空间
	free(pool);
	
	return 0;
}