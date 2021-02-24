
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <errno.h>
#include <pthread.h>

#define MAX_WAITING_TASKS	1000
#define MAX_ACTIVE_THREADS	20


//任务
struct task
{
	void *(*task)(void *arg);
	void *arg;

	struct task *next;
};

//线程池
typedef struct thread_pool
{
	pthread_mutex_t lock;//互斥锁
	pthread_cond_t  cond;//条件变量
	struct task *task_list;//任务队列

	pthread_t *tids;//线程id

	unsigned waiting_tasks;//等待任务
	unsigned active_threads;//

	bool shutdown;//停始状态
}thread_pool;



struct file
{
	char srcfile[1024];
	char dstfile[1024];
};



#if 0
//初始化线程池
bool init_pool(thread_pool *pool,
          unsigned int threads_number);

//新增任务
bool add_task(thread_pool *pool,
         void *(*task)(void *arg),
         void *arg);

//新增线程
int add_thread(thread_pool *pool,
           unsigned int additional_threads_number);

//移除线程
int remove_thread(thread_pool *pool,
              unsigned int removing_threads_number);

//销毁线程池
bool destroy_pool(thread_pool *pool);

//处理程序
void *routine(void *arg);

//copy函数
void *(*copy)(void * arg);
#endif

//互斥锁解锁
void handler(void *arg)
{

	pthread_mutex_unlock((pthread_mutex_t *)arg);
}

//
void *routine(void *arg)
{
	thread_pool *pool = (thread_pool *)arg;
	struct task *p;//声明一个任务头节点
	printf("runtone... ...\n");

	while(1)
	{

		pthread_cleanup_push(handler, (void *)&pool->lock);//线程清理函数1
		pthread_mutex_lock(&pool->lock);//上锁


		while(pool->waiting_tasks == 0 && !pool->shutdown)//a.非停止状态
		{
			pthread_cond_wait(&pool->cond, &pool->lock);
		}


		if(pool->waiting_tasks == 0 && pool->shutdown == true)//b.停止状态
		{
			pthread_mutex_unlock(&pool->lock);//互斥锁解锁
			pthread_exit(NULL);//退出线程
		}


		p = pool->task_list->next;//指向任务队列下一个任务节点
		pool->task_list->next = p->next;//任务头节点的下一个赋值给线程池的变量
		pool->waiting_tasks--;//任务等待队列减1


		pthread_mutex_unlock(&pool->lock);//解锁
		pthread_cleanup_pop(0);//2


		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);//线程的分离相关知识
		(p->task)(p->arg);	
		printf("runtine is running ...\n");
		pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
		free(p->arg);
		free(p);
	}

	pthread_exit(NULL);
}
//初始化线程池
bool init_pool(thread_pool *pool, unsigned int threads_number)
{
	pthread_mutex_init(&pool->lock, NULL);//互斥锁
	pthread_cond_init(&pool->cond, NULL); //条件变量初始化，pool->cond条件变量

	pool->shutdown = false;//非关闭状态
	pool->task_list = malloc(sizeof(struct task));//为任务链表申请内存空间
	pool->tids = malloc(sizeof(pthread_t) * MAX_ACTIVE_THREADS);//为所有线程申请内存空间

	if(pool->task_list == NULL || pool->tids == NULL)//判断任务是否有任务、是否有线程
	{
		perror("allocate memory error");
		return false;
	}

	pool->task_list->next = NULL;

	pool->waiting_tasks = 0;
	pool->active_threads = threads_number;//当前线程个数

	int i;
	for(i=0; i<pool->active_threads; i++)//初始化所有的线程
	{
		if(pthread_create(&((pool->tids)[i]), NULL,
					routine, (void *)pool) != 0)
		{
			perror("create threads error");
			return false;
		}
	}

	return true;
}
//新增任务
bool add_task(thread_pool *pool,
			void *(*task)(void *arg), void *arg)
{
	struct task *new_task = malloc(sizeof(struct task));//为新任务申请内存空间
	if(new_task == NULL)
	{
		perror("allocate memory error");
		return false;
	}
	//给新任务数据赋值
	new_task->task = task;
	new_task->arg = arg;
	new_task->next = NULL;
	printf("new_task init successfully!\n");
	//
	pthread_mutex_lock(&pool->lock);//互斥锁上锁
	if(pool->waiting_tasks >= MAX_WAITING_TASKS)//判断等待任务数是否大于最大数
	{
		pthread_mutex_unlock(&pool->lock);

		fprintf(stderr, "too many tasks.\n");
		free(new_task);

		return false;
	}
	//把新的任务插入任务链表
	struct task *tmp = pool->task_list;
	while(tmp->next != NULL)
		tmp = tmp->next;//指向链表尾

	tmp->next = new_task;//把新任务节点插到链表尾
	pool->waiting_tasks++;//任务等待加1
	
	printf("insert new_task to pthread_pool tasklink tail successfully!\n");
	
	pthread_mutex_unlock(&pool->lock);//互斥锁解锁
	pthread_cond_signal(&pool->cond);//发送一个信号给另外一个正在处于阻塞等待状态的线程,使其脱离阻塞状态,继续执行.
	
	printf("close add_task successfully!\n");
	return true;
}
//新增线程，返回进程数
int add_thread(thread_pool *pool, unsigned additional_threads)
{
	if(additional_threads == 0)
		return 0;

	unsigned total_threads =
		     pool->active_threads + additional_threads;//总线程数

	int i, actual_increment = 0;
	//对线程池中的线程进行创建
	for(i = pool->active_threads;
	    i < total_threads && i < MAX_ACTIVE_THREADS;
	    i++)
	{
		if(pthread_create(&((pool->tids)[i]),
				NULL, routine, (void *)pool) != 0)
		{
			perror("add threads error");

			if(actual_increment == 0)
				return -1;

			break;
		}
		actual_increment++; //对实际创建的进程数计数
	}

	pool->active_threads += actual_increment;//更新活跃进程总数
	return actual_increment;
}
//移除线程
int remove_thread(thread_pool *pool, unsigned int removing_threads)
{
	if(removing_threads == 0)//移除个数为0，直接返回
		return pool->active_threads;

	int remain_threads = pool->active_threads - removing_threads;
	remain_threads = remain_threads>0 ? remain_threads:1;

	int i;
	for(i=pool->active_threads-1; i>remain_threads-1; i--)
	{
		errno = pthread_cancel(pool->tids[i]);
		if(errno != 0)
			break;
	}

	if(i == pool->active_threads-1)
		return -1;
	else
	{
		pool->active_threads = i+1;
		return i+1;
	}
}
//销毁线程池
bool destroy_pool(thread_pool *pool)
{

	pool->shutdown = true;
	pthread_cond_broadcast(&pool->cond);

	int i;
	for(i=0; i<pool->active_threads; i++)
	{
		errno = pthread_join(pool->tids[i], NULL);
		if(errno != 0)
		{
			printf("join tids[%d] error: %s\n",
					i, strerror(errno));
		}
		else
			printf("[%u] is joined\n", (unsigned)pool->tids[i]);
		
	}

	free(pool->task_list);
	free(pool->tids);
	free(pool);

	return true;
}

