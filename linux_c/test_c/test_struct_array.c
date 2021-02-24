#include<stdio.h>
#include<string.h>
#include<stdio.h>
typedef struct 
{
    int num;
    char name[20];
    char sex;
    int age;
    float score;
    char addr[30];
}student;
char str[1000] = {0};
#define TELNET_MASTER "/dev/ptmx"
#define TELNET_SLAVE "/dev/pts"

student sss;

student return_str()
{
	return sss;
}

int main()
{
    int i;
	char* cPathTemp = "/dev/pts/5";
	char* str1 = "sssss";
	char* str2 = "aaaaa";
	student stu[3] = {0};
	for(i=0;i<3;i++)
    {
       //printf("%d %s %c %d %1f %s\n",stu[i].num,stu[i].name,stu[i].sex,stu[i].age,stu[i].score,stu[i].addr);
    }
   for(i=0;i<3;i++)
    {
       stu[i].num = i;
       //snprint(stu[i].name,20,"%d",(i+200));
	memcpy(stu[i].name,"dsdsd",10);
	stu[i].sex = 'F';
	stu[i].age = 10 +i;
	stu[i].score = 10 +i+20;
	memcpy(stu[i].addr,"asasasa",10);
	//snprint(stu[i].addr,20,"%d",(i+300));

    }
    for(i=0;i<3;i++)
    {
       //printf("%d %s %c %d %1f %s\n",stu[i].num,stu[i].name,stu[i].sex,stu[i].age,stu[i].score,stu[i].addr);
	memset(str,0,1000);
	snprintf(str,sizeof(str),"%s_%d_%s_%d",str2,i,str1,(i+10));
	printf("str = %s\n",str);
    }

	printf("(strstr(cPathTemp,/dev/ptmx)!=NULL) = %d\n",strstr(cPathTemp,TELNET_MASTER)!=NULL);
	printf("(strstr(cPathTemp,/dev/pts)!=NULL) = %d\n",strstr(cPathTemp,TELNET_SLAVE)!=NULL);

	sss.sex ='F';
	sss.age = 20;
	sss.score = 300;
	memcpy(sss.addr,"asasasa",10);


	

return 0;
    //return 0;
}
