Linux-C  UDP简单例子
一、简述

       记--使用UDP协议通信的简单例子。

        说明：  网络中有很多主机，我们使用IP地址标识主机的身份。一台主机有多个应用程序，我们使用端口号来标识应用。

        例子打包链接: https://pan.baidu.com/s/1-JlZpAd5A86Lkor03FbGZg 提取码: 6wrq 

       例子1：UDP单播，一方发送，一方接收。

       例子2：UDP单播，使用多线程实现 双方通信。

       例子3：UDP单播，使用多路复用实现 双方通信。

       例子4：组播，recv程序加入组播，当其他应用往该组发送组播消息时，recv程序将收到其他应用发给组的消息。

       例子5：广播，send往xxx端口发送广播消息，在同以网段中绑定xxx端口的recv程序就会收到广播消息。

二、例子

        直接创建UDP通信socket，然后使用sendto()函数向指定的地址发送数据。

        需要接受数据的话，要绑定IP端口地址。使用recvfrom()函数接收数据。
		三、相关函数：

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

sendto()函数
功能	发送消息给socket。(一般在UDP通信中使用，往指定的IP端口发送消息)
头文件	#include <sys/types.h>
#include <sys/socket.h>
原型	ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
参数	sockfd	通信的socket
buf	要发送的消息
len	要发送的消息长度.(一般为sizeof(buf) )
flags	
附加标志选项，UDP通信中为0即可。

MSG_CONFIRM：告诉对方收到之后回复确认。更多请查询man 手册：man 2 sendto

dest_addr	目的地址。(也就是接收方的地址信息)
 	addrlen	目的地址长度（一般为sizeof(dest_addr)）
返回值	转换后的值
备注	
详细请查看man手册：man 2 sendto

 

recvfrom()函数
功能	从socket接收消息。(一般在UDP通信中使用，注册某个IP端口，然后从此IP端口接收消息)
头文件	#include <sys/types.h>
#include <sys/socket.h>
原型	ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);
参数	sockfd	通信的socket，(已经绑定/注册 某个IP端口号的socket才可以从IP端口接收消息)
buf	用来存放接收到的消息
len	要接收的消息长度.(一般为sizeof(buf) )
flags	
附加标志选项，UDP通信中为0即可。更多请查询man 手册：man 2 sendto

src_addr	消息源地址。(用来保存发送方的地址信息)
 	addrlen	消息源地址长度（一般为sizeofr(src_addr)）
返回值	转换后的值
备注	
详细请查看man手册：man 2 sendto

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

 

setsockopt()函数
功能	在套接字上设置选项（设置socket套接字的相关操作、属性）
头文件	#include <sys/types.h>          
#include <sys/socket.h>
原型	int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
参数	sockfd	要设置的socket套接字
level	选项所属的级别(不同的级别有不同的选项-不同的操作)
optname	要设置的选项名称
optval	指向标志变量，将设置给optname所指定的选项。
optlen	optval指向的变量所占的字节数
返回值	
成功：返回0

出错：返回-1，并设置error

备注	
详细请查看man手册：man 2 setsockopt

示例：

    开启发送广播数据功能
    int on = 1; //1开启 0关闭
    setsockopt(socket_fd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));

      套接字设置选项：

Leve(级别)

optname(选项名)

说明

数据类型

 

 

 

 

 

 

 

 

 

 

 

 

 

 

SOL_SOCKET

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

SO_BROADCAST

允许发送广播数据报

int

SO_DEBUG

开启调试跟踪

int

SO_DONTROUTE

绕过外出路由表查询

int

SO_KEEPALIVE

周期性测试连接是否仍存活

int

SO_LINGER

若有数据待发送则延迟关闭

linger

SO_OOBINLINE

让接收到的带外数据继续在线留存

int

SO_RCVBUF

接收缓冲区大小

int

SO_SNDBUF

发送缓冲区大小

int

SO_RCVLOWAT

接收缓冲区低水位标记

int

SO_SNDLOWAT

发送缓冲区低水位标记

int

SO_RCVTIMEO

接收超时

timeval{}

SO_SNDTIMEO

