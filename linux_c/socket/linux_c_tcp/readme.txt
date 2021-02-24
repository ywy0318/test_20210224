Linux-C TCP简单例子_Genven_Liang的博客-CSDN博客
https://blog.csdn.net/nanfeibuyi/article/details/88540144

Linux-C TCP简单例子
一、简述

       记-使用TCP协议通信的简单例子。

       例子1：一个客户端，一个服务端，客户端发送信息，服务端就收信息。

       例子2：使用多线程实现  服务器与客户端的双向通信。

       例子3：使用多路复用实现 服务器与客户端的双向通信 。

       例子4：多个客户端，一个服务器，客户端发送信息，服务端就收信息。

       例子5：使用多线程实现  服务器与多个客户端的双向通信。

       例子6：使用多路复用实现  服务器与多个客户端的双向通信。   

       代码打包：链接: https://pan.baidu.com/s/1x-JnmAm-4yqu54SoUqr20A 提取码: sxt5 

二、TCP基本操作。

     说明：  网络中有很多主机，我们使用IP地址标识主机的身份。一台主机有多个应用程序，我们使用端口号来标识应用。

       端口号范围0~65535,其中0~1024一般给系统使用，或者被知名软件所注册使用，所以为了避免冲突，开发时一般使用1025~65535。当主机某个端口收到消息，只有注册该端口(或者说绑定该端口)的应用才会收到消息。一般一个端口同时只能被一个应用所使用。

     补充：占用端口的程序异常退出之后，系统回收端口会有一定时间，此时再次绑定同一个端口会出现，端口被占用的情况。
	 
	     解决办法：方法1) 换一个端口    方法2）在代码中设置端口复用
		 
     基本操作步骤：

服务器端：创建tcp监听scoket，绑定地址，accept()接受客户端连接，返回一个与客户端通信的socket。接收数据使用read(),

                 发送数据用write();使用close()关闭通信。

客户端：创建tcp通信socket，直接向指定的服务器地址发起连接请求，连接成功后，接收数据使用read(),发送数据用write();

                使用close()关闭通信。
				
server端

//1 创建TCP通信socket
    int tcp_socket_fd = socket(AF_INET,SOCK_STREAM,0);//AF_INET:标识IPv4协议，IPv6是AF_INET6；SOCK_STREAM标识是TCP协议，UDP是SOCK_DGRAM;0表示默认
 
//2 绑定IP地址
	struct sockaddr_in local_addr = {0};
	local_addr.sin_family = AF_INET;//使用IPv4
	local_addr.sin_port = htons(port));//port是端口号，网络传输使用大端字节序，使用htons()进行转换。端口是int类型，范围0~65535
	local_addr.sin_addr.s_addr = INADDR_ANY;  //自动检测本地网卡设备并绑定IP
	
	bind(tcp_socket_fd,(struct sockaddr *)&local_addr,sizeof(local_addr));//绑定socket的IP地址
 
// 3 设置监听队列(最多可以连接多少个客户端)
    listen(tcp_socket_fd,5);
 
//4 等待，接受客户端的链接
    struct sockaddr_in client_addr = {0};//用来存放客户端的地址信息
	int len = sizeof(client_addr);//地址信息长度
	int new_socket = 0;//与客户端通信的socket
    new_socket  = accept(tcp_socket_fd,(struct sockaddr *)&client_addr,&len);//阻塞，等待客户端的连接
	
//5 关闭通信socket
    close(new_socket);
    close(tcp_socket_fd);

client端
//1 创建TCP通信socket
    int tcp_socket_fd = socket(AF_INET,SOCK_STREAM,0);
 
//2 连接服务器
    struct sockaddr_in server_addr = {0};//要连接服务器的地址
    server_addr.sin_family = AF_INET;//使用IPv4
	server_addr.sin_port = htons(port);//指定要连接服务器的某个端口， 端口是int类型，范围0~65535
	server_addr.sin_addr.s_addr = inet_addr(ip);//服务器的ip， ip是字符串类型，要进行相应的转换
	
	connect(tcp_socket_fd ,(struct sockaddr *)&server_addr,sizeof(server_addr));//发起连接服务器请求
	
//3 关闭通信socket
    close(tcp_socket_fd);
	
	
socket()函数
功能	创建通信端点(可以创建TCP通信端点、UDP通信端点)
头文件	#include <sys/types.h>          
#include <sys/socket.h>
原型	int socket(int domain, int type, int protocol);
参数	domain	通信协议簇（包含IPv4,IPv6）,详细请看<sys/socket.h>
type	
通信协议类型(包含TCP，UDP)，更多请查询手册： man socket

SOCK_STREAM：表示TCP

