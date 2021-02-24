#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdio.h>
#include "udsSocket.h"
 
#define RECV_SIZE_MAX	1024
 
enum e_ErrNo
{
	RETERR,
	RETFAIL,
	RETOK,
	RETCONTINUE,
	RETNUL
};
 
struct sockaddr_un gSrcAddr = {0};
struct sockaddr_un gDestAddr = {0};
socklen_t gSockLen = 0;
int gSocketFd = 0;
 
//绑定socket
int udsBind(const char* _path, int _len)
{
	int ret;
	int flag;
	char path[32];
 
	if (_len > sizeof(path))
	{
	    perror( "path is too long!" );
	    return -1;
	}
 
	strncpy(path, _path, _len);
	
	if ((gSocketFd = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0)
	{
		perror( "socket error!" );
		return -1;
	}
 
	unlink(path);
	//printf("gSocketFd:%d,\n",gSocketFd);
 
	memset( &gSrcAddr, 0, sizeof(gSrcAddr));
	gSrcAddr.sun_family = AF_UNIX;
	strncpy( gSrcAddr.sun_path,  path, strlen(path));
 
	gSockLen = strlen( gSrcAddr.sun_path ) + sizeof( gSrcAddr.sun_family);
	
	ret = bind(gSocketFd,(struct sockaddr*)&gSrcAddr, gSockLen);
	if(ret < 0)
	{
		perror("bind err!\n");
		return -1;
	}
 
	//设置为非阻塞
#ifdef NONBLOCK
	flag = fcntl(gSocketFd, F_GETFL, 0);
	if(flag < 0)
	{
		perror("fcntl fail!\n");
		return -1;
	}
	flag |= O_NONBLOCK;//非阻塞，没有读到消息立即返回不等待
	if (fcntl(gSocketFd, F_SETFL, flag) < 0)
	{
		perror("fcntl fail!\n");
		return -1;
	}
#endif
	
	chmod(path, S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP|S_IROTH|S_IWOTH|S_IXOTH);
 
    return gSocketFd;
}
 
 
//发送socket消息
int udsSendMessage(int _socketFd, char* _data, int _len, const char * _destAddr)
{
	int ret;	
	struct sockaddr_un destAddr;
	if(gSocketFd>0)
	{
		memset( &destAddr, 0, sizeof( destAddr ) );
		destAddr.sun_family = AF_UNIX;
		strncpy(destAddr.sun_path, _destAddr, strlen(_destAddr));
		
		socklen_t sockLen = strlen(destAddr.sun_path) + sizeof(destAddr.sun_family);
		
		ret = sendto( gSocketFd, _data, _len, 0, (struct sockaddr *)&destAddr, sockLen);
		if( ret < 0 )
		{
			perror( "write socket error!" );
			return RETERR;
		}
	}	
 
	return ret;
}
 
 
//接收socket消息
int udsRecv(int _socketFd, char *sBuf) 
{
	int err, ret = 0;
	char tmpbuf[RECV_SIZE_MAX];
	
	if(_socketFd>0)
	{
		memset(tmpbuf, 0, RECV_SIZE_MAX); 
		socklen_t sockLen = strlen(gDestAddr.sun_path) + sizeof(gDestAddr.sun_family);
		
		errno = 0;
		ret = recvfrom(_socketFd, tmpbuf, RECV_SIZE_MAX, 0, (struct sockaddr*)&gDestAddr, &sockLen);
		printf("sockLen=%d,\n", sockLen);
		err = errno;
 
		if (ret == -1 && err != EAGAIN && err != EWOULDBLOCK)
		{	
			perror("recv failed.\n");
			return RETERR;
		}
		else if (ret == 0 || (ret==-1 && err==EAGAIN))
		{
			return RETCONTINUE;
		}
		
		memcpy(sBuf, tmpbuf, ret);
	}	
	
	return ret;
}