#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

void test_read()
{
    int fd,size;
    char s [ ]="Linux Programmer!!!!!SSSSS!\n";
	char buffer[80];
    fd=open("./test.txt",O_WRONLY|O_CREAT);
    size = write(fd,s,sizeof(s));
   
printf("size = %d sizeof(s) = %d fd = %d\n",size,sizeof(s),fd);
 close(fd);
size = 0 ;

	fd=open("./test.txt",O_RDONLY);
    size=read(fd,buffer,sizeof(buffer));
printf("size = %d sizeof(s) = %d fd = %d\n",size,sizeof(s),fd);
    close(fd);
    printf("%s",buffer);
	return ;	
}

void test_lseek()
{
	int fd,size;
	 fd=open("./test.txt",O_RDWR|O_APPEND);
	size = lseek(fd, 0, SEEK_END);
printf("size = %d \n ",size);

	close(fd);
}

int main()
{
	test_read();
	sleep(10);
	test_lseek();
    return 0;
   
}
