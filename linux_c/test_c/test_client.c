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


#if 0
struct sockaddr_in client_for_debug;

int sockfd_for_check=-1;

void  udp_init_for_client()
{   
     
    /* setup a socket，attention: must be SOCK_DGRAM */
    if ((sockfd_for_check = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
   
        perror("socket");
        exit(1);
    }
    bzero(&client_for_debug, sizeof(client_for_debug));
    client_for_debug.sin_family = AF_INET;
    client_for_debug.sin_port = htons(UDP_TEST_PORT_FOR_SEND);
    client_for_debug.sin_addr.s_addr = inet_addr(UDP_SERVER_IP);

    printf("%s(%d)--udp_init_for_client--success\n", __FILE__, __LINE__);    
}

int login(char * id_for_login,char * password_for_login)
{
	printf("%s(%d)-%s-%s\n",__FILE__,__LINE__,id_for_login,password_for_login);
	return 0;
}
#endif

//执行注册

int register()
{
	char id[20];
	char password[20];
	printf("please input your id:");
	gets(id);
	//发送给服务器去验证有没有用户名被占用;
	
	//验证失败,
	//验证成功,
	printf("please input your password:");
	gets(password);
	//发送给服务器,
	printf("please input your password again:");
	gets(password);
	//
	login(id,password);
	return 0;
}

char login_id[20];
char login_password[20];

int main()
{
	//启动之后,
	//询问是否注册,不注册，直接登陆
	//登陆以后//获取字符根据字符判断
	printf("welcom to tiandy QQ ^-^! ");
	printf("您是否注册新账号?注册:y;");
	if(getchar()=="y")
	{
	register();
		//执行注册
		//注册成功之后直接登陆
	}
	else
	{
		printf("please input your id:");
		gets(login_id);
		//发送给服务器,
		printf("please input your password:");
		gets(login_password);
		//执行登陆
		login(login_id,login_password);
		//登陆成功以后
		//登陆失败以后
	}
	
}



































































