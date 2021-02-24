#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h> //atoi()
 //gcc client.c -o client
 //效果：刚开始的时候，客户端没有连接，是没有超时现象，也就是select()还没有"工作"。
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
 
	//定义一个文件描述符集合
	fd_set fds;
	
	//3 发送消息
	while(1)
	{
		//清空文件描述符集合
		FD_ZERO(&fds);
		//把标准输入设备加入到集合中 
		FD_SET(0,&fds);
		//把网络通信文件描述符加入到集合中 
		FD_SET(socket_fd,&fds);
		
		
		ret = select(socket_fd+1,&fds,NULL,NULL,NULL);
		if(ret < 0)//错误
		{
			perror("select fail:");
			return -1;
		}
		else if(ret > 0) //有活跃的
		{
			//判断是否是 标准输入设备活跃 假设是则发送数据
			if(FD_ISSET(0,&fds))
			{
				char buf[1024] = {0};
				scanf("%s",buf);
				write(socket_fd,buf,strlen(buf));
				if(strcmp(buf, "exit") == 0)
				{
					break;
				}
			}
 
			//判断是否是socket_fd活跃，是则说明有数据收到
			if(FD_ISSET(socket_fd,&fds))
			{
				char buf[1024]={0};
				read(socket_fd,buf,sizeof(buf));
				printf("receive msg:%s\n",buf);
				if(strcmp(buf, "exit") == 0 || strcmp(buf, "") == 0)
				{
					break;
				}
 
 
			}
		}
		printf("·");//用来验证select的阻塞
	
	}
 
	//4 关闭通信socket
	close(socket_fd);
 
	return 0;
}