#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
typedef struct
{
	int array[10];
	int test[10];
}IDiskSt;

typedef struct 
{
	int num;
	int score;
	char name[128];

}stu;

stu aa[3];



int dst_array[10];
int src_array[10];
void test_struct()
{
	IDiskSt test[10];
	int i = 0;
	int j = 0;
	for(i = 0;i < 10;i++)
	{
		for(j = 0;j < 10;j++)
		{
			test[i].array[j]=i*2+j;
			test[i].test[j]=i*3+j;
			printf("i=%d,j=%d,%d-%d\n",i,j,test[i].array[j],test[i].test[j]);
			printf("---\n");
		}
	}
	
	
}

void test_array_memcpy()
{
	int i = 0;	
	memset(dst_array,0,10);
	memset(src_array,0,10);
	for(i = 0;i<10;i++)
	{
		src_array[i]=i+10;
	}
	memcpy(dst_array,src_array,sizeof(dst_array));
	
	for(i = 0;i<10;i++)
	{
		//src_array[i]=i+10;
		printf("src_array[%d]=%d\n",i,src_array[i]);
	}
	for(i = 0;i<10;i++)
	{
		//src_array[i]=i+10;
		printf("dst_array[%d]=%d\n",i,dst_array[i]);
	}
}
void test_bcpm()
{
	static FILE * g_fp_log_Template[3]={NULL};
	int i =0;
	for(i =0;i<3;i++)
	{
		printf("i=%d,%d\n",i,g_fp_log_Template[i]==NULL);
	}
}



void test_struct_array(stu *p)
{
	p->num = 1;
	p->num
}
int main()
{
	//test_bcpm();
	//test_struct();
	//test_array_memcpy();
	
	int i = 0;
	for(i = 0;i < 3;i++)
	{
		aa[i].num = 0;
		aa[i].score = 0;
		aa[i].name[0]='\0';
	}
	test_struct_array(aa);

	while(1)
	{
		printf("main finished...i=%d...\n",i);
		i++;
		sleep(2);
	}
	
}
