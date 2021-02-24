
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h> //atoi()
 //gcc server.c -o server 
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
	int new_socket_fd = -1;//存放与客户端的通信socket
	
	//4 等待客户端连接
	new_socket_fd = accept( socket_fd, (struct sockaddr *)&client_addr, &len);
	if(new_socket_fd == -1)
	{
		perror("accpet error!\n");
	}
	else
	{
		printf("IP:%s, PORT:%d [connected]\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
	}
 
	//定义一个文件描述符集合
	fd_set fds;
	//定义一个时间结构体  
	struct timeval  time;
	time.tv_sec = 5;//5秒
	time.tv_usec = 0;
 
	
	//循环监视文件描述符集合 	
	while(1)
	{
		//清空文件描述符集合
		FD_ZERO(&fds);
		//把标准输入设备加入到集合中 
		FD_SET(0,&fds);
		//把网络通信文件描述符加入到集合中 
		FD_SET(new_socket_fd, &fds);
		
		//select会更新超时参数以指示剩余时间
		time.tv_sec = 3;//3秒超时
		time.tv_usec = 0;
		
		//select会等待time这么久，time可以不设置，即填NULL，那么select会一直阻塞，直到集合中有活跃的描述符
		ret = select(new_socket_fd+1,&fds,NULL,NULL,&time);//阻塞等待time，直到集合中有活跃的描述符
		if(ret < 0)//错误
		{
			perror("select fail:");
			return -1;
		}
		else if(ret == 0) //超时
		{
			printf("timeout\n");
		}
		else if(ret > 0) //有活跃的  ret为1
		{
			//printf("ret=%d\n",ret);
			
			//判断是否是 标准输入设备活跃 假设是则发送数据 
			if(FD_ISSET(0, &fds))//标准输入的描述符是0
			{
				char buf[1024] = {0};
				scanf("%s",buf);
				write(new_socket_fd,buf,strlen(buf));
				if(strcmp(buf, "exit") == 0)
				{
					break;
				}
			}
			
			//判断是否是new_socket_fd活跃，(有消息收到)
			if(FD_ISSET(new_socket_fd,&fds))
			{
				char buf[1024] = {0};
				read(new_socket_fd, buf, sizeof(buf));
				printf("receive msg:%s\n", buf);
				if(strcmp(buf, "exit") == 0 || strcmp(buf, "") == 0)
				{
					break;
				}
			}
		}
		printf(".");//用来验证select的阻塞
		
	}
 
	//5 关闭通信socket
	close(new_socket_fd);
	close(socket_fd);
 
	return 0;
}