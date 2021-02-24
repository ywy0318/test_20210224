//用select对TCP客户端代码进行修改
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/select.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<signal.h>
#include <errno.h>
ssize_t readn(int fd, void *buf, size_t count)
{
    size_t nleft = count;
    ssize_t nread;
    char *bufp = (char*) buf;
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
    char *bufp = (char*) buf;
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
        for (i = 0; i < nread; i++)
        {
            if (bufp[i] == '\n')
            {
                ret = readn(sockfd, bufp, i + 1);
                if (ret != i + 1)
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
int main(int argc,char *argv[])
{
    signal(SIGPIPE,SIG_IGN);
    fd_set rset;
    FD_ZERO(&rset);
    struct sockaddr_in user;
    user.sin_family = AF_INET;
    user.sin_port = htons(8001);
    user.sin_addr.s_addr = inet_addr("127.0.0.1");
    int sockfd,stdinfd,maxfd;
    char sendbuf[1024]= {0},revbuf[1024]= {0};
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1)
    {
        printf("socket failed!\n");
        exit(0);
    }
    stdinfd=fileno(stdin);
    maxfd = sockfd+1;
    if ( connect(sockfd, (struct sockaddr*) (&user), sizeof(user)) < 0)
    {
        perror("connect failed!\n");
        exit(0);
    }
    for(;;)
    {
        FD_SET(stdinfd,&rset);
        FD_SET(sockfd,&rset);
        int ret=select(maxfd,&rset,NULL,NULL,NULL);
        if(ret==-1)
            printf("select failed!\n");
        if(ret==0)
            continue;
        if(FD_ISSET(sockfd,&rset))
        {
            int val=readline(sockfd,revbuf,sizeof(revbuf));
            if(val==0)
                break;
            printf("client revmsg:");
            fputs(revbuf,stdout);
            memset(revbuf,0,sizeof(revbuf));
        }
        if(FD_ISSET(stdinfd,&rset))
        {
            if(fgets(sendbuf,sizeof(sendbuf),stdin)==NULL)
                break;
            writen(sockfd,sendbuf,strlen(sendbuf));
            memset(sendbuf,0,sizeof(sendbuf));
        }
    }
    close(sockfd);
    return 0;
}