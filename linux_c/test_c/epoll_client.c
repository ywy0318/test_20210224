#include <netinet/in.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
 
#define MAXSIZE 1024
#define IPADDRESS "127.0.0.1"
#define SERV_PORT 8888
#define FDSIZE 1024
#define EPOLLEVENTS 20
 
static void handle_connection(int sockfd);
static void handle_events(int epollfd, struct epoll_event *events, int num, int sockfd, char *buf);
static void do_read(int epollfd, int fd, int sockfd, char *buf);
static void do_write(int epollfd, int fd, int sockfd, char *buf);
static void change_event(int epollfd, int fd, int state, int op);
 
 
int main()
{
    int sockfd;
    struct sockaddr_in server_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
    {
        perror("client create socket failed\n");
 	exit(EXIT_SUCCESS);
    }
 
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, IPADDRESS, &server_addr.sin_addr);
    
    socklen_t length = sizeof(server_addr);
    if (connect(sockfd, (struct sockaddr*)&server_addr, length) < 0)
    {
        perror("clint connect failed\n");
        exit(EXIT_SUCCESS);
    }   
    //deal with connection
    handle_connection(sockfd);
    //do not forget to close sockfd
    close(sockfd);
    return 0;    
}
static void handle_connection(int sockfd)
{
    int epollfd;
    struct epoll_event events[EPOLLEVENTS];
    char buf[MAXSIZE];
    memset(buf, 0, sizeof(buf));
    int result;
    epollfd = epoll_create(FDSIZE);
    change_event(epollfd, STDIN_FILENO,EPOLLIN, EPOLL_CTL_ADD);		//STDIN_FILENO 接受键盘的输入
    while (1)
    {
       result = epoll_wait(epollfd, events, EPOLLEVENTS, -1);
       printf("clinet need deal events is %d\n", result);
       handle_events(epollfd, events, result, sockfd, buf);
    }
    //do not forget to close epollfd
    close(epollfd);
}
static void handle_events(int epollfd, struct epoll_event *events, int num, int sockfd, char *buf)
{
    int fd;
    int i;
    for (i = 0; i < num; i++) 
    {
        fd = events[i].data.fd;
        if (events[i].events & EPOLLIN)
        {
           do_read(epollfd, fd, sockfd, buf);		//可能读标准输入 也可能读服务端传来的socket输入
        }
        else if (events[i].events & EPOLLOUT)
        {
           do_write(epollfd, fd, sockfd, buf);		//可能写标准输出 也可能向服务端写输出
        }
    }
}
static void do_read(int epollfd, int fd, int sockfd, char *buf)
{
    int nread;
    nread = read(fd, buf, MAXSIZE);
    if (nread == -1) 
    {
       perror("client read fail\n");
       close(fd);
    }
    else if (nread == 0)
    {
       fprintf(stderr, "server close\n");
       close(fd);
    }
    else 
    {
        if (fd == STDIN_FILENO)
        {
            puts("do read fd == STDIN_FILENO");
            change_event(epollfd, sockfd, EPOLLOUT, EPOLL_CTL_ADD);   //read完成键盘的输入之后  将客户端的sockfd更改为监听可写状态 用于向服务端socket写数据
        }
        else 
        {
            puts("do read fd != STDIN_FILENO");
            change_event(epollfd, sockfd, EPOLLIN, EPOLL_CTL_DEL);
            change_event(epollfd, STDOUT_FILENO, EPOLLOUT, EPOLL_CTL_ADD);//read完socket数据后将标准输出更改为可写  准备输出数据
        }
    }
}
static void do_write(int epollfd, int fd, int sockfd, char *buf)
{
    int nwrite;
    nwrite = write(fd, buf, strlen(buf));
    if (nwrite == -1)
    {
        perror("client write failed\n");
        close(fd);
    }
    else 
    {
        if (fd == STDOUT_FILENO)
        {  
           puts("do write fd == STDOUT_FILENO");
           change_event(epollfd, fd, EPOLLOUT, EPOLL_CTL_DEL);
        } 
        else 
        {
           puts("do write fd != STDOUT_FILENO");
           change_event(epollfd, fd, EPOLLIN, EPOLL_CTL_MOD);
        }
    }
    memset(buf, 0, MAXSIZE);
}
static void change_event(int epollfd, int fd, int state, int op)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, op, fd, &ev);
}
 
 