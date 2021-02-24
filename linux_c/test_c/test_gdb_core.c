#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
	while(1)
	{
		printf("%s %s (%d) YWY.\n",__FILE__,__FUNCTION__,__LINE__);
sleep(2);
	}
	return 0;
}
