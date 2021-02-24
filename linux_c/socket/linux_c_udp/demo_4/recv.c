//接收组播消息
#include <stdio.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
 //recv程序加入组播，当其他应用往该组发送组播消息时，recv程序将收到其他应用发给组的消息。
//            (同时也可以收到指定发给自己的消息)
//gcc recv.c -o recv 
//gcc send.c -o send 
int main(int argc,char *argv[])
{
	//命令行传参，默认系统会传递一个参数--可执行文件的名称，我们传递的第一个参数是argv[1]
	//判断命令行参数是否满足
	if(argc != 3)
	{
		printf("请传递组播ip，及要绑定的端口号\n");
		return -1;
	}
 
	//将接收端口号并转换为int
	int port = atoi(argv[2]);
	if( port<1025 || port>65535 )//0~1024一般给系统使用，一共可以分配到65535
	{
		printf("端口号范围应为1025~65535");
		return -1;
	}
	
	//1、 创建udp通信socket  AF_INET：IPv4协议，SOCK_DGRAM：UDP数据报，0：默认属性
	int udp_socket_fd = socket(AF_INET,SOCK_DGRAM,0);
	if(udp_socket_fd < 0 )
	{
		perror("creat socket fail\n");
		return -1;
	}
 
		
	//2、加入组播  组播地址224.0.0.0~239.255.255.255 
	struct ip_mreq zu = {0};
	zu.imr_multiaddr.s_addr = inet_addr(argv[1]);  //设置组播地址
	zu.imr_interface.s_addr = inet_addr("0.0.0.0");  
	int ret = setsockopt(udp_socket_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &zu, sizeof(zu));
	if(ret < 0)
	{
		perror("setsockopt fail\n");
		return -1;
	}
	else
	{
		printf("已经加入组：[%s:%d], 等待接收组消息！！！\n", argv[1], port);
	}
	
	//3、设置UDP的地址并绑定 
	struct sockaddr_in  local_addr = {0};//地址信息结构体
	local_addr.sin_family  = AF_INET; //使用IPv4协议
	local_addr.sin_port	= htons(port);   //网络通信都使用大端格式
	local_addr.sin_addr.s_addr =  inet_addr("0.0.0.0");  //32位的整形   
	//注意：Linux下，加入组播后，绑定地址只能绑定0.0.0.0地址否则会接收不到数据
 
	ret = bind(udp_socket_fd, (struct sockaddr*)&local_addr, sizeof(local_addr));
	if(ret < 0)
	{
		perror("bind fail:");
		return -1;
	}	
	
	struct sockaddr_in  src_addr={0};  //定义一个缓冲区 存放对方的IP地址信息
	int len = sizeof(src_addr);
	char buf[1024] = {0};//消息缓冲区
	
	//4 接收消息 
	while(1)
	{
		recvfrom(udp_socket_fd, buf, sizeof(buf), 0, (struct sockaddr *)&src_addr, &len);
		printf("[IP:%s,PORT:%d]",inet_ntoa(src_addr.sin_addr),ntohs(src_addr.sin_port));//打印消息发送者的IP信息
		printf(" buf=%s\n", buf);//打印消息
		if(strcmp(buf, "exit") == 0)
		{
			break;//当接收到"exit"时退出循环
		}
		
		bzero(buf, sizeof(buf));//清空接收到的消息，避免影响下次接收
	}	
}