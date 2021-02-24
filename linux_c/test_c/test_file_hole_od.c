#include "apue.h"
#include <fcntl.h>
char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";
int main(void)
{
	int fd;
	if((fd = creat("file_no.hole",FILE_MODE)) < 0 )
	{
		printf("create error");
		exit(1);
	}
	if(write(fd,buf1,sizeof(buf1))!=sizeof(buf1))
	{
		printf("buf1 write error");
		exit(1);
	}
	/*
	if(lseek(fd,16384,SEEK_SET) == -1)
	{
		printf("lseek error");
		exit(1);
	}
	*/
	if(write(fd,buf2,sizeof(buf2)) !=sizeof(buf2))
	{
		printf("buf2 write error");
		exit(1);
	}
	exit(0);

}
