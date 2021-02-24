#include "pthread.h"
#include "sys/types.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/types.h"
#include "fcntl.h"
#include "signal.h"
#include "sys/stat.h"
#include "sys/termios.h"
#include "sys/ioctl.h"
#include "sys/msg.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include "sys/soundcard.h"
#include "dirent.h"
#include <net/if.h>
#include <memory.h>
#include <malloc.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <linux/rtc.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>

#include <netdb.h>                     //gethostbyname();

//int sender;
//网络初始化
//创建处理登陆信息线程--更新在线用户列表
//创建转发消息线程
//创建注册处理线程 
//刷新在线用户列表---处理显示类信息
//会话切换--如果客户端切到当前正在进行的会话，直接把消息转过去,如果不在的话,就谈一个提示
/*
typedef struct
{
	char loginid[20];    
	char password[20];       
}users_t;

typedef struct
{
    int r_sockfd;
  
    char content[500];
}hdr_t;

typedef struct mes 
{
	char command[8];
	char content[32];
}Message;
static pthread_t s_receive_data_thread_id;


void *receive_data_thread( void *param )
{
    int len = 0;
    unsigned char buf[2000];
    
    while ( 1 )
    {
        memset(buf, 0, sizeof(buf));
#ifdef SHENZHEN9
        socklen_t socklen = 0;
        struct sockaddr_in remoteaddr;
        memset(&remoteaddr, 0, socklen);
        remoteaddr.sin_family = AF_INET;
        len = recvfrom(s_receive_fd, buf, sizeof(buf), 0, (struct sockaddr *)&remoteaddr, &socklen);
#else
        len = local_socket_read(s_receive_fd, buf, sizeof(buf));
#endif
        
        if (len > 0)
        {
            prc_receive_data_matrix((PIS_DATA_STRU *)buf);
        }
        else
        {
            usleep(1000);
        }
        
       
        if ( s_ut_while_break_status == 1 )
        {
            s_ut_while_break_status = 0;
            break;
        }
    }
    
    return NULL;
}



void main()
{
	
	pthread_create(&s_receive_data_thread_id, NULL, receive_data_thread, NULL);
	
}

*/
typedef struct
{
	char loginid[20];    /*用户名*/
	char password[20];       /*密码*/
	char *p;//指针由于保存接收到的而对方未在线的时候的消息的起始地址
}users_t;

typedef struct
{
    int r_sockfd;
  //  int sender;
    char content[500];
}hdr_t;

typedef struct mes 
{
	char command[8];
	char content[32];
}Message;
static pthread_t s_receive_data_thread_id;


void *receive_data_thread( void *param )
{
    int len = 0;
    unsigned char buf[2000];
    
    while ( 1 )
    {
        memset(buf, 0, sizeof(buf));
#ifdef SHENZHEN9
        socklen_t socklen = 0;
        struct sockaddr_in remoteaddr;
        memset(&remoteaddr, 0, socklen);
        remoteaddr.sin_family = AF_INET;
        len = recvfrom(s_receive_fd, buf, sizeof(buf), 0, (struct sockaddr *)&remoteaddr, &socklen);
#else
        len = local_socket_read(s_receive_fd, buf, sizeof(buf));
#endif
        
        if (len > 0)
        {
            prc_receive_data_matrix((PIS_DATA_STRU *)buf);
        }
        else
        {
            usleep(1000);
        }
        
        //只是为路单元测试时提高覆盖率
        if ( s_ut_while_break_status == 1 )
        {
            s_ut_while_break_status = 0;
            break;
        }
    }
    
    return NULL;
}



void main()
{
	//网络初始化
	
	//创建处理登陆信息线程--更新在线用户列表
	//初始化一个发送数据的线程
	//一个接受数据的线程,接受的时候同时可以发送
	//会话切换--如果客户端切到当前正在进行的会话，直接把消息转过去,如果不在的话,就谈一个提示
	
	//创建注册处理线程 
	
	//刷新在线用户列表---处理显示类信息
	

	//文件传输
	
	pthread_create(&s_receive_data_thread_id, NULL, receive_data_thread, NULL);


	//00:0C:29:75:A4:11--Ubuntu16.04
	
	//00:0C:29:5E:04:E3--Ubuntu1604_64
	
}













