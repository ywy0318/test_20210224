#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h> //atoi()
#include <pthread.h>
 
void * recv_msg(void *arg);
 
int main(int argc, char *argv[])
{
	//判断参数个数是否匹配
	if(argc != 3)
	{
		printf("请传递要连接的服务器的IP和端口号\n");
		return -1;
	}
	
	int port = atoi(argv[2]);//从命令行接收参数
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
 
	
	//开启接收线程
	pthread_t recv_thread;//存放线程id       recv_msg：线程执行的函数，将通信socket：new_socket_fd传递进去
	ret = pthread_create(&recv_thread, NULL, recv_msg, (void*)&socket_fd);
	if(ret != 0)
	{
		printf("开启线程失败\n");
	}
	
 
	//3 循环发送消息
	while(1)
	{
		char buf[1024] = {0};
		scanf("%s",buf);
		write(socket_fd,buf,strlen(buf));
		if(strcmp(buf, "exit") == 0 || strcmp(buf, "") == 0)
		{
			pthread_cancel(recv_thread);//取消接收线程
			break;
		}
	}
 
	//4 关闭socket
	close(socket_fd);
 
	return 0;
}
 
//接收线程所要执行的函数 接收消息
void * recv_msg(void *arg)
{
	int *socket_fd = (int *)arg;//通信的socket
	while(1)
	{
		char buf[1024] = {0};
		read(*socket_fd, buf, sizeof(buf));//阻塞，等待接收消息
		printf("receive msg:%s\n", buf);
		if(strncmp(buf, "exit", 4) == 0 || strcmp(buf, "") == 0)
		{
			//通知主线程。。。
			
			break;//退出
		}
	}
	return NULL;
}
