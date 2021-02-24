#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	char buf[128] = {0};
	char cmd[256] = {0};
	printf("hello world\n");
	snprintf(buf,128,"%s (%d) %s",__FUNCTION__,__LINE__,"hello world!!YWY");
	printf("buf = %s\n",buf);
	snprintf(cmd,256,"echo '%s' >>./a.txt",buf);
	printf("cmd = %s\n",cmd);
	system(cmd);
	memset(buf,0,128);
	memset(cmd,0,256);
	snprintf(buf,128,"%s (%d) %s",__FUNCTION__,__LINE__,"LoL!!YWY");
	printf("buf = %s\n",buf);
	snprintf(cmd,256,"echo '%s' >>./a.txt",buf);
	printf("cmd = %s\n",cmd);
	system(cmd);
	return 0;
}
