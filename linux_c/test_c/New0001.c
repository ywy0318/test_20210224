#include<stdio.h>
#include <stdlib.h>  
#include <unistd.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <string.h>   
#include <sys/socket.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <sys/epoll.h>
#define MAX_EVENTS 256 
typedef struct fd_buff
{
    int fd;
    char buff[1024];
} fd_buff_t,*fd_buff_p;
struct epoll_event evts[256];
static void usage(char* proc)
{
    printf("usage:%s[server ip][server port]",proc);
}
int startup(char* ip,int port)
{
    int sock=socket(AF_INET,SOCK_STREAM,0);
    if(sock<0)
    {
        perror("socket");
        exit(2);
    }
    int op=1;
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&op,sizeof(op));
    struct sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(port);
    server_addr.sin_addr.s_addr=inet_addr(ip);
    if(bind(sock,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
        perror("bind");
        exit(3);
    }
    if(listen(sock,10)<0)
    {
        perror("listen");
        exit(4);
    }
    return sock;
}
fd_buff_p new_fd_buff(int _sock)
{
    fd_buff_p ret =(fd_buff_p)malloc(sizeof(fd_buff_t));
    ret->fd=_sock;
    memset(ret->buff,0,sizeof(ret->buff));
    return ret;
}
int main(int argc,char* argv[])
{
    if( argc!=3)
    {
        usage(argv[0]);
        exit(1);
    }
    int listen_sock=startup(argv[1],atoi(argv[2]));//封装一个函数去获取监听套接字和select和poll的套路一样，不详细说明
    int epollfds=epoll_create(MAX_EVENTS);//创建epoll模型，其实epoll的内部使用的数据结构是红黑树，还有一个链表存储准备好的文件描述符结构
    if(epollfds<0)
    {
        perror("epoll_create");
        exit(5);
    }
    struct epoll_event evt;
    evt.events=EPOLLIN;
    evt.data.ptr=new_fd_buff(listen_sock);
    epoll_ctl(epollfds,EPOLL_CTL_ADD,listen_sock,&evt);
    int nfds=0;
    int timeout=10000;
    while(1)
    {
        nfds=epoll_wait(epollfds,evts,MAX_EVENTS,timeout);
        if(nfds<0)
        {
            perror("epoll_wait");
            exit(6);
        }
        else if(nfds==0)
        {
            printf("timeout...\n");
        }
        else
        {
            int idx=0;
            for(;idx<nfds;++idx)
            {
                fd_buff_p fp=evts[idx].data.ptr;
                if(fp->fd==listen_sock && evts[idx].events & EPOLLIN)
                {
                    //fds_access()//准备接受外部链接
                    struct sockaddr_in client_addr;
                    socklen_t len=sizeof(client_addr);
                    int new_sock=accept(listen_sock,(struct sockaddr*)&client_addr,&len);
                    if(new_sock<0)
                    {
                        perror("accept");
                        exit(7);
                    }
                    printf("new client connected\n");
                    fflush(stdout);
                    struct epoll_event _event;
                    _event.events=EPOLLIN;
                    _event.data.ptr=new_fd_buff(new_sock);
                    epoll_ctl(epollfds,EPOLL_CTL_ADD,new_sock,&_event);
                }
                else if(fp->fd!=listen_sock)
                {
                    if(evts[idx].events& EPOLLIN)
                    {
                        int s=read(fp->fd,fp->buff,sizeof(fp->buff));
                        if(s>0)
                        {
                            fp->buff[s]=0;
                            printf("client:%s",fp->buff);
                            struct epoll_event new_event;
                            new_event.events=EPOLLOUT;
                            new_event.data.ptr=fp;
                            epoll_ctl(epollfds,EPOLL_CTL_MOD,fp->fd,&new_event);
                        }
                        if(s<=0)
                        {
                            printf("client quit\n");
                            close(fp->fd);
                            epoll_ctl(epollfds,EPOLL_CTL_DEL,fp->fd,NULL);
                            free(fp);
                        }
                    }
                    else if(evts[idx].events&EPOLLOUT)
                    {
                        const char* msg = "HTTP/1.1 200 OK\r\n\r\n<html><h1>Hello epoll!</h1></html>";
                        write(fp->fd,msg,strlen(msg));
                        close(fp->fd);
                        epoll_ctl(epollfds,EPOLL_CTL_DEL,fp->fd,NULL);
                        free(fp);
                    }
                }
            }
        }
    }

    return 0;
}


