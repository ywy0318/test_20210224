#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> //close()
#include <string.h> //strcmp()等字符串操作函数
#include <stdlib.h> //atoi() 字符串转int
 //gcc client.c -o client
int main(int argc, char *argv[])
{
	//检查命令行参数是否匹配
	if(argc != 3)
	{
		printf("请传递要连接的服务器的ip和端口号");
		return -1;
	}
	
	int port = atoi(argv[2]);//从命令行获取端口号
	if( port<1025 || port>65535 )//0~1024一般给系统使用，一共可以分配到65535
	{
		printf("端口号范围应为1025~65535");
		return -1;
	}
	
	//1 创建tcp通信socket
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd == -1)
	{
		perror("socket failed!\n");
	}
 
	//2 连接服务器
	struct sockaddr_in server_addr = {0};//服务器的地址信息
	server_addr.sin_family = AF_INET;//IPv4协议
	server_addr.sin_port = htons(port);//服务器端口号
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);//设置服务器IP
	int ret = connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if(ret == -1)
	{
		perror("connect failed!\n");
	}
	else
	{
		printf("connect server successful!\n");
	}
 
 
	//3 循环发送消息
	while(1)
	{
		char buf[1024] = {0};
		printf("Please enter msg:");
		scanf("%s",buf);
		write(socket_fd,buf,strlen(buf));//发送消息
		if(strcmp(buf, "exit") == 0)
		{
			break;//退出循环
		}
	}
 
	//4 关闭心贴心socket
	close(socket_fd);
 
	return 0;
}