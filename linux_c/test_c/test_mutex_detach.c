#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
typedef struct ct_sum
{	int sum;
	pthread_mutex_t lock;
}ct_sum;
void * add1(void * cnt)
{     
   
   	pthread_mutex_lock(&(((ct_sum*)cnt)->lock));
   	int i;
       	for( i=0;i<50;i++)
	{
		(*(ct_sum*)cnt).sum+=i;
	}
	printf("add1 sum %d\n",(*(ct_sum*)cnt).sum);
   	pthread_mutex_unlock(&(((ct_sum*)cnt)->lock));
  	pthread_exit(NULL);
  	return 0;
}
void * add2(void *cnt)
{     
   	int i;
   	cnt= (ct_sum*)cnt;
   	pthread_mutex_lock(&(((ct_sum*)cnt)->lock));
   	for( i=50;i<101;i++)
   	{    
		(*(ct_sum*)cnt).sum+=i;       
   	}
	printf("add2 sum %d\n",(*(ct_sum*)cnt).sum);
  	pthread_mutex_unlock(&(((ct_sum*)cnt)->lock));
   	pthread_exit(NULL);
   	return 0;
}


void test_mutex()
{
	int i;
	pthread_t ptid1,ptid2;
	int sum=0;
	ct_sum cnt;
	pthread_mutex_init(&(cnt.lock),NULL);
	cnt.sum=0;
	pthread_create(&ptid1,NULL,add1,&cnt);
	pthread_create(&ptid2,NULL,add2,&cnt);
 
	pthread_mutex_lock(&(cnt.lock));
	printf("sum %d\n",cnt.sum);
	pthread_mutex_unlock(&(cnt.lock));
	pthread_join(ptid1,NULL);
	pthread_join(ptid2,NULL);
	pthread_mutex_destroy(&(cnt.lock));
	return ;
}
void *thread_function(void *arg)
{
  int i;
  for ( i=0;; i++)
 {
    printf("Thread working...! %d \n",i);
    sleep(1);
  }
  return NULL;
}
//pthread_join()函数，以阻塞的方式等待thread指定的线程结束。当函数返回时，被等待线程的资源被收回。如果线程已经结束，那么该函数会立即返回。并且thread指定的线程必须是joinable的。
void test_pthread_join()
{
	pthread_t mythread;
	if ( pthread_create( &mythread, NULL, thread_function, NULL) )
	{
		printf("error creating thread.");
		abort();
	}
	/*
	if ( pthread_join ( mythread, NULL ) )
	{
		printf("error join thread.");
		abort();
	}
	*/
	printf("thread done! \n");
	exit(0);

}
void test_pthread()
{
	pthread_t mythread;
	if ( pthread_create( &mythread, NULL, thread_function, NULL) )
	{
		printf("error creating thread.");
		abort();
	}
	
	printf("thread done! \n");
	exit(0);

}
//有两种方式创建分离线程：
//（1）在线程创建时将其属性设为分离状态(detached)；
//（2）在线程创建后将其属性设为分离的(detached)。
/*
void test_detach()
{
    pthread_t mythread;
    pthread_create( &mythread, NULL, thread_function, NULL); 
		
    pthread_detach(mythread);  // 使线程处于分离状态
    sleep(1);
    printf("Leave main thread!\n");
    pthread_exit("end"); //这个地方执行后，子进程并没有退出
    //return 0; //return后，系统会调用_exit，所有进程都会退出。

}
*/



void test_detach()
{
	pthread_t mythread;
	if ( pthread_create( &mythread, NULL, thread_function, NULL) )
	{
		printf("error creating thread.");
		abort();
	}
	
	pthread_detach(mythread);
	printf("pthread_detach(mythread) \n");
	sleep(1);
	printf("leave test_detach() \n");
	//pthread_exit("end");////这个地方执行后，子进程并没有退出
	return; //return 后，系统会调用_exit，所有进程都会退出。 	
}
int main(void)
{ 	
	int i = 0;
	//test_mutex();
	//test_pthread_join();
	//test_pthread();
	test_detach();
	while(1)
	{
		if(i==10)
		{
			break;	
		}
		printf("main function()...\n");	
		//i++;	//main函数不退出,线程不会退出
		sleep(1);
	}
	printf("main function finished.... \n");
	pthread_exit(NULL);//test_detach以后线程不会退出
//	return 0;
} 

