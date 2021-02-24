
ll(上百万个客户)
epoll_create(创建一个epoll对象)
一般 epollfd=epoll_create();
int epoll_create(int size);
epoll_ctl(epoll_add|epoll_del的合体)
往epoll对象中添加删除一个流的某一个事件
int epoll_ctl(int epollfd,int op,int fd,struct  epoll_event*event);
EPOLL_CTL_ADD
EPOLL_CTL_DEL
EPOLL_CTL_MOD(LT|ET)

typedef union epoll data
{
	void*ptr;
	int fd;
	_unit32_t u32;
	_unit64_t u64;
	
}epoll_data_t;
struct epoll_event
{
	_unit32_t events;//epoll_event
	epoll_data_t data;//usr data variable
}

epoll_wait(epollfd,....)//等待直到注册的事发生
int epoll_wait(int epfd,struct epoll_event*events,int max events,int timeout);
while(TRUE)
{
	fd=epoll_wait();
	for(i=0;i<fd;i++)
	{
		do something;
		
	}
}

LT(level triggered)是缺省的工作方式，并且同时支持block和no_block socket;
在这种做法中，内核告诉你一个文件描述符是否就绪，然后就可以对这个就绪的fd
进行IO操作，如果你不做任何操作，内核还会继续通知你，所以这种模式出错可能小一点
传统的select/poll是这种模型的代表

ET(edge-triggered)是高速工作模式，只支持no_block模式，如果一直不对这个fd做iO
操作(从而导致它再次变成未就绪，)，内核不会发送更多的通知，only_once




*/

#include"socket_includes.h"
#include"unistd.h"
#include"sys/epoll.h"
#include"fcntl.h"
#include"unistd.h"
int ipv4_tcp_create_socket()
{
	
}
int process_data(int sockfd)
{
	int bytes;
	char buf[100];
	char *s=NULL;
	//检测time out 
	while(1)
	{
		bytes=recv(sockfd,s,100,0);
		
		if(bytes<0)
		{
			if(error==EAGIN)
			{
				printf("no data\n");
				break;
				
			}
			perror();
			return -1;
			
			
		}
		if(bytes==0)
		{
			return -2;
			
		}
		printf("buf:%s\n",buf);
		send(sockfd,buf,bytes,0);
		return 0;
		
	}
	s+=bytes;
}

int main(int argc,char *argv[])
{
	struct addr_in client;
	int len;
	int epollfd,listenfd;
	struct epoll_event ev;events[MAX_EVENTS];
	
	int fds,i,rv,sockfd;
	epollfd=epoll_create(MAX_EVENTs);
	if(epollfd<0)
	{
		perror("epoll_create failed");
		return -1;
	}
	listenfd=ipv4_tcp_create_socket();
	fcntl(epollfd,F_SETFL,O_NOBLOCK);//将监听套接字变成非阻塞套接字
	
	ev.data.fd=listenfd;
	ev.events=EPOLLIN;//有事件可读
	
	rv=epoll_ctl(epollfd,EPOLL_CTL_ADD,listenfd,&ev);
	
	if(rv<0)
	{
		perror();
		return -1;
		
	}
	while(1)
	{
		fd=epoll_wait(epollfd,eventd,MAX_EVENTS,-1);//-1表示如果没有事件永远等待
		for(i=0;i<fds;i++)
		{
			if(eventd[i].data.fd==listenfd)
			{
				sockfd=accept(listenfd,(struct sockaddr*)&client,&len);
				if(sockfd<0)
				{
					continue;
					perror();
				}
				ev.data.fd=sockfd;
				ev.events=EPOLLIN|EPOLLET;
				epollctl(epollfd,EPOLL_CTL_ADD,sockfd,&ev);
				continue;
			}
			else 
			{
			process_data(event[i].data.fd);
			if(rv==-2)
			{
				epoll_ctl(epollfd,EPOLL_CTL_DEL,events[i],data.fd,&ev);
				close(eventd[i].data.fd);
				continue;
			}
			
			}
		}
	}

A
A
A
A
A
A
A
A
A
A
A
A
A
A
A
A
A
A
A
A
A
A
A
A
A
A
B
B
B
B
B
B
B
B
B
}