SOCK_DGRAM：表示UDP

 	protocol	指定与套接字一起使用的特定协议。通常，只有一个协议支持给定协议族中的特定套接字类型，在这种情况下协议可以指定为0.但是，可能存在许多协议，在这种情况下，必须在此指定特定协议方式。
返回值	
成功：返回一个文件描述符。

失败：返回-1，并设置errno

备注	详细请查看man手册：man 2 socket
 

bind()函数
功能	将IP地址信息绑定到socket
头文件	#include <sys/types.h>          
#include <sys/socket.h>
原型	int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
参数	sockfd	通信socket
addr	
要绑定的地址信息（包括IP地址，端口号）

通用地址结构体定义：

struct sockaddr {
               sa_family_t sa_family;//地址族, AF_xxx
               char        sa_data[14];//包括IP和端口号
}

新型的IP地址结构体：(查看新型的结构体信息： gedit  /usr/include/linux/in.h )

struct sockaddr_in {
  __kernel_sa_family_t    sin_family;    /*地址族，IP协议*/  默认：AF_INET
  __be16        sin_port;            /*端口号*/
  struct in_addr    sin_addr;        /*网络IP地址*/


  unsigned char        __pad //8位的预留接口
};

 	addrlen	地址信息大小
返回值	
成功：返回0。

失败：返回-1，并设置errno

备注	详细请查看man手册：man 2 bind
connect()函数
功能	发起连接请求
头文件	#include <sys/types.h>          
#include <sys/socket.h>
原型	int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
参数	sockfd	通信socket
addr	
要连接的服务器地址

 	addrlen	地址信息大小
返回值	
成功：返回0。

失败：返回-1，并设置errno

备注	详细请查看man手册：man 2 connect
 

htons()函数
功能	
将无符号短整型数（unsigned short integer）主机字节顺序转换为网络字节序

（h:host主机，to，n:net网络，s:short短整型）

头文件	#include <arpa/inet.h>
原型	uint16_t htons(uint16_t hostshort);
参数	hostshort	无符号短整型数
返回值	转换后的值
备注	
详细请查看man手册：man 3 htons

相关函数：

uint32_t htonl(uint32_t hostlong);

uint32_t ntohl(uint32_t netlong);

uint16_t ntohs(uint16_t netshort);

inet_addr()函数
功能	
将地址cp从IPv4数字和点符号(点分十进制形式)转换为 网络字节顺序的二进制形式。

(cp:char 类型的ip)

头文件	#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
原型	in_addr_t inet_addr(const char *cp);
参数	cp	ip地址 (如"192.168.21.155")
返回值	
成功：转换后的ip值

失败：INADDR_NONE  (-1)

备注	
手册中提到：

使用inet_addr()函数是有问题的，因为失败时返回的-1是有效地址（255.255.255.255），应该避免使用。可以使用inet_aton（），inet_pton（3）或getaddrinfo（3），它们提供了一种更清晰的方式来指示错误返回。

详细请查看man手册：man 3 inet_addr

相关函数：

int inet_aton(const char *cp, struct in_addr *inp);

in_addr_t inet_network(const char *cp);

char *inet_ntoa(struct in_addr in);

struct in_addr inet_makeaddr(in_addr_t net, in_addr_t host);

in_addr_t inet_lnaof(struct in_addr in);

in_addr_t inet_netof(struct in_addr in);

----------------------------------------------------多路复用-----------------------------

再某些情况下代替多线程，以便节省资源。

select)函数
功能	监视多个文件描述符，阻塞等待设定的时间，直到一个或多个文件描述符变为“准备好”，继续往下执行。
头文件	#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
原型	int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
参数	nfds	要监视的描述符集合中数值最大的描述符
readfds	读文件描述符集合，通常设置为要监视的描述符集合
writefds	写文件描述符集合，通常设置为NULL
exceptfds	其它文件描述符集合，通常设置为NULL
 	timeout	
超时时间(阻塞等待的时间，时间一到，就会往下执行。如果为NULL，会一直等到有描述符活跃为止)

时间结构体 (定义在<sys/time.h> 头文件中)

struct timeval {
               long    tv_sec;         /* 秒*/
               long    tv_usec;        /* 微秒*/
};

返回值	
-1：出错

0：超时

1：有活跃的文件描述符

备注	
详细请查看man手册：man 2 select

相关函数：

void FD_CLR(int fd, fd_set *set); //将某个描述符 从集合中清除出去
int  FD_ISSET(int fd, fd_set *set);//判断某个描述符是否 活跃
void FD_SET(int fd, fd_set *set);//往描述符监视集合 添加一个描述符
void FD_ZERO(fd_set *set);//清空描述符集合

注：select会更新 超时时间timeout，所以如果多次使用select需要重置timeout。

往下执行时，将修改每个文件描述符集以指示哪些文件描述符实际更改了状态。 因此，如果在循环中使用select（），则需要在每次调用之前对集合进行重新定义。