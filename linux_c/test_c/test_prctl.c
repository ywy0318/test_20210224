#include <stdlib.h>
#include <stdio.h>
#include<sys/prctl.h>

int main()
{
	char name[128] = {0};
	prctl(PR_GET_NAME,&name, 0, 0);
	printf("%s %s (%d) YWY........%s \n",__FILE__,__FUNCTION__,__LINE__,name);
	while(1);
	return 0;	
}