//拷贝普通文件,成功返回0，失败返回-1
void *copyregfile(void *arg)
{
	struct file * dofile = (struct file *)arg;
	printf("copyregfile is running...\n");
	struct stat file_stat;/*struct stat这个结构体是用来描述一个linux系统文件系统中的文件属性的结构*/
	stat(dofile->srcfile, &file_stat);//获取文件的属性

	int srcfd,dstfd;
	srcfd = open(dofile->srcfile,O_RDONLY);
	dstfd = open(dofile->dstfile,O_CREAT | O_TRUNC | O_RDWR,file_stat.st_mode);//以源文件的类型和权限创建文件

	if(srcfd == -1 || dstfd == -1)
	{
		perror("open file:");
		
		//return -1;
	}

	int nread;
	char buf[100];
	while((nread = read(srcfd,buf,100)) > 0)
	{
		if( write(dstfd,buf,nread) == -1)
		{
			break;
		}
	}

	close(dstfd);
	return NULL;
}



//拷贝目录,成功返回0.失败返回-1
int copydir(struct file* dofile)
{
	printf("copydir is running... \n");
	struct stat file_stat;
	stat(dofile->srcfile,&file_stat); //获取文件的属性
	mkdir(dofile->dstfile,file_stat.st_mode); //以源目录的类型和目录来创建一个目录

	DIR *srcdir = opendir(dofile->srcfile); //打开源目录
	struct dirent *dp;
	struct file *tmpfile = malloc(sizeof(struct file)); //对本目录下的所有文件进行拷贝操作

	while( (dp = readdir(srcdir))!=NULL )
	{
		memset(tmpfile,0,sizeof(struct file));

		if(dp->d_name[0] == '.') //如果文件为. 或者 .. 则跳过
		{
			continue;
		}

		sprintf(tmpfile->srcfile,"%s/%s",dofile->srcfile,dp->d_name);
		sprintf(tmpfile->dstfile,"%s/%s",dofile->dstfile,dp->d_name);
		

		struct stat tmpstat;
		stat(tmpfile->srcfile,&tmpstat);

		if(S_ISREG(tmpstat.st_mode))//如果为普通文件,则拷贝
		{
			copyregfile(tmpfile);  //这个是任务
			printf("%s\n",tmpfile->srcfile);
		}
		else if(S_ISDIR(tmpstat.st_mode))//如果为目录，则递归
		{
			copydir(tmpfile);
			printf("%s\n",tmpfile->srcfile);
		}

	}
	
	closedir(srcdir);
	free(tmpfile); 
	return 0;
}



int main(int argc,char *argv[])
{
	printf("enter\n");
	thread_pool *pool = malloc(sizeof(thread_pool));
	init_pool(pool, 20);
	//struct file *dofile = (struct file*)arg;
	if(argc != 3)
	{
		printf("Please run : ./%s xxx yyy\n",argv[0]);
		return -1;
	}
	
	struct file dofile;
	strcpy(dofile.srcfile,argv[1]);
	strcpy(dofile.dstfile,argv[2]);
	
	struct stat srcstat;
	stat(dofile.srcfile,&srcstat);
	
	if(S_ISREG(srcstat.st_mode))//如果为普通文件,则拷贝
	{
		add_task(pool,copyregfile,(void *)&dofile);
	}
	else if(S_ISDIR(srcstat.st_mode))//如果为目录，则递归
	{
		copydir(&dofile);
	}
	printf("current thread number: %d\n",
		remove_thread(pool, 0));	
	
			
	destroy_pool(pool);
	return 0;
}

