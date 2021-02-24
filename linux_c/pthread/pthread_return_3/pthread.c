#include <stdio.h>
#include <pthread.h>
#include <string.h>//strerror()
#include <stdlib.h>//calloc()
 //gcc pthread.c -o pthread -lpthread
/*
./pthread
arg==> s_id = 18,s_name =liang
join success ,retinfo==>:ret_num = 100,info = is ok

*/
typedef struct s_student
{
	int s_id;
	char s_name[16];
}Student;
 
typedef struct s_ret_info
{
	int ret_num;
	char info[64];
}Retinfo;
 
void* thread(void *arg)
{
	Student *stu = (Student*) arg;
	printf("arg==> s_id=%d, s_name=%s\n", stu->s_id, stu->s_name);
 
	Retinfo *retp = (Retinfo*)calloc(1, sizeof(Retinfo));
	retp->ret_num = 100;
	strcpy( retp->info, "is ok" );
 
	return (void*)retp;
}
 
 
int main(void)
{
	pthread_t tid;
	int retval;
	void *retp;
 
	Student stu1 = { 18, "liang"};
 
	retval = pthread_create( &tid, NULL, thread, &stu1);//创建线程
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
 
	Retinfo *retinfo = (Retinfo*) retp;
	printf("join success, retinfo==>:ret_num=%d, info=%s\n", retinfo->ret_num, retinfo->info);
 
	return 0;
}