发送超时

timeval{}

SO_REUSEADDR

允许重用本地地址

int

SO_REUSEPORT

允许重用本地端口

int

SO_TYPE

取得套接字类型

int

SO_USELOOPBACK

路由套接字取得所发送数据的副本

int

 

 

 

 

 

 

 

 

 

 

 

 

 

IPPROTO_IP

 

 

 

 

 

 

 

 

 

 

 

 

 

 

IP_HDRINCL

随数据包含的IP首部

int

IP_OPTIONS

IP首部选项

int

IP_RECVDSTADDR

返回目的IP地址

int

IP_RECVIF

返回接收接口索引

int

IP_TOS

服务类型和优先权

int

IP_TTL

存活时间

int

IP_MULTICAST_IF

指定外出接口

in_addr{}

IP_MULTICAST_TTL

指定外出TTL

u-char

IP_MULTICAST_LOOP

指定是否环回

u_char

IP_ADD_MEMBERSHIP

加入多播组

ip_mreq{}

IP_DROP_MEMBERSHIP

离开多播组

ip_mreq{}

IP_BLOCK_SOURCE

阻塞多组播

ip_mresource{}

IP_UNBLOCK_SOURCE

开通多组播

ip_mresource{}

IP_ADD_SOURCE_MEMBERSHIP

加入源特定多组播

ip_mresource{}

IP_DROP_SOURCE_MEMBERSHIP

离开源特定多组播

ip_mresource{}

IPPROTO_ICMPV6

ICMP6_FILTIER

指定待传递的ICMPv6

icmp6_filter{}

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

IPPROTO_IPV6

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

IPV6_CHECKSUM

用于原始套接字的校验和字段偏移

int

IPV6_DONTFRAG

丢弃大的分组而将其分片

int

IPV6_NEXTHOP

指定下一跳地址

sockaddr_int6{}

IPV6_PATHMTU

获取当前路径MTU

ip6_mtuinfo{}_

IPV6_RECVDSTOPTS

接收目的地选项

int

IPV6_RECVHOPLIMIT

接收单播跳限

int

IPV6_RECVHOPOPTS

接收步跳选项

int

IPV6_RECVPATHMTU

接收路径MTU

int

IPV6_RECVPKTINFO

接收分组信息

int

IPV6_CVRTHDR

接收源路径

int

IPV6_RECVTCLASS

接收流通类型

int

IPV6_UNICAST_HOPS

默认单播跳限

int

IPV6_USE_MIN_MTU

使用最小MTU

int

IPV6_V6ONLY

禁止v4兼容

int

IPV6_XXX

粘附性辅助数据

int

IPV6_ULTICAST_IF

指定外出接口

u_int

IPV6_MULTICAST_HOPS

指定外出跳限

int

IPV6_MULTICAST_LOOP

指定是否环回

u_nt

IPV6_JOIN_GROUP

加入多组播

ip6_mreq{}

IPV6_LEAVE_GROUP

离开多组播

ip6_mreq{}

 

 

 

 

 

IPPROTO_IP 或PROTO_IPV6

 

MCAST_JOIN_IF

加入多组播

group_req{}

MCAST_LEAVE_GROUP

离开多组播

group_source_req{}

MCAST_BLOCK_SOURCE

阻塞多播源

group_source_req{}

MCAST_UNBLOCK_SOURCE

开通多播源

group_source_req{}

MCAST_JOIN_SOURCE_GROUP

加入源特定多播组

group_source_req{}

MCAST_LEAVE_SOURCE_GROUP

离开源特定多播组

group_source_req{}

 

IPPROTO_TCP

TCP_MAXSEG

TCP最大分节大小

int

TCP_NODELAY

禁止Nagle算法

int

 

 

 

 

 

 

 

 

 

 

 

 

 

IPPROTO_SCTP

SCTP_ADAPTION_LAYER

适配层指示

sctp_setadaption{}

SCTP_ASSOCINFO

检查并设置关联信息

sctp_assocparams{}

SCTP_AUTOCLOSE

自动关闭操作

int

SCTP_DEFAULT_SEND_PARAM

默认发送参数

