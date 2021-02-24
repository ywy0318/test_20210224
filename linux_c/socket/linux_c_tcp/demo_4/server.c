#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h> //atoi()
 //多个客户端，一个服务器，客户端发送信息，服务端接收消息。(只能接收最后连接的客户端的消息，因为代码中只处理最新获取的socket)
 //gcc server.c -o server
 //gcc client.c -o client
int main(int argc, char *argv[])
{
	//判断命令行参数是否满足
	if(argc != 2)
	{
		printf("请传递一个端口号\n");
		return -1;
	}
 
	//将接收端口号并转换为int
	int port = atoi(argv[1]);
	if( port<1025 || port>65535 )//0~1024一般给系统使用，一共可以分配到65535
	{
		printf("端口号范围应为1025~65535");
		return -1;
	}
 
	//1 创建tcp通信socket
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd == -1)
	{
		perror("创建tcp通信socket失败!\n");
		return -1;
	}
 
	//2 绑定socket地址
	struct sockaddr_in server_addr = {0};//存放地址信息
	server_addr.sin_family = AF_INET;//AF_INET->IPv4  
	server_addr.sin_port = htons(port);//端口号
	server_addr.sin_addr.s_addr = INADDR_ANY;//让系统检测本地网卡，自动绑定本地IP
	int ret = bind(socket_fd, (struct sockaddr *) &server_addr, sizeof(server_addr) );
	if(ret == -1)
	{
		perror("bind failed!\n");
		return -1;
	}
 
	//3 设置监听队列，设置为可以接受5个客户端连接
	ret = listen(socket_fd, 5);
	if(ret == -1)
	{
		perror("listen falied!\n");
	}
 
 
	printf("server is running!\n");
 
	struct sockaddr_in client_addr = {0};//用来存放客户端的地址信息
	int len = sizeof(client_addr);
	int new_socket_fd = -1;//存放与客户端的通信socket
	
	//循环接受客户端
	while(1)
	{
		new_socket_fd = accept( socket_fd, (struct sockaddr *)&client_addr, &len);//阻塞，直到有客户端连接，才会向下执行
		if(new_socket_fd == -1)
		{
			perror("accpet error!\n");
		}
		else
		{
			printf("IP:%s, PORT:%d [connected]\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
		}
		
		char buf[1024] = {0};
		read(new_socket_fd, buf, sizeof(buf));//接收最新客户端的消息。
		printf("receive msg:%s\n", buf);
		if(strcmp(buf, "exit") == 0)
		{
			break;
		}
	}
 
	//5 关闭通信socket
	close(new_socket_fd);
	close(socket_fd);
 
	return 0;
}