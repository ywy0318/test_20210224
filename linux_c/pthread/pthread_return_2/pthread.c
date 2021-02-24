#include <stdio.h>
#include <pthread.h>
#include <string.h>//strerror()
 //运行结果：pthread_exit()
 //gcc pthread.c -o pthread -lpthread
 //./pthread
 /*
 arg = hellp
 join success,rept = world--exit
 */
void test(char *arg)
{
	printf("arg=%s\n", arg);
}
 
void* thread(void *arg)
{
	char *str_arg = (char*)arg;
	if(strcmp(str_arg, "hello") == 0)
	{
		test(str_arg);
		pthread_exit("world--exit");
	}
	
	printf("=======");
	return "world--return";
}
 
 
int main(void)
{
	pthread_t tid;
	int retval;
	void *retp ;
 
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