#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
char* stringsssss = NULL;
char *ssss=NULL;
char string[128];
char sd[128];

void test_copy_1(char* str1,char str2[])
{
	str1 = str2;
	printf("%s (%d) ........(%s) \n",__FUNCTION__,__LINE__,str1);
return ;

}
void test_copy_2(char* str1,char str2[])
{
	str2 = str1;
	printf("%s (%d) ........(%s) \n",__FUNCTION__,__LINE__,str2);
return ;

}

int main()
{
	char hello[128]="hello world";
	char* world = "yangweiyu";

	char* pcProcName = malloc(128);
	char* pcProcName2 = malloc(128);
	memcpy(pcProcName,"ssssszXSXxxxxxx",sizeof("ssssszXSXxxxxxx"));
	test_copy_1(stringsssss,hello);
	printf("%s (%d) ........ \n",__FUNCTION__,__LINE__);
	test_copy_2(world,string);
	printf("%s (%d).....sdsdsd ........ \n",__FUNCTION__,__LINE__);

	test_copy_1(pcProcName2,pcProcName);
	printf("%s (%d) ........ \n",__FUNCTION__,__LINE__);
	test_copy_2(pcProcName,sd);

	while(1);

}
