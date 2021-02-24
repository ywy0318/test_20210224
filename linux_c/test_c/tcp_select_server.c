//将fork多进程并发服务器端代码改写单进程多连接池select模型
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
 
#define ERR_EXIT(m) \
        do \
        { \
                perror(m); \
                exit(EXIT_FAILURE); \
        } while(0)
 
ssize_t readn(int fd, void *buf, size_t count)
{
    size_t nleft = count;
    ssize_t nread;
    char *bufp = (char*)buf;
 
    while (nleft > 0)
    {
        if ((nread = read(fd, bufp, nleft)) < 0)
        {
            if (errno == EINTR)
                continue;
            return -1;
        }
        else if (nread == 0)
            return count - nleft;
 
        bufp += nread;
        nleft -= nread;
    }
 
    return count;
}
 
ssize_t writen(int fd, const void *buf, size_t count)
{
    size_t nleft = count;
    ssize_t nwritten;
    char *bufp = (char*)buf;
 
    while (nleft > 0)
    {
        if ((nwritten = write(fd, bufp, nleft)) < 0)
        {
            if (errno == EINTR)
                continue;
            return -1;
        }
        else if (nwritten == 0)
            continue;
 
        bufp += nwritten;
        nleft -= nwritten;
    }
 
    return count;
}
 
ssize_t recv_peek(int sockfd, void *buf, size_t len)
{
    while (1)
    {
        int ret = recv(sockfd, buf, len, MSG_PEEK);
        if (ret == -1 && errno == EINTR)
            continue;
        return ret;
    }
}
 
ssize_t readline(int sockfd, void *buf, size_t maxline)
{
    int ret;
    int nread;
    char *bufp = buf;
    int nleft = maxline;
    while (1)
    {
        ret = recv_peek(sockfd, bufp, nleft);
        if (ret < 0)
            return ret;
        else if (ret == 0)
            return ret;
 
        nread = ret;
        int i;
        for (i=0; i<nread; i++)
        {
            if (bufp[i] == '\n')
            {
                ret = readn(sockfd, bufp, i+1);
                if (ret != i+1)
                    exit(EXIT_FAILURE);
 
                return ret;
            }
        }
 
        if (nread > nleft)
            exit(EXIT_FAILURE);
 
        nleft -= nread;
        ret = readn(sockfd, bufp, nread);
        if (ret != nread)
            exit(EXIT_FAILURE);
 
        bufp += nread;
    }
 
    return -1;
}
 
void echo_srv(int conn)
{
    char recvbuf[1024];
    while (1)
    {
        memset(recvbuf, 0, sizeof(recvbuf));
        int ret = readline(conn, recvbuf, 1024);
        if (ret == -1)
            ERR_EXIT("readline");
        if (ret == 0)
        {
            printf("client close\n");
            break;
        }
 
        fputs(recvbuf, stdout);
        writen(conn, recvbuf, strlen(recvbuf));
    }
}
int main(int argc,char *argv[])
{
    char buf[1024]= {};
    signal(SIGPIPE, SIG_IGN);
    int listenfd;
    if ((listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        ERR_EXIT("socket");
    struct sockaddr_in serv;
    bzero(&serv,sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8001);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    int on = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
        ERR_EXIT("setsockopt");
 
    if (bind(listenfd, (struct sockaddr*)&serv, sizeof(serv)) < 0)
        ERR_EXIT("bind");
    if (listen(listenfd, SOMAXCONN) < 0)
        ERR_EXIT("listen");
    struct sockaddr_in cli;
    socklen_t len=sizeof(cli);
    int connfd,i,maxi=0,maxfd=listenfd,client[FD_SETSIZE],nready;
    for(i=0; i<FD_SETSIZE; i++)
    {
        client[i]=-1;
    }
    printf("FD_SETSIZE max is %d\n",FD_SETSIZE);
    fd_set rset,allset;
    FD_ZERO(&rset);
    FD_ZERO(&allset);
    FD_SET(listenfd,&allset);
    for(;;)
    {
        rset=allset;
        nready=select(maxfd+1,&rset,NULL,NULL,NULL);
        if(nready==-1)
        {
            printf("select error!\n");
        }
        if(nready==0)
            continue;
        if(FD_ISSET(listenfd,&rset))
        {
            connfd=accept(listenfd, (struct sockaddr*)&cli,&len);
            if(connfd==-1)
            {
                printf("connfd error!\n");
            }
            for(i=0; i<FD_SETSIZE; i++)
            {
                if(client[i]==-1)
                {
                    client[i]=connfd;
                    if(i>maxi)
                        maxi=i;
                    break;
                }
            }
            if(i==FD_SETSIZE)
                printf("no more connect!\n");
            FD_SET(connfd,&allset);
            if(connfd>maxfd)
                maxfd=connfd;
            if(--nready<=0)
                continue;
        }
        for(i=0; i<=maxi; i++)
        {
            if(client[i]==-1)
                continue;
            if(FD_ISSET(client[i],&rset))
            {
                memset(buf,0,sizeof(buf));
                int ret=readline(client[i],buf,sizeof(buf));
                if(ret==-1)
                    printf("read error!\n");
                if(ret==0)
                {
                    printf("client closed!\n");
                    client[i]=-1;
                    FD_CLR(client[i],&allset);
                    close(client[i]);
                }
                fputs(buf,stdout);
                writen(client[i],buf,strlen(buf));
                if(--nready<=0)
                    break;
            }
        }
    }
    return 0;
}