sctp_sndrcvinfo{}

SCTP_DISABLE_FRAGMENTS

SCTP分片

int

SCTP_EVENTS

感兴趣事件的通知

sctp_event_subscribe{}

SCTP_I_WANT_MAPPED_V4_ADDR

映射的v4地址

int

SCTP_INITMSG

默认的INIT参数

sctp_initmsg{}

SCTP_MAXBURST

最大猝发大小

int

SCTP_MAXSEG

最大分片大小

int

SCTP_NODELAY

禁止Nagle算法

int

SCTO_PEER_ADDR_PARAMS

对端地址参数

sctp_paddrparams{}

SCTP_PRIMARY_ADDR

主目的地址

sctp_setprim{}

SCTP_PTOINFO

RTO信息

sctp_rtoinfo{}

SCTP_SET_PEER_PRIMARY_ADDR

对端的主目的地址

sctp_setpeerprim{}

2、UDP组播 （涉及多台主机）
加入某一个组，那么有成员往该组发送信息时，所有组员都将收到信息。往某个组播IP地址的xxx端口发送信息。那么所有加入该组的主机 中注册xxx端口的应用都将收到。
//1 创建UDP通信socket
int udp_socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
 
//2 加入组播 
struct ip_mreq zu = {0};//存放组播地址信息
zu.imr_multiaddr.s_addr = inet_addr("224.10.10.2");  //设置组播地址224.0.0.0~239.255.255.255
zu.imr_interface.s_addr = inet_addr("0.0.0.0");  	
setsockopt(udp_socket_fd, IPPROTO_IP,I P_ADD_MEMBERSHIP, &zu, sizeof(zu);
	
//3 绑定地址 (可以通过绑定的IP端口接收其它应用发来的消息)
struct sockaddr_in  local_addr ={0};
local_addr.sin_family  = AF_INET; //使用IPv4协议
local_addr.sin_port	= htons(port));   //网络通信都使用大端格式
local_addr.sin_addr.s_addr =  inet_addr("0.0.0.0");  //32位的整形   //注意：Linux下设置组播的时候绑定地址只能绑定0.0.0.0地址否则会接收不到数据
bind(udp_socket_fd,(struct sockaddr*)&local_addr,sizeof(local_addr));
	
//4 收发数据
char buf[1024] = {0};//数据缓区
 
//接收数据 （可以收到组播的消息，也可以收到绑定端口的消息）
struct sockaddr_in  src_addr ={0};  //定义一个缓冲区 存放对方的IP地址信息
int len = sizeof(src_addr);//地址的大小
recvfrom(udp_socket_fd, buf,sizeof(buf), 0, (struct sockaddr *)&src_addr,&len);
 
//发送数据 (可以往组播地址发送，也可以往制定的IP端口发送，组播地址就是特殊的IP地址)
sendto(udp_socket_fd, "hello", strlen("hello"), 0, (struct sockaddr *)&zu_addr, sizeof(zu_addr)); 
 
//其中组播地址
struct sockaddr_in zu_addr;
addr.sin_family = AF_INET;
addr.sin_port = htons(8888);
addr.sin_addr.s_addr = inet_addr("224.10.10.2");  //设置组播地址 D类地址

3、UDP广播 （涉及多台主机）

往某个IP网段的xxx端口发送信息。那么在本网段的所有主机中注册xxx端口的应用都将收到(包括自己)。

//1 创建UDP通信socket
int udp_socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
 
//2 开启发送广播数据功能
int on = 1; //1开启 0关闭
int ret = setsockopt(udp_socket_fd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));
 
//3 向广播地址发送广播数据
sendto(udp_socket_fd, "hello", strlen("hello"), 0, (struct sockaddr *)&bro_addr,sizeof(bro_addr)); 
 
//其中bro_addr为广播地址
struct sockaddr_in bro_addr = {0};
bro_addr.sin_family = AF_INET;//IPv4协议
bro_addr.sin_port = htons(8888);//设置广播端口
bro_addr.sin_addr.s_addr = inet_addr("192.168.13.255");  //设置本网段广播地址，192.168.xxx.255
