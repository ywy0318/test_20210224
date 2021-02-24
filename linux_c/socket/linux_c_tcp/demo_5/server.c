
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h> //atoi()
#include <pthread.h>
 
void * recv_msg(void *arg);//接收消息函数声明
void * send_msg(void *arg);//发送消息函数声明
 //（没有检查数组索引越界，在线程退出时没有处理好资源释放）
 //gcc server.c -o server -lpthread
 //gcc client.c -o client -lpthread
int main(int argc, char *argv[])
{
	//命令行需要传递一个参数
	if(argc != 2)
	{
		printf("请传递一个端口号\n");
		return -1;
	}
 
	//从命令行获取端口号
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
		perror("socket failed!\n");
		return -1;
	}
 
	//2 绑定socket地址
	struct sockaddr_in server_addr = {0};
	server_addr.sin_family = AF_INET;//AF_INET->IPv4  
	server_addr.sin_port = htons(port);// server port
	server_addr.sin_addr.s_addr = INADDR_ANY;//server ip (auto set by system)
	int ret = bind(socket_fd, (struct sockaddr *) &server_addr, sizeof(server_addr) );
	if(ret == -1)
	{
		perror("bind failed!\n");
		return -1;
	}
 
	//3 设置监听队列，设置为可以同时连接5个客户端
	ret = listen(socket_fd, 5);
	if(ret == -1)
	{
		perror("listen falied!\n");
		return -1;
	}
 
 
	printf("server is running!\n");
 
	struct sockaddr_in client_addr = {0};//用来存放客户端的地址信息
	int len = sizeof(client_addr);
	
	int i = 0;
	int socket_arr[5] = {0};//存放与客户端的通信socket
	pthread_t send_thread = 0;//存放发送线程的id
	while(1)//不断的接受客户端的请求
	{
		int new_socket_fd = -1;
		new_socket_fd = accept( socket_fd, (struct sockaddr *)&client_addr, &len);
		if(new_socket_fd == -1)
		{
			perror("accpet error!\n");
		}
		else
		{
			printf("[ID:%d] IP:%s, PORT:%d [connected]\n", i, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
			socket_arr[i] = new_socket_fd;
 
			//开启接收线程 一条接收线程对应一个连接的客户端
			pthread_t recv_thread;
			pthread_create(&recv_thread, NULL, recv_msg, (void*)&socket_arr[i]);
			i++;
			if(send_thread == 0)//只在第一次创建发送线程
			{
				pthread_create(&send_thread, NULL, send_msg, (void*)socket_arr);
			}
			
		}
	}
 
	//5 关闭socket
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
 
//发送线程所要执行的函数 发送消息
void * send_msg(void *arg)
{
	int (*socket_arr_pt)[5] = (int (*) [5])arg;//数组指针
	
	while(1)
	{
		int id = 0;
		char buf[1024] = {0};
		scanf("%d %s", &id, buf);
		if(id<0 || id>4)
		{
			printf("id 0~4");
			continue;
		}
		
		
		write( (*socket_arr_pt)[id], buf, sizeof(buf));
		
		if(strcmp(buf, "exit") == 0 || strcmp(buf, "") == 0)
		{
			
			break;
		}
	}
	
	//close(socket_arr[0]);
	return NULL;
}