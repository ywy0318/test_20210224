#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <errno.h>
 
#define IPADDRESS "127.0.0.1"
#define PORT 8888
#define MAXSIZE 1024
#define LISTENQ 5
#define FDSIZE 1000
#define EPOLLEVENTS 100
 
//bind socket
static int socket_bind(const char* ip, int port);
//io epoll
static void do_epoll(int listenfd);
//deal with events
static void handle_events(int epollfd, struct epoll_event *event, int num, int listenfd, char *buf);
//deal with accpet events
static void handle_accpet(int epolled, int listenfd);
//deal with read
static void do_read(int epollfd, int fd, char *buf);
//deal with  write
static void do_write(int epollfd, int fd, char *buf);
//change event
static void change_event(int epolled, int fd, int state, int op);
 
 
 
int main()
{
    printf("EPOLL_CTL_ADD is %d\n", EPOLL_CTL_ADD);
    printf("EPOLL_CTL_DEL is %d\n", EPOLL_CTL_DEL);
    printf("EPOLL_CTL_MOD is %d\n", EPOLL_CTL_MOD);
    int listenfd;
    listenfd = socket_bind(IPADDRESS, PORT);
    listen(listenfd, LISTENQ);
    do_epoll(listenfd);						//while 结构
    puts("epoll server end");
    return 0;
}
 
//bind socket
static int socket_bind(const char* ip, int port)
{ 
    int listenfd;
    struct sockaddr_in serveraddr;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1)
    {
       perror("create socket failed\n");
       exit(EXIT_FAILURE);
    }
    //please do not forget bzero serveraddr
    bzero(&serveraddr, sizeof(serveraddr));
    //init serveraddr
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &serveraddr.sin_addr);
    //please do not forget this is htons(port). not is port
    serveraddr.sin_port = htons(port);
    if (bind(listenfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) == -1)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    return listenfd;
}
 
//io epoll
static void do_epoll(int listenfd)
{
    int epollfd;
    struct epoll_event events[EPOLLEVENTS];
    int  result;
    char buf[MAXSIZE];
    memset(buf, 0, MAXSIZE);
 
	//函数原型：int epollfd = epoll_create(int size);
    //函数解释：创建一个epoll的句柄，size用来告诉内核这个监听的数目一共有多大
    epollfd = epoll_create(FDSIZE);
	
    //add listen listenfd event
    change_event(epollfd, listenfd, EPOLLIN, EPOLL_CTL_ADD);
    while (1)
    {
         //函数原型： int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);
　　		 //函数解释：等待事件的产生，类似于select()调用
		 //参数events用来从内核得到事件的集合，maxevents告之内核这个events有多大
		 //参数timeout是超时时间（毫秒，0会立即返回，-1将不确定，也有说法说是永久阻塞）
		 //该函数返回需要处理的事件数目，如返回0表示已超时。
         result = epoll_wait(epollfd, events, EPOLLEVENTS, -1);
         printf("need deal with events is %d\n", result);
         handle_events(epollfd, events, result, listenfd, buf); 
    }
    close(epollfd);
   
}
 
//deal with events
static void handle_events(int epollfd, struct epoll_event *events, int num, int listenfd, char *buf)
{
    int i;
    int fd;
    //foreach
    for (i = 0; i < num; ++i)
    {
         fd = events[i].data.fd;
         //deal with events by fd
         if ((fd == listenfd) && (events[i].events & EPOLLIN)) 		//表示在监听描述符上有数据  三次握手accept
         {
            puts("has go in handle_accpet");
            handle_accpet(epollfd, listenfd);
         }
         else if (events[i].events & EPOLLIN)
         { 
            puts("do read");  
            do_read(epollfd, fd, buf);
 	 	}
         else if (events[i].events & EPOLLOUT)
         {
            puts("do write");
            do_write(epollfd, fd, buf);
         }
    }
}
//deal with accpet events
static void handle_accpet(int epolled, int listenfd)
{
    int clifd;
    struct sockaddr_in cli_addr;
    socklen_t length = sizeof(cli_addr);
    clifd = accept(listenfd, (struct sockaddr*)&cli_addr, &length);
//    if (clifd < 0) {
    if (clifd == -1)
        perror("accept failed\n");
//      exit(EXIT_FAILURE);
//    }  
    else 
    {
        printf("accpet a new client:ip is %s and portsi %d\n", inet_ntoa(cli_addr.sin_addr), cli_addr.sin_port);
        //add client event
        change_event(epolled, clifd, EPOLLIN, EPOLL_CTL_ADD);
    }
}
//deal with read
static void do_read(int epollfd, int fd, char *buf)
{
    int nread;
    nread = read(fd, buf, MAXSIZE);
    if (nread == -1) 
    {
        perror("read data failed\n");
        close(fd);
        //delelet event
        change_event(epollfd, fd, EPOLLIN, EPOLL_CTL_DEL);        
    }
    else if (nread == 0)
    {
        fprintf(stderr, "client close\n");
        close(fd);
        //delete event
        change_event(epollfd, fd, EPOLLIN, EPOLL_CTL_DEL);        
    }
    else 
    {
        printf("read message is  %s\n", buf);
        //change event. from read to write
        change_event(epollfd, fd, EPOLLOUT, EPOLL_CTL_MOD);
    }
}
//deal with  write
static void do_write(int epollfd, int fd, char *buf)
{
    int nwrite;
    nwrite = write(fd, buf, strlen(buf));
    if (nwrite == -1)
    {
        perror("write falied\n");
        close(fd);
        change_event(epollfd, fd, EPOLLOUT, EPOLL_CTL_DEL);		//不可写时从epollfd中删除监听的fd
    }
    else 
    {
        change_event(epollfd, fd, EPOLLIN, EPOLL_CTL_MOD);
        memset(buf, 0, MAXSIZE);
    }
}
//change event
static void change_event(int epollfd, int fd, int state, int op)
{
    struct epoll_event ev;
    ev.events = state;					
    ev.data.fd = fd;
 
	//函数原型：int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
	//函数解释：参数一epfd为epoll_create返回的创建fd
	//			参数二op为需要执行的操作(EPOLL_CTL_ADD：注册新的fd到epfd中；EPOLL_CTL_MOD：修改已经注册的fd的监听事件；EPOLL_CTL_DEL：从epfd中删除一个fd；)
	//			参数三fd为要监听的fd套接字
	//			参数四event为要监听的状态   在ev.states=state,中赋值  包括EPOLLIN、EPOLLOUT
	epoll_ctl(epollfd, op, fd, &ev);
}
 