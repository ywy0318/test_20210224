
//UDP 接收广播信息
#include <stdio.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
 //gcc recv.c -o recv 
 //gcc send.c -o send 
// 广播的发送与接收。send往xxx端口发送广播消息，在同以网段中绑定xxx端口的recv程序就会收到广播消息
 // 某个应用往xxx端口发出广播，在同一网段的绑定xxx端口的所有应用都会收到广播的消息（如果发出广播消息的应用板绑定的也是xxx端口，也会收到广播消息）。如飞秋软件的好友上下线通知。
 
int main(int argc,char *argv[])
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
	
	// 1.创建udp通信socket  
	int udp_socket_fd = socket(AF_INET,SOCK_DGRAM,0);
	if(udp_socket_fd < 0 )
	{
		perror("creat socket fail\n");
		return -1;
	}
 
	//2.设置UDP的地址并绑定 
	struct sockaddr_in  local_addr = {0};
	local_addr.sin_family  = AF_INET; //使用IPv4协议
	local_addr.sin_port	= htons(port);   //网络通信都使用大端格式
	local_addr.sin_addr.s_addr = INADDR_ANY;//inet_addr("0.0.0.0");;//Linux下，需要设为0.0.0.0才能接收到广播
 
	int ret = bind(udp_socket_fd,(struct sockaddr*)&local_addr,sizeof(local_addr));
	if(ret < 0)
	{
		perror("bind fail:");
		close(udp_socket_fd);
		return -1;
	}
	else
	{
		printf("recv ready!!!\n");
	}
	
	
	
	struct sockaddr_in  src_addr = {0};  //用来存放对方(信息的发送方)的IP地址信息
	int len = sizeof(src_addr);	//地址信息的大小
	char buf[1024] = {0};//消息缓冲区
	
	//3 循环接收客户发送过来的数据  
	while(1)
	{
		ret = recvfrom(udp_socket_fd, buf, sizeof(buf), 0, (struct sockaddr *)&src_addr, &len);
		if(ret == -1)
		{
			break;
		}
		
		printf("[%s:%d]",inet_ntoa(src_addr.sin_addr),ntohs(src_addr.sin_port));//打印消息发送方的ip与端口号
		printf("buf=%s\n",buf);
		if(strcmp(buf, "exit") == 0)
		{
			break;//收到"exit"退出循环
		}
		memset(buf, 0, sizeof(buf));//清空存留消息
 
	}
	
	//4 关闭通信socket
	close(udp_socket_fd);
	return 0;
}