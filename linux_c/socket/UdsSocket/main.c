#include <stdio.h>
#include "udsSocket.h"
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
 
int gSockFd = -1;
pthread_t gRecv_thread = -1;
void * recv_msg(void *arg);
void releaseResource(int sigNo);
 
int main(int argc, char* argv[])
{
	int ret;
	char buf[1024] = {0};
	char destAddr[1024] = {0};
	
	if(argc<2)
	{
		printf("eg:./main /home/liang/sock_A\n");
		return -1;
	}
	
	//绑定sock
	printf("addr:%s,\n",argv[1]);
	int gSockFd = udsBind(argv[1], strlen(argv[1]));
	if(gSockFd<=0)
	{		
		return -1;
	}
	
	//printf("gSockFd:%d,\n",gSockFd);
	
	//捕捉Ctrl+C信号，用来释放资源
	signal(SIGINT, releaseResource);
	
	//创建接收线程	
	pthread_create(&gRecv_thread, NULL, recv_msg, (void*)&gSockFd);
	
	//循环发送消息
	while(1)
	{
		printf("destAddr Msg:");
		scanf("%s %s", destAddr, buf);
		if(strlen(buf)>0)
		{
			ret = udsSendMessage(gSockFd, buf, strlen(buf), destAddr);
			printf("buf:%s, ret:%d,\n", buf, ret);
			if(ret<=0)
			{
				printf("send ret：%d.\n", ret);
			}
		
			if(strcmp(buf, "exit") == 0)
			{				
				break;
			}
		}		
		
		memset(buf, 0, sizeof(buf));
		memset(destAddr, 0, sizeof(destAddr));
	}
	
	//关闭子线程
	if(gRecv_thread>=0)
	{
		pthread_cancel(gRecv_thread);
		gRecv_thread = -1;
	}
	
	printf("exit program!\n");
	return 0;
}
 
//处理挂断信号--SIGINT
void releaseResource(int sigNo)
{
	//关闭通信socket
	if(gSockFd>=0)
	{
		close(gSockFd);
	}
	
	//关闭子线程
	if(gRecv_thread>=0)
	{
		pthread_cancel(gRecv_thread);
		gRecv_thread = -1;
	}
	
	printf("\nRelease resource.\n");
	exit(0);
}
 
//接收线程所要执行的函数 接收消息
void* recv_msg(void *arg)
{
	int ret = 0;
	int *socket_fd = (int *)arg;//通信的socket
	struct sockaddr_un  src_addr;  //用来存放对方(信息的发送方)的IP地址信息
	char msg[1024] = {0};//消息缓冲区
	char msg2[1024] = {0};//消息缓冲区
	socklen_t sockLen = sizeof(src_addr);
	
	if(*socket_fd<1)
	{
		return (void *)-1;
	}
	
	memset(&src_addr, 0, sizeof(src_addr));
	
	//循环接收客户发送过来的数据  
	while(1)
	{
		//ret = udsRecv(*socket_fd, msg);
		ret = recvfrom(*socket_fd, msg, sizeof(msg), 0, (struct sockaddr *)&src_addr, &sockLen);
		if(ret>=0)
		{
			//printf("\n[RECV From %s:%d]%s,\n", inet_ntoa(src_addr.sin_addr), ntohs(src_addr.sin_port), msg);//打印消息发送方的ip与端口号 本地套接字都是在本机通信的，sockaddr_un结构体没有IP和端口的成员，sockaddr_in结构体有
			printf("\n[RECV From %s]%s\n", src_addr.sun_path, msg);
			printf("destAddr Msg:");
			fflush(stdout);
			if(strcmp(msg, "exit") == 0)
			{
				//通知主线程。。。
				break;
			}	
			memset(msg, 0, sizeof(msg));//清空上次消息
		}
		usleep(400);			 
	}
	
	//关闭通信socket
	close(*socket_fd);
	printf("exit program!\n");
	exit(0);
	return NULL;
}