//将fork多进程并发服务器端代码改写单进程多连接池select模型
//20190723
//ubuntu1602_client ip:192.168.10.204
//ubuntu1602_server ip:192.168.10.230
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include "pthread.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/epoll.h>
#include<time.h>
#define ERR_EXIT(m) \
        do \
        { \
                perror(m); \
                exit(EXIT_FAILURE); \
        } while(0)
#define IPADDRESS "192.168.10.230"
//#define IPADDRESS "127.0.0.1"
#define PORT 8888
#define MAXSIZE 1024
#define LISTENQ 5
#define FDSIZE 1000
#define EPOLLEVENTS 100

struct user
{
	int num_qq;//相当于QQ号码
	char loginid[20];    /*用户名*/
	char password[20];       /*密码*/
	int r_sockfd;//连接的socket套接字
	int broad_id_count;
	int broad_id[10];//多人会话id号--从900开始;三位数字999结束;每个人最多加10多人会话,
	unsigned char is_login;//判断是否登陆
	int black_count;//黑名单数目
	int friend_count;//好友数目
	int friend[100];//好友列表	
	int black_list[100];//黑名单列表
	//只能保存两人对话的消息
	char *p[20];//指针数组,用于保存接收到的而对方未在线的时候的消息的起始地址
};

struct broad
{
	int broad_id;//多人会话的账号
	int user_list[20];//多人会话中的成员
};

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
static pthread_t s_station_broadcast_circle_thread_id;
static pthread_t s_thread_id;

static char file[100];
char file_1[100];
char file_2[100];
char file_3[100];
char file_4[3];
char str_for_search_name[10];
int sockfd_for_file=-1;
char *cmd[20]={};



char cmd_for_4_server[10];

char *cmd_server_1[20]=
{
	"help","show","broad_show","login","send",
	"add","adb_broad","ftp","sdb_","set_black_list",
	"register"
};
char *cmd_server[20]=
{
	"help","show","bdsh","logn","send",// 0 1 2 3 4
	"addf","adbd","ftpd","sdbd","stbl",// 5 6 7 8 9
	"rgst","shbf"						//10 11
};


char *cmd_for_help[20]=
{
	"help------------------------------------------------------give all command",
	"show-------------------------------------------------show your friend list",	
	"broad_show---------------------------------------------show your broad list",
	"login [id] [password]------------------------------------------------login",
	"send [friend_id] [message]------------------------send your friend message",
	"add [friend_id]-----------------------------------------------add a friend",
	"adb_broad [friend_id] [friend_id]-----add some friend to broad(at most 10)",
	"ftp [frined_id] [file_name]-------------------transform your friend a file",
	"sdbd [broad_id]-----------------send message for all friend in broad",
	"set_black_list [friend_id]------------------------set someone in black list ",
	"register [id] [password]----------------------------------register a newer"	
};

char *info_of_staff[20]=
{
	"1 aaaaa aaaaaa ",
	"2 bbbbb bbbbbb ",
	"3 ccccc cccccc ",
	"4 ddddd dddddd ",
	"5 eeeee eeeeee ",
	"6 fffff ffffff ",
	"7 ggggg gggggg",
	"8 hhhhh hhhhhh",
	"9 iiiii iiiiii",
	"10 kkkkk kkkkk",
};

char *info_staff[500]=
{
    	"aaaaa",
		"bbbbb",
		"ccccc",
		"ddddd",
		"eeeee",
		"fffff",
		"ggggg",
		"hhhhh",
		"iiiii",
		"kkkkk" 	
};


char *staff_info[20][3]=
{
	{"1","aaaaa","aaaaaa"},
	{"2","bbbbb","bbbbbb"},
	
	{"3","ccccc","cccccc"},
	{"4","ddddd","dddddd"},
	
	{"5","eeeee","eeeeee"},
	{"6","fffff","ffffff"},
	
	{"7","ggggg","gggggg"},
	{"8","hhhhh","hhhhhh"},
	
	{"9","kkkkk","kkkkk"},
	{"10","mmmmm","mmmmmm"},
	NULL
};

char staff_infomation[20][20]=
{
	"1 aaaaa aaaaaa ",
	"2 bbbbb bbbbbb ",
	"3 ccccc cccccc ",
	"4 ddddd dddddd ",
	"5 eeeee eeeeee ",
	"6 fffff ffffff ",
	"7 ggggg gggggg",
	"8 hhhhh hhhhhh",
	"9 iiiii iiiiii",
	"10 kkkkk kkkkk",
};
static char sub_str_3[10];
char str_for_read[1000];
struct user staff[500];//员工列表
struct broad broad_array[100];//最多100个多人会话列表
int r_socked_for_broad[20];
const unsigned char allchar[63] = "0123456789ASDFGHJKLQWERTYUIOPZXCVBNMasdfghjklqwertyuiopzxcvbnm";
int space_count=0;
static int num_for_register=0;
static int num_for_online=0;
int epollfd;
int fd_for_client=-1;//客户端
int fd_for_send_message=-1;//要转发给其他人的消息
int index_in_staff=-1;

char num_to_char_server[3];
int char_to_num_server=0;
static int count_for_cmd=-1;
char buf_for_login_success[100]="login success";
char buf_for_login_failed[100]="user id or password error,login failed";
//char buf_for_login_success[100]="login success";
char buf_for_register_success[100]="success";
char buf_for_register_failed[100]="user id already,register failed";
char buf_for_send_failed[100]="your friend is not online,message send failed";

char message_server_1[4];//命令字
char message_server_2[10];//目标id
char message_server_3[100];//源id或者文件名
char message_server_4[1000];//具体的消息内容或者源id
char message_server_5[1000];//文件内容
int flag_for_message_or_file_server=0;//0-message   1--file

char buf_for_read_server[1024];
static pthread_t s_receive_data_thread_id_s;


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



/*
char型数字转换为int类型
转换方法 a[i]-'0'

int类型转换为char类型
转换方法a[i]+'0'
*/
void test_int_to_char_server(int num)
{
	int a=0,b=0,c=0;
	a=num/100;
	b=num%100/10;
	c=num%10;	
	char_to_num_server=num;
	num_to_char_server[0]=a+'0';
	num_to_char_server[1]=b+'0';
	num_to_char_server[2]=c+'0';
	printf("%s(%d)%c %c %c %d\n",__FILE__,__LINE__,num_to_char_server[0],num_to_char_server[1],num_to_char_server[2],char_to_num_server);
}

void test_char_to_int_server()
{
	int a=0;
	int b=0;
	int c=0;
	a=num_to_char_server[0]-'0';
	b=num_to_char_server[1]-'0';
	c=num_to_char_server[2]-'0';
	char_to_num_server=a*100+b*10+c;
	printf("%s(%d)%c %c %c %d\n",__FILE__,__LINE__,num_to_char_server[0],num_to_char_server[1],num_to_char_server[2],char_to_num_server);
}


void test_write_info_to_txt(int num,char *str1,char *str_2)
{
	char string[100];
	FILE *fp=fopen("./test.txt","r+");
	fseek(fp, 0, SEEK_END);
	sprintf(string,"%d", num);
	strcat(string," ");
	strcat(string,str1);
	strcat(string," ");
	strcat(string,str_2);
	strcat(string,"\n");
	fputs(string, fp);
	fclose(fp);	
}
int search(char *string_for_search)
{
	//printf("111\n");
	index_in_staff=-1;
	for(int i=0;i<num_for_register;i++)
	{
		struct user *pst=&(staff[i]);
		if(strcmp(pst->loginid,string_for_search)==0)
		{
			index_in_staff=i;
			break;
		}
	}
	return index_in_staff;
}
int search_num_qq_for_loginid(int num)
{	int i=0;
	//printf("%s(%d) %s \n",__FILE__,__LINE__,(staff[10].loginid));
	for(i=0;i<(num_for_register);i++)
	{
		//printf("%s(%d) (%d)(%d)\n",__FILE__,__LINE__,i,num);
		
		if((i+1)==num)
		{
			//struct user *pst=&(staff[i]);
			//return pst->loginid;
			strncpy(str_for_search_name,(staff[i].loginid),strlen(staff[i].loginid));
			//return (staff[i].loginid);
			return 1;
		}
	}
	return 0;	
}
int search_fd(int fd)
{
	//printf("111\n");
	index_in_staff=-1;
	for(int i=0;i<num_for_online;i++)
	{
		struct user *pst=&(staff[i]);
		//printf("%d-%d-%d\n",num_for_online,fd,pst->r_sockfd);
		if(fd==pst->r_sockfd)
		//if(strcmp(pst->loginid,string_for_search)==0)
		{
			index_in_staff=i;
			break;
		}
		
	}
	//printf("index_in_staff=%d\n",index_in_staff);
	return index_in_staff;
}


void generate_string(char *string,unsigned int n)
{
	int i = 0;
	int ret;
	usleep(1000*1000);
	srand(time(0));
	for (i = 0; i < n; i++)
	{
		ret = rand() % 63;
		*string = allchar[ret];
		//printf("%c\n", allchar[ret]);
		string++;
	}
	*string='\0';
}
/*
char message_server_1[4];//命令字
char message_server_2[10];//目标id
char message_server_3[100];//源id或者文件名
char message_server_4[1000];//具体的消息内容或者源id
char message_server_5[1000];//文件内容
int flag_for_message_or_file_server=0;//0-message   1--file
*/

void cut_string_for_message_file_recv_server(char *string,int flag)
{
	int i=0;
	char *p=string;
	while((*string)!=' ')
	{
		message_server_1[i]=*string;//命令字
		i++;
		string++;
	}
	string++;
	i=0;
	while((*string)!=' ')
	{
		message_server_2[i]=*string;//目标id
		i++;
		string++;
	}
	string++;
	i=0;
	while((*string)!=' ')
	{
		message_server_3[i]=*string;//消息报文或者是文件名
		i++;
		string++;
	}
	string++;
	i=0;

	if(flag)
	{
		while((*string)!=' ')
		{
			message_server_4[i]=*string;//源id
			i++;
			string++;
		}
		string++;
		i=0;
		while((*string)!='\0')
		{
			message_server_5[i]=*string;//文件内容
			i++;
			string++;
		}
	}
	else
	{
		while((*string)!='\0')
		{
			message_server_4[i]=*string;//消息报文
			i++;
			string++;
		}
	}
		
}


//获取控制台输入的前四个字符
void cutString_server(char* string,int num)
{
	char *p_start = string;	    
    char newString[32];
	if(num>strlen(string))
	{
		printf("%s(%d)string is too short\n",__FILE__,__LINE__);
	}
	else 
	{
		strncpy(cmd_for_4_server, string, num);	
	}	
}

void substr(char *str1)
{
	int i=0;
	char *p=str1;
	while(i<3)
	{
		sub_str_3[i]=*str1;
		i++;
		str1++;
	}
	printf("%s\n",sub_str_3);
}

//ftp aaaaa test.txt 009 xxxxxxx
//切四次,
void cut_string_for_file(char *string)
{
	int i=0;
	char *p=string;
	while((*string)!=' ')
	{
		file_1[i]=*string;
		i++;
		string++;
	}
	string++;
	i=0;
	while((*string)!=' ')
	{
		file_2[i]=*string;
		i++;
		string++;
	}
	string++;
	i=0;
	while((*string)!=' ')
	{
		file_3[i]=*string;
		i++;
		string++;
	}
	string++;
	i=0;
	//获取长度
	while((*string)!=' ')
	{
		file_4[i]=*string;
		i++;
		string++;
	}	
}


void test_strtok(char * str)
{	
	int i=0;
	space_count=0;
	//printf("%s\n",str);
	char *token=strtok(str," ");
	
	if(token!=NULL)
	{
		//printf("%s\t",token);	
	}
	printf("%s(%d)\n",__FILE__,__LINE__);
	while(token!=NULL)
	{
		printf("%s\t",token);
		cmd[space_count]=token;
		space_count+=1;		
		token=strtok(NULL," ");
	}
	printf("\n");
#if 0
	printf("\n");
	printf("space_count=%d\n",space_count);	
	for (i = 0; i < space_count; i++)
	{
      printf("%s\n", cmd[i]);
    }  
	printf("\n");
#endif
}


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
 
ssize_t readline(int sockfd, char *buf, size_t maxline)
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
            //printf("client close\n");
			printf("%s(%d)-client close\n",__FILE__,__LINE__);
			break;
        }
 
        fputs(recvbuf, stdout);
        writen(conn, recvbuf, strlen(recvbuf));
    }
}

int test_select_server()
{
	char buf[1024]= {};
	//char buff[20]="hello\n";
	
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
				//strcat(buf,"$^-^$\n");
				//fputs(buff,stdout);
               fputs(buf,stdout);
				//printf("%s",buf);
				//printf("%s\n",buff);
				//strcat(buf,"$^-^$");
			    //printf("%s",buf);
                writen(client[i],buf,strlen(buf));
				//writen(client[i],buf,strlen(buf));
                if(--nready<=0)
                    break;
				memset(buf,0,sizeof(buf));
            }
        }
    }
    return 0;
}


void test_struct()
{
	struct user user_s[10];
	 char buf[10]="sss";
	 struct user *pst=&(user_s[0]);
	 pst->num_qq=10;
	 strcpy(pst->loginid,buf);
	 //pst->loginid="sss";
	 printf("%d\n",user_s[0].num_qq);
	 printf("%s\n",user_s[0].loginid);
	 //user_s[0].num=10;
	 //printf("%d\n",user_s[0].num);
}

/*

char *str_int="892";
int int_val=atoi(str_int);
printf("字符串转整型：%d\n",int_val);

*/
//初始化n个注册的账号密码
void init_staff_struct(int n)
{
	int i=0;
	char str[62];//
	char string[100];
	
	FILE *fp=fopen("./test.txt","r+");
	/*	
	while((fgets(str_for_read,100,fp))!=NULL)
	{
		if(strlen(str_for_read)!=0)
		{
			printf("%s\n",str_for_read);
		}
	}
	*/
	fseek(fp, 0, SEEK_SET);
	//fseek(fp, 0, SEEK_END);
	for(i=0;i<n;i++)
	{
		struct user *pst=&(staff[i]);
		pst->num_qq=(i+1);
		//printf("i=%d,%d-",i,pst->num_qq);
		sprintf(string,"%d", pst->num_qq);
		//strcat(string,pst->num_qq);
		strcat(string," ");	
		generate_string(str,5);
		strcpy(pst->loginid,str);
		strcat(string,pst->loginid);
		strcat(string," ");
		memset(str,0,62);
		
		//printf("%s-",pst->loginid);
		generate_string(str,6);
		strcpy(pst->password,str);
		strcat(string,pst->password);
		strcat(string,"\n");
		//printf("%s\n",pst->password);
		//printf("string=%s",string);
		fputs(string, fp);	 
	}			
	for(i=0;i<n;i++)
	{
		printf("%d-%s-%s\n",staff[i].num_qq,staff[i].loginid,staff[i].password);
	}

	
	fclose(fp);
	return ;
}
void test_read_staff_infomation()
{
	int i=0;
	//while((info_of_staff[num_for_register])!=NULL)
	while((staff_infomation[0][i])!='\0')
	{
		printf("i=%d-%c\n",i,staff_infomation[0][i]);
		i++;
	}
	i=0;
	printf("\n111\n");
	while((staff_infomation[9][i])!='\0')
	{
		printf("i=%d-%c\n",i,staff_infomation[9][i]);
		i++;
	}
	//printf()
	
}

void init_info_staff()
{
	int i=0;
	int j=0;
	num_for_register=0;
	while((info_staff[num_for_register])!=NULL)
	{
		struct user *pst=&(staff[num_for_register]);
		pst->num_qq=(num_for_register+1);
		strcpy(pst->loginid,info_staff[num_for_register]);			
		strcpy(pst->password,info_staff[num_for_register]);
		pst->is_login=0;
		num_for_register++;
	}
	staff[0].friend_count=5;
	staff[1].friend_count=5;
	staff[2].friend_count=5;
	staff[3].friend_count=5;
	staff[4].friend_count=5;
	
	for(j=0;j<5;j++)
	{
		for(i=0;i<5;i++)
		{
			staff[j].friend[i]=(i+1);		
		}
	}
	
	#if 0
	for(i=0;i<num_for_register;i++)
	{
		printf("%d-%s-%s\n",staff[i].num_qq,staff[i].loginid,staff[i].password);
	}
	i=0;
	while(staff[0].friend[i]>0)
	{
	  printf("staff[0].friend[i]=%d\n",staff[0].friend[i]);
	  i++;
	  if(i>100)
	  {
		break;
	  }
	}
	#endif
	i=0;
	while((cmd_for_help[i])!=NULL)
	{
		i++;
	}
	count_for_cmd=i;
	//初始化aaaaa bbbbb ccccc在900的多人会话里面
	staff[0].broad_id_count=1;
	staff[1].broad_id_count=1;
	staff[2].broad_id_count=1;
	staff[0].broad_id[0]=900;
	staff[1].broad_id[0]=900;
	staff[2].broad_id[0]=900;
	broad_array[0].broad_id=900;
	broad_array[0].user_list[0]=1;
	broad_array[0].user_list[1]=2;
	broad_array[0].user_list[2]=3;
	
}
void test_read_info_for_txt()
{
	int i=0;
	num_for_register=0;
	FILE *fp=fopen("./test.txt","r+");
	while((fgets(str_for_read,100,fp))!=NULL)
	{
		if(strlen(str_for_read)!=0)
		{
			//printf("%s\n",str_for_read);
			test_strtok(str_for_read);
			struct user *pst=&(staff[num_for_register]);
			pst->num_qq=atoi(cmd[0]);
			strcpy(pst->loginid,cmd[1]);			
			strcpy(pst->password,cmd[2]);      		
		}
		num_for_register++;
	}
	printf("num_for_register=%d\n",num_for_register);
	for(i=0;i<num_for_register;i++)
	{
		printf("%d-%s-%s\n",staff[i].num_qq,staff[i].loginid,staff[i].password);
	}
	
}
void test_read_info_of_staff()
{	
	num_for_register=0;
	//int i=0;
	while((info_of_staff[num_for_register])!=NULL)
	{
		printf("%s\n",info_of_staff[num_for_register]);
		test_strtok(info_of_staff[num_for_register]);
		struct user *pst=&(staff[num_for_register]);
		pst->num_qq=atoi(cmd[0]);
		strcpy(pst->loginid,cmd[1]);			
		strcpy(pst->password,cmd[2]);
		//printf("%s\n",cmd_for_help[i]);
		//printf("\n");
		num_for_register++;	
	}
}
void test_read_staff_info()
{
	int i=0;
	num_for_register=0;
	while((staff_info[num_for_register])!=NULL)
	{
		struct user *pst=&(staff[num_for_register]);
		pst->num_qq=atoi(staff_info[num_for_register][0]);
		strcpy(pst->loginid,staff_info[num_for_register][1]);			
		strcpy(pst->password,staff_info[num_for_register][2]);
		num_for_register++;	
	}
	for(i=0;i<num_for_register;i++)
	{
		printf("%d-%s-%s\n",staff[i].num_qq,staff[i].loginid,staff[i].password);
	}
}

void test_epoll()
{
	//printf("EPOLL_CTL_ADD is %d\n", EPOLL_CTL_ADD);
    //printf("EPOLL_CTL_DEL is %d\n", EPOLL_CTL_DEL);
    //printf("EPOLL_CTL_MOD is %d\n", EPOLL_CTL_MOD);
    int listenfd;
    listenfd = socket_bind(IPADDRESS, PORT);
    listen(listenfd, LISTENQ);
    do_epoll(listenfd);						//while 结构
    puts("epoll server end");
}
void test_help_command()
{
	//printf("%d\n",strlen(cmd_for_help));
	int i=0;
	while((cmd_for_help[i])!=NULL)
	{
		printf("%s\n",cmd_for_help[i]);
		printf("\n");
		i++;	
	}
}

void process_showbroad_server(char *buf)
{	
	char buf_temp[1024];
	char buf_temp_for_bdsh[1024];
	int i=0;
	int j=0;
	//printf("%s(%d) %s %d\n",__FILE__,__LINE__,buf,space_count);
	test_strtok(buf);
	//printf("%s(%d) %s %d\n",__FILE__,__LINE__,buf,space_count);
	//cmd_for_4_server
	//show
	//printf("%s(%d)%s %s %s %s\n",__FILE__,__LINE__,cmd[0],cmd[1],cmd_server[1],cmd_server[2]);
	memset(buf_temp,0,1024);
	if(strcmp(cmd[0],cmd_server[1])==0)
	//if(strcmp(cmd_for_4_server,cmd_server[1])==0)
	{
		//printf("%d\n",__LINE__);
		if(cmd[1]!=NULL)
		{
			//search(cmd[1]);
			for(i=0;i<num_for_register;i++)
			{
				//struct user *pst=&(staff[i]);
				//if(staff[i].loginid==cmd[1])
				if(strcmp(staff[i].loginid,cmd[1])==0)
				{
					strcat(buf_temp,cmd_for_4_server);
					strcat(buf_temp," ");	
					strcat(buf_temp,cmd[1]);
					for(j=0;j<staff[i].friend_count;j++)
					{
						if(search_num_qq_for_loginid(staff[i].friend[j]))
						{
							//printf
							strcat(buf_temp," ");							
							strcat(buf_temp,str_for_search_name);
							printf("%s (%d) %s\n",__FILE__,__LINE__,str_for_search_name);
						}
					}
					#if 0
					while((staff[i].friend[j])>0)
					{
												
					}
					#endif
					fd_for_send_message=staff[i].r_sockfd;
					printf("%s (%d) %s\n",__FILE__,__LINE__,buf_temp);
					do_write(epollfd, fd_for_send_message,buf_temp);
				}
			}
		}
	}
	//bdsh
	//if(strcmp(cmd_for_4_server,cmd_server[1])==0)
	//else if(strcmp(cmd_for_4_server,cmd_server[2])==0)
	else if(strcmp(cmd[0],cmd_server[2])==0)
	{
		//printf("%d\n",__LINE__);
		memset(buf_temp_for_bdsh,0,1024);
		if(cmd[1]!=NULL)
		{
			for(i=0;i<num_for_register;i++)
			{				
				//if(staff[i].loginid==cmd[1])
				if(strcmp(staff[i].loginid,cmd[1])==0)
				{
					strcat(buf_temp_for_bdsh,cmd_for_4_server);
					strcat(buf_temp_for_bdsh," ");	
					strcat(buf_temp_for_bdsh,cmd[1]);					
					for(j=0;j<staff[i].broad_id_count;j++)
					{
						test_int_to_char_server(staff[i].broad_id[j]);
						strcat(buf_temp_for_bdsh," ");
						strcat(buf_temp_for_bdsh,num_to_char_server);
					}
					fd_for_send_message=staff[i].r_sockfd;
					printf("%s (%d) %s\n",__FILE__,__LINE__,buf_temp_for_bdsh);
					do_write(epollfd, fd_for_send_message,buf_temp_for_bdsh);
					#if 0
					while(staff[i].broad_id>0)
					{
						test_int_to_char_server(staff[i].friend[j]);
						strcat(buf," ");
						strcat(buf,num_to_char_server);
					}					
					while((staff[i].friend[j])>0)
					{
						
						
						if(search_num_qq_for_loginid(staff[i].friend[j]))
						{
							strcat(buf," ");
							strcat(buf,buf_temp);
						}
						
					}	
					#endif				
				}
			}
		}	
	}
	
}


void process_show_server(char *buf)
{
	//printf("111\n");
	char buf_temp[10];
	int i=0;
	int j=0;
	test_strtok(buf);
	if(cmd[1]!=NULL)
	{
		//search(cmd[1]);
		for(i=0;i<num_for_register;i++)
		{
			//struct user *pst=&(staff[i]);
			if(staff[i].loginid==cmd[1])
			{
				while((staff[i].friend[j])>0)
				{
					if(search_num_qq_for_loginid(staff[i].friend[j]))
					{
						strcat(buf," ");
						strcat(buf,buf_temp);
					}
					
				}
				do_write(epollfd, fd_for_send_message,buf);
			}
		}
	}
	
}
/*
char message_server_1[4];//命令字
char message_server_2[10];//目标id
char message_server_3[100];//源id或者文件名
char message_server_4[1000];//具体的消息内容或者源id
char message_server_5[1000];//文件内容
int flag_for_message_or_file_server=0;//0-message   1--file
*/
void process_recv_file(char* buf_2)
{
	int ret=-1;
	FILE *fq_rc_s;
	char file_name_server[100];
	cut_string_for_message_file_recv_server(buf_2,1);
	ret=search(message_server_2);
	if(ret>=0)
	{
		if(staff[ret].is_login)
		{
			//用户在线
			do_write(epollfd, staff[ret].r_sockfd,buf_2);
		}
		else
		{
			//用户不在线,写在服务器本地文件---上线以后--的功能,获取有没有没接受到的文件,如果有就接收;
			cut_string_for_message_file_recv_server(buf_2,1);
			//接收文件
			memset(file_name_server,0,100);
			strcat(file_name_server,message_server_4);
			strcat(file_name_server,"_");
			strcat(file_name_server,message_server_2);
			strcat(file_name_server,"_");
			strcat(file_name_server,"s");
			strcat(file_name_server,"_");
			strcat(file_name_server,message_server_3);
			printf("%s(%d) %s \n",__FILE__,__LINE__,file_name_server);
			fq_rc_s=fopen(file_name_server,"w");
			if(fq_rc_s!=NULL)
			{
				//ssize_t write(int fd, void *buf, size_t count);				
				ret=fwrite(message_server_5,strlen(message_server_5),1,fq_rc_s);
				if(ret>0)
				{
					printf("%s(%d) fwrite success \n",__FILE__,__LINE__);
					fclose(fq_rc_s);
				}
				else
				{
					printf("%s(%d) fwrite failed \n",__FILE__,__LINE__);
					fclose(fq_rc_s);
				}
			}
			else
			{
				printf("%s(%d) server created file failed\n",__FILE__,__LINE__);
			}
		}
	}

}

void process_send_server(char *buf_1,int num)
{
	//printf("%s(%d) sendbroad\n",__FILE__,__LINE__); 
	//printf("%s(%d) send\n",__FILE__,__LINE__); 
	char buf_temp[1024];
	int index_staff_dst=-1;
	int index_staff_src=-1;
	int i=0;
	int j=0;
	int k=0;
	int broad_id_temp=0;
	int count=0;
	cut_string_for_message_file_recv_server(buf_1,0);
	if(num==8)
	{
		//printf("%s(%d) sendbroad\n",__FILE__,__LINE__);
		//strncpy(message_server_2,num_to_char_server,3);
		strncpy(num_to_char_server,message_server_2,3);
		test_char_to_int_server();
		while(1)
		{
			if(char_to_num_server==broad_array[i].broad_id)
			{
				break;
			}
			if(i>99)
			{
				break;
			}
			i++;
		}
		//获得多人会话id
		if(i<=99)
		{
			//r_socked_for_broad
			broad_id_temp=char_to_num_server;
			//找到所有在多人会话的num_qq;
			while(broad_array[i].user_list[j]>0)
			{
				index_staff_dst=broad_array[i].user_list[j]-1;
				if(staff[index_staff_dst].is_login)
				{
					r_socked_for_broad[k]=staff[index_staff_dst].r_sockfd;
					k++;
				}				
				j++;				
			}
			count=k;
			k=0;
			while(k<count)
			{
				do_write(epollfd, r_socked_for_broad[k],buf_1);
				k++;
			}
		}
		
	}
	else if(num==4)
	{
		//printf("%s(%d) send\n",__FILE__,__LINE__);
		index_staff_dst=search(message_server_2);
		index_staff_src=search(message_server_3);
		if(index_staff_dst>=0)
		{
			if(staff[index_staff_dst].is_login>0)
			{
				//do_write();
				do_write(epollfd, staff[index_staff_dst].r_sockfd,buf_1);
			}
			else
			{
				//cut_string_for_message_file_recv_server(buf_1,0);
				strcat(buf_temp,message_server_1);
				strcat(buf_temp," ");
				strcat(buf_temp,message_server_2);
				strcat(buf_temp," ");
				strcat(buf_temp,message_server_3);
				strcat(buf_temp," ");
				strcat(buf_temp,buf_for_send_failed);
				do_write(epollfd, staff[index_staff_src].r_sockfd,buf_temp);
				memset(buf_temp,0,sizeof(buf_temp));
			}
		}
		
	}


#if 0
	int ret=0;
	int ret_for_fd=0;
	int i=0;
	char message_for_client[200];
	char temp[200];
	memset(message_for_client, 0, 200);
	ret_for_fd=search_fd(fd_for_client);
	if((ret_for_fd>=0)&&(ret_for_fd<num_for_register))
	{
		struct user *pst=&(staff[ret_for_fd]);
		//printf("%d-%s\n",ret_for_fd,pst->loginid);		
		strcat(temp,pst->loginid);
		//printf("%s\n",temp);
	}
	ret=search(cmd[1]);
	if((ret>=0)&&(ret<num_for_register))
	{
		struct user *pst=&(staff[ret]);
		if(pst->is_login==1)
		{
			fd_for_send_message=pst->r_sockfd;
			strcat(message_for_client,temp);
			strcat(message_for_client," ");
			strcat(message_for_client,cmd[2]);
			//strcat(message_for_client,'\0');
			//printf("%s(%d)-%s-%d\n",__FILE__,__LINE__,message_for_client,strlen(message_for_client));
			do_write(epollfd, fd_for_send_message,message_for_client);
			//return 	fd_for_send_message;
		}
		
		/*
		struct user *pst=&(staff[ret]);
		if(strcmp(cmd[2],pst->password)==0)
		{
			printf("%s(%d)login success\n",__FILE__,__LINE__);
			pst->is_login=1;
			pst->r_sockfd=fd_for_client;
		}
		*/
		else
		{
			//return -1;
			printf("%s(%d) id offline,send message when he is online\n",__FILE__,__LINE__);
			printf("%s(%d) Segmentation fault (core dumped)\n",__FILE__,__LINE__);
			//Segmentation fault (core dumped)
			/*
			while(pst->p[i]!=NULL)
			{
				i++;
			}
			strcpy(pst->p[i],cmd[1]);
			*/
		}
		
	}
	else
	{
		printf("%s(%d) id error\n",__FILE__,__LINE__);
		//return -1;
	}
#endif
}
//处理增加和拉黑-addf [friend_id]
//addf bbbbb [source_id]
//set  bbbbb [source_id]
void process_add_set_server(char *buf_1)
{
	int ret=0;
	int i=0;
	int num_qq_for_friend_black_list=-1;
	test_strtok(buf_1); 
	ret=search(cmd[1]);//要把谁拉黑
	num_qq_for_friend_black_list=search(cmd[2]);
	staff[num_qq_for_friend_black_list].r_sockfd=fd_for_client;
	printf("%s(%d) (%d) (%d)\n",__FILE__,__LINE__,ret,num_qq_for_friend_black_list);
	if(ret>=0)
	{
		//num_qq_for_friend_black_list=
		//增加一个好友
		if(strcmp(cmd[0],cmd_server[5])==0)
		{
			while(staff[num_qq_for_friend_black_list].friend[i]>0)
			{
				i++;
				if(staff[num_qq_for_friend_black_list].friend[i]==(ret+1))
				{
					strcat(buf_1," ");
					strcat(buf_1," firend already exist!");
					//strcat(buf_1," ");
					do_write(epollfd, fd_for_send_message,buf_1);
					break;
				}
				
			}
			staff[num_qq_for_friend_black_list].friend[i]=(ret+1);
			staff[num_qq_for_friend_black_list].friend_count+=1;
			strcat(buf_1," ");
			strcat(buf_1," firend add suceess!");
			//strcat(buf_1," ");
			do_write(epollfd, fd_for_send_message,buf_1);
			
		}
		//拉黑
		else if(strcmp(cmd[0],cmd_server[9])==0)
		{
			while(staff[num_qq_for_friend_black_list].black_list[i]>0)
			{
				i++;
				if(staff[num_qq_for_friend_black_list].black_list[i]==(ret+1))
				{
					strcat(buf_1," ");
					strcat(buf_1," balck list already exist!");
					//strcat(buf_1," ");
					do_write(epollfd, fd_for_send_message,buf_1);
					break;
				}
				
			}
			staff[num_qq_for_friend_black_list].black_list[i]=(ret+1);
			staff[num_qq_for_friend_black_list].black_count+=1;
			strcat(buf_1," ");
			strcat(buf_1," balck list set suceesee!");
			//strcat(buf_1," ");
			do_write(epollfd, fd_for_send_message,buf_1);
		}
	}
}

// adbd [friend_id] [friend_id] [friend_id] [friend_id] [friend_id]-----add some friend to broad(at most 5) 
//待优化.....还没考虑黑名单的问题
void process_adbd_friend_server(char *buf_1)
{
	//space_count;
	char buf_for_adbd[100];
	int j=0;
	int k=0;
	int index_of_board_array=0; 
	int staff_index=-1;
	int broad_id_temp=0;
	//printf("%s(%d) %s\n",__FILE__,__LINE__,buf_1);
	test_strtok(buf_1);
	//ret=search(cmd[space_count-1]);
	int i=0;
	while(broad_array[i].broad_id>0)
	{
		i++;
	}
	index_of_board_array=i;
	//找到第一个能分配的多人会话的号码
	broad_id_temp=900+i;
	broad_array[index_of_board_array].broad_id=broad_id_temp;//要分配的多人会话的号码,发送多人会话,直接sdbd [多人会话号码]

	test_int_to_char_server(broad_id_temp);
	
	i=1;
	while(i<space_count)
	{
		//printf("%s(%d) %s %d,%d\n",__FILE__,__LINE__,cmd[i],i,space_count);
		staff_index=search(cmd[i]);
		if(staff_index>=0)
		{				
			j=0;
			while(staff[staff_index].broad_id[j]>0)
			{
				j++;
			}
			staff[staff_index].broad_id[j]=broad_id_temp;
			staff[staff_index].broad_id_count=(staff[staff_index].broad_id_count)+1;
			
			broad_array[index_of_board_array].user_list[k]=(staff_index+1);		
			//printf("%s(%d) broad_array[%d].user_list[%d]=%d\n",__FILE__,__LINE__,index_of_board_array,k,(staff_index+1));
			k++;
			strcat(buf_for_adbd,cmd_for_4_server);
			strcat(buf_for_adbd," ");
			strcat(buf_for_adbd,staff[staff_index].loginid);
			strcat(buf_for_adbd," ");
			strcat(buf_for_adbd,num_to_char_server);
			//num_to_char_server
			strcat(buf_for_adbd," ");
			strcat(buf_for_adbd,"success");			
			//usleep(1000);
			//printf(" %s(%d) %s (%d) \n ",__FILE__,__LINE__,staff[staff_index].loginid,j);
			printf(" %s(%d) %s  \n ",__FILE__,__LINE__,buf_for_adbd);
			do_write(epollfd, staff[staff_index].r_sockfd,buf_for_adbd);
			memset(buf_for_adbd,0,100);
			
		}
		i++;
	}
	//printf("%s(%d) %d\n",__FILE__,__LINE__,broad_id_temp);
	//test_int_to_char_server(broad_id_temp);
	
	//strcat(buf_1,num_to_char_server);
	//strcat(buf_1," ");
	//do_write(epollfd, fd_for_send_message,buf_1);
}


//char buf_for_login_success[100]="login success";
//char buf_for_login_failed[100]="user id or password error,login failed";
void process_login_rgst_server(char *buf_1)
{
	int ret=0;
	test_strtok(buf_1); 
	if(strcmp(cmd[0],cmd_server[3])==0)
	{			
			ret=search(cmd[1]);
			if(ret>=0)
			{
				staff[ret].r_sockfd=fd_for_client;
				//login
				//printf("%s(%d) (%s)%s(%d)(%d)\n",__FILE__,__LINE__,staff[ret].password,cmd[2],(int)strlen(staff[ret].password),(int)strlen(cmd[2]));
				if(strcmp(staff[ret].password,cmd[2])==0)
				{
					staff[ret].is_login=1;//登陆
					num_for_online+=1;
					staff[ret].r_sockfd=fd_for_client;
					fd_for_send_message=staff[ret].r_sockfd;
					strcat(buf_1," ");
					strcat(buf_1,staff[ret].loginid);
					strcat(buf_1," ");
					strcat(buf_1,buf_for_login_success);
					//printf("%s(%d)(%s) %s\n",__FILE__,__LINE__,,buf_for_login_success);
					//do_write(epollfd, fd_for_send_message,buf_1);
					do_write(epollfd, fd_for_send_message,buf_1);
				}
				else
				{
					strcat(buf_1," ");
					strcat(buf_1,buf_for_login_failed);
					printf("%s(%d) %s\n",__FILE__,__LINE__,buf_for_login_failed);
					do_write(epollfd, fd_for_send_message,buf_1);
				}
			}
			else
			{
				strcat(buf_1," ");
				strcat(buf_1,buf_for_login_failed);
				printf("%s(%d) %s\n",__FILE__,__LINE__,buf_for_login_failed);
				do_write(epollfd, fd_for_send_message,buf_1);
			}
			
	}
	//register注册
	else if(strcmp(cmd[0],cmd_server[10])==0)
	{
						
			if(search(cmd[1])>=0)
			{
				strcat(buf_1," ");
				strcat(buf_1,buf_for_register_failed);
				printf("%s(%d) %s\n",__FILE__,__LINE__,buf_for_register_failed);
				do_write(epollfd, fd_for_send_message,buf_1);
			}
			else
			{
				//printf("%s(%d) \n",__FILE__,__LINE__);
				struct user *pst=&(staff[num_for_register]);
				//printf("%s(%d) \n",__FILE__,__LINE__);
				pst->num_qq=(num_for_register+1);

				strcpy(pst->loginid,cmd[1]);			
				strcpy(pst->password,cmd[2]);
				//strcpy(pst->loginid,info_staff[num_for_register]);			
				//strcpy(pst->password,info_staff[num_for_register]);
				pst->is_login=1;//登陆
				num_for_online+=1;
				staff[num_for_register].r_sockfd=fd_for_client;
				//staff[ret].r_sockfd=fd_for_client;
				fd_for_send_message=fd_for_client;
				//fd_for_send_message=staff[ret].r_sockfd;
				
				printf("%s(%d) %s\n",__FILE__,__LINE__,buf_1);
				strcat(buf_1," ");
				strcat(buf_1,staff[num_for_register].loginid);
				strcat(buf_1," ");
				strcat(buf_1,buf_for_register_success);
				printf("%s(%d) %s\n",__FILE__,__LINE__,buf_1);
				num_for_register++;
				do_write(epollfd, fd_for_send_message,buf_1);
			}	
			
			
			//char buf_for_register_success[100]="register success";
			//char buf_for_register_failed[100]="user id already,register failed";
			
			#if 0
			if(strcmp(staff[ret].password,cmd[2])==0)
			{
				staff[ret].is_login=1;
				num_for_online+=1;
				staff[ret].r_sockfd=fd_for_client;
				fd_for_send_message=staff[i].r_sockfd;
				strcat(buf_1," ");
				strcat(buf_1,buf_for_login_success);
				//do_write(epollfd, fd_for_send_message,buf_1);
				do_write(epollfd, fd_for_send_message,buf_1);
			}
			else
			{
				strcat(buf_1," ");
				strcat(buf_1,buf_for_login_success);
				do_write(epollfd, fd_for_send_message,buf_1);
			}
			#endif
	}

	#if 0
	test_strtok(buf_1); 
	ret=search(cmd[1]);
	if(ret>=0)
	{
		staff[ret].r_sockfd=fd_for_client;
		//login
		
		struct user *pst=&(staff[ret]);
		pst->is_login=1;
		pst->r_sockfd=fd_for_client;
		//printf("%d-%d\n",strlen(cmd[2]),strlen(pst->password));
		//printf("%s(%d)cmd[2]=%s,pst->password=%s\n",__FILE__,__LINE__,cmd[2],pst->password);	
		if(strcmp(pst->password,cmd[2])==0)
		//if(strcmp(cmd[2],pst->password)==0)
		{
			//printf("%s(%d)login success\n",__FILE__,__LINE__);
			pst->is_login=1;
			num_for_online+=1;
			pst->r_sockfd=fd_for_client;			
		}
		else
		{
			//printf("%d\n",strcmp(pst->password,cmd[2]));
			//printf("%s(%d) cmd[2]=%s,pst->password=%s\n",__FILE__,__LINE__,cmd[2],pst->password);
		}
		
		
		
		
		
	}
	else
	{
		printf("%s(%d) %s\n",__FILE__,__LINE__,buf_1);
	}
	#endif
}
void process_register(char *buf_1)
{
	int ret=0;	
	ret=search(cmd[1]);
	if(ret>=0)
	{
		//用户名已经存在,请重新输入
		//printf("%s(%d) ""\n",__FILE__,__LINE__,buf_1);
	}
	else
	{
		//新增一个用户名和密码账号
		struct user *pst=&(staff[num_for_register]);
		pst->num_qq=(num_for_register+1);
		strcpy(pst->loginid,cmd[1]);
		strcpy(pst->password,cmd[2]); 
		//pst->loginid=cmd[1];		
		//pst->password=cmd[2];
		num_for_register+=1;
		pst->is_login=1;
		pst->r_sockfd=fd_for_client;
		printf("%s(%d)register success\n",__FILE__,__LINE__);
		
		//test_write_info_to_txt(num_for_register,pst->loginid,pst->password);
	}
}

void *station_broadcast_circle_thread( void *param )
{
	char buff[4096];
	int n=0;
	FILE *fp;
	pthread_detach(pthread_self());
	printf("%s(%d) %s\n",__FILE__,__LINE__,file);
	//sleep(3);
	if((fp = fopen(file,"ab") ) == NULL )
    {
        printf("File.\n");        
        exit(1);
    }
	printf("%s(%d) recv file\n",__FILE__,__LINE__);
	 while(1){
             n = read(sockfd_for_file, buff, 4096);
             if(n == 0)
                 break;
             fwrite(buff, 1, n, fp);
         }
	 fclose(fp);
	 exit(0);;
	/*
	while(is_ready_recv_file);
	int len=0;
	FILE *fq;
	if((fq=fopen(file[0],"rb"))==NULL)
	{
		printf("%s(%d) file open.\n",__FILE__,__LINE__);
		return;
	}
	bzero(buffer_for_send_file,sizeof(buffer_for_send_file));
	while(!feof(fq))
	{
		len=fread(buffer_for_send_file,1,sizeof(buffer_for_send_file),fq);
		if(len!=write(clientId,buffer_for_send_file,len))
		{
			break;
		}
	}
	is_ready_recv_file=1;
	fclose(fq);
	return;
	*/
	
}
void *station_thread( void *param )
{
	while(1)
	{
		//printf("child thread tid = %u\n", pthread_self());
		printf("%s(%d) station_thread tid=%lu\n",__FILE__,__LINE__,pthread_self());
		sleep(2);
	}
		
}

void analysis_message_server(char *buf)
{
	//if(strcmp(buf_for_read,"quit")==0)
	//printf("%s-%s\n",cmd[0],cmd_1[i]);
	int i=0;	
	int cmd_num=20;	
	while(i<count_for_cmd)
	{		
		if(strcmp(cmd_for_4_server,cmd_server[i])==0)
		{			
			//printf("%s(%d)-%s\n",__FILE__,__LINE__,cmd[0]);
			cmd_num=i;
			break;
		}
		i++;			
	}
	//printf("%s(%d) cmd_num=%d\n",__FILE__,__LINE__,cmd_num);
	switch(cmd_num)
	{
		case 2:
        case 1: 
			//printf("show\n");
			printf("%s(%d) show\n",__FILE__,__LINE__);
			//process_show_server(buf);
			process_showbroad_server(buf);
			break;
        //case 2: 
			//printf("showbroad\n");
			//printf("%s(%d) showbroad\n",__FILE__,__LINE__); 
			//break;
		case 10: 
			//printf("register\n");
			//process_register(); 
			//break;
        case 3: 
			printf("%s(%d) login\n",__FILE__,__LINE__);
			process_login_rgst_server(buf); 
			break;
		case 8://printf("%s(%d) sendbroad\n",__FILE__,__LINE__); 
			//printf("sendbroad\n"); 
			//break;
        case 4: 
			//printf("send\n");
			//printf("%s(%d) sendbroad\n",__FILE__,__LINE__); 
			//printf("%s(%d) send\n",__FILE__,__LINE__); 
			process_send_server(buf,cmd_num);			
			break;
		case 9: 
			//printf("setblacklist\n"); 
			//break;
        case 5: 
			//printf("add\n");
			printf("%s(%d) add\n",__FILE__,__LINE__);
			process_add_set_server(buf);
			
			break;
        case 6: 
			printf("add_broad\n");
			process_adbd_friend_server(buf);
			break;
        case 7: 
			//printf("ftp\n");
			printf("%s(%d) ftp\n",__FILE__,__LINE__);
			process_recv_file(buf);
			//pthread_create(&s_station_broadcast_circle_thread_id, NULL, station_broadcast_circle_thread, NULL);
			//pthread_create(&s_thread_id, NULL, station_thread, NULL);
			break;
		
        
        				
        default:
			printf("help\n");
			printf("command not found\n");
			test_help_command(); 
			break;
	}
	
	if(i>=11)
	{		
		//printf("command not found\n");
		//printf("please input help to get all cmd\n");
		//test_help_command();
	}
	
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

//change event
 static void change_event(int epollfd, int fd, int state, int op)
{
    struct epoll_event ev;
    ev.events = state;					
    ev.data.fd = fd;
 
	//函数原型：int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
	//函数解释：参数一epfd为epoll_create返回的创建fd
	//			参数二op为需要执行的操作(EPOLL_CTL_ADD：注册新的fd到epfd中；
	//EPOLL_CTL_MOD：修改已经注册的fd的监听事件；EPOLL_CTL_DEL：从epfd中删除一个fd；)
	//			参数三fd为要监听的fd套接字
	//			参数四event为要监听的状态   在ev.states=state,中赋值  包括EPOLLIN、EPOLLOUT
	
	epoll_ctl(epollfd, op, fd, &ev);
}

//io epoll
static void do_epoll(int listenfd)
{
    
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
#if 0
　　	 //函数解释：等待事件的产生,类似于select()调用
#endif
         //参数events用来从内核得到事件的集合,maxevents告之内核这个events有多大
		 //参数timeout是超时时间（毫秒，0会立即返回，-1将不确定，也有说法说是永久阻塞）
		 //该函数返回需要处理的事件数目，如返回0表示已超时。

         result = epoll_wait(epollfd, events, EPOLLEVENTS, -1);
         //printf("need deal with events is %d\n", result);
         handle_events(epollfd, events, result, listenfd, buf);
		 memset(buf,0,1024);
    }
    close(epollfd);
 
}

//deal with events
static void handle_events(int epollfd, struct epoll_event *events, int num, int listenfd, char *buf)
{
    int i;
    int fd;
	
	struct sockaddr_in localaddr;
	socklen_t len = sizeof(localaddr);
	int ret=-1;
    //foreach
    for (i = 0; i < num; ++i)
    {
         fd = events[i].data.fd;		
         //deal with events by fd
         if ((fd == listenfd) && (events[i].events & EPOLLIN)) 		//表示在监听描述符上有数据  三次握手accept
         {
            //puts("has go in handle_accpet");
            printf("%s(%d)-handle_accpet\n",__FILE__,__LINE__);
            handle_accpet(epollfd, listenfd);			
			
         }
         else if (events[i].events & EPOLLIN)
         { 
            //puts("do read");			
			//printf("%s(%d)-do read\n",__FILE__,__LINE__);
           do_read(epollfd, fd, buf);
		   
		   //客户端连接的套接字------------------------------------------------------------------------------------------------
		   fd_for_client=fd;
		   sockfd_for_file=fd;		   
		   //传输文件的协议和聊天的分开
			
		   //substr(buf);	
		   cutString_server(buf,4);		      
#if 0		   	
		   if(strcmp(sub_str_3,"ftp")==0)
		   	{
		   		
				printf("%s(%d) %s\n",__FILE__,__LINE__,cmd[2]);
				strcat(file,"server_");
				printf("%s(%d) %s\n",__FILE__,__LINE__,file);
		   		strcat(file,cmd[2]);
				printf("%s(%d) %s\n",__FILE__,__LINE__,file);
		   		//strcat("server_",file[0]);		   
		   		//strcat(file[0],"_server");				
		    }
		   else
		   	{
			 	printf("%s(%d)\n",__FILE__,__LINE__);
				test_strtok(buf);
				//test_strtok(buf);				
		    }
#endif
			//printf("%s(%d) %s\n",__FILE__,__LINE__,buf);
		    analysis_message_server(buf);	
		   
		   //接受数据以后,解析数据,如果收到的是登陆信息则验证账号密码,则修改登陆状态,记录套接字用于通信;
		   //如果收到的是注册信息则检测数据库中是否存在账号,如果存在则返回,如果不存在，记录到数据库中,
		   //修改账号登陆状态,记录套接字
		   if(space_count>=2)
		   {
		   	//do_write(epollfd, fd, cmd[2]);
		   }
		   //Segmentation fault (core dumped)		   
 	 	} 
         else if (events[i].events & EPOLLOUT)
         {
            //puts("do write");			
			printf("%s(%d)-do write\n",__FILE__,__LINE__);
            //do_write(epollfd, fd, buf);
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
        printf("%s(%d)accpet a new client:ip is %s and portsi %d---\n",__FILE__,__LINE__,inet_ntoa(cli_addr.sin_addr), cli_addr.sin_port);
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
       // change_event(epollfd, fd, EPOLLIN, EPOLL_CTL_DEL);        
    }
    else if (nread == 0)
    {
        //fprintf(stderr, "client close\n");
		printf("%s(%d) client close\n",__FILE__,__LINE__);
        close(fd);
        //delete event
        change_event(epollfd, fd, EPOLLIN, EPOLL_CTL_DEL);        
    }
    else 
    {
        //printf("%s(%d) read message (%d)is:  %s\n",__FILE__,__LINE__,nread,buf);
		
        //change event. from read to write
        //change_event(epollfd, fd, EPOLLOUT, EPOLL_CTL_MOD);
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
        //change_event(epollfd, fd, EPOLLOUT, EPOLL_CTL_DEL);		//不可写时从epollfd中删除监听的fd
    }
    else 
    {
		printf("%s(%d) do write\n",__FILE__,__LINE__);
        //change_event(epollfd, fd, EPOLLIN, EPOLL_CTL_MOD);
        //memset(buf, 0, MAXSIZE);
    }
}

void test_cmd_for_help()
{
	int i=0;
	int count=0;
	while(cmd_for_help[i]!=NULL)
	{
		//printf("%s\n",cmd_for_help[i]);
		count+=strlen(cmd_for_help[i]);
		i++;
	}
	
	printf("%d-%d\n",i,(int)strlen(cmd_for_help[1]));
	printf("%d\n",count);
}
void test_fread_file()
{
	FILE *fq;
	int len=0;
	int i=0;
	char buffer[1024];
	char buf[1000];
	strcpy(buffer,"ftp aaaa ./test.txt");
	printf("%s\n",buffer);
	
	i=sizeof("ftp aaaa ./test.txt");
	//strcat(buffer,'0');
	printf("%lu\n",sizeof("ftp aaaa ./test.txt"));
	//FILE *fp=fopen("./test.txt","r+");
	if((fq=fopen("./test.txt","r+"))!=NULL)
	{
		
		//printf("sss\n");
		fseek(fq, 0, SEEK_SET);
		
		while(!feof(fq))
		{
	        len = fread(buf, 1, 1000, fq);
			printf("len=%d\n",len);
			/*
	        if(len != write(sockfd, buffer, len))
			{
	             //printf("write.\n");
	            break;
	        }
	        */
     	}		
  	}
  printf("%s\n",buf);
  strcat(buffer,buf);
	//strcat(buffer[i],buf);
  //strcpy(buffer[i],buf);
  printf("%s\n",buffer);
}
void *receive_data_thread_server( void *param )
{
	int i=0;
	int ii=0;
	int temp=-1;
	int j=0;
	int k=0;
	char buf_from_stdin[1024];
	while(1)
	{	
		memset(buf_from_stdin,0,1024);
		ii=0;
		//gets(buf_for_read_server);
		fgets(buf_for_read_server,1024,stdin);
		while(buf_for_read_server[ii]!='\n')
		{
			ii++;
		}
		buf_for_read_server[ii]='\0';
		//printf("%s\n",buf_for_read_server);
		
		//printf("%c\n",buf_for_read_server[0]);
		//printf("%c\n",buf_for_read_server[1]);
		//printf("%c\n",buf_for_read_server[2]);
		if(strcmp(buf_for_read_server,"get")==0)
		{
			printf("register num is %d\n",num_for_register);
			for(i=0;i<num_for_register;i++)
			{
				printf("%d-%s-%s\n",staff[i].num_qq,staff[i].loginid,staff[i].password);
			}
			
		}

		if(strcmp(buf_for_read_server,"broad_array")==0)
		{
			k=0;
			j=0;
			while(broad_array[k].broad_id>0)
			{
				printf("---broad_array[%d].broad_id=%d---\n",k,broad_array[k].broad_id);
				//printf();				
				while(broad_array[k].user_list[j]>0)
				{
					printf("broad_array[%d].user_list[%d]=%d\n",k,j,broad_array[k].user_list[j]);
					j++;
				}
				k++;
				j=0;
			}
		}
		
		temp=(buf_for_read_server[0]-'0');
		if((temp>=0)&&(temp<num_for_register))
		{
			printf("staff[%d].loginid=%s\n",temp,staff[temp].loginid);
			printf("staff[%d].num_qq=%d\n",temp,staff[temp].num_qq);
			printf("staff[%d].friend_count=%d\n",temp,staff[temp].friend_count);
			printf("staff[%d].black_count=%d\n",temp,staff[temp].black_count);
			printf("staff[%d].broad_id_count=%d\n",temp,staff[temp].broad_id_count);
			if(staff[temp].friend_count>0)
			{
				for(i=0;i<staff[temp].friend_count;i++)
				{
					printf("staff[%d].friend[%d]=%d\n",temp,i,staff[temp].friend[i]);
				}
			}
			if(staff[temp].black_count>0)
			{
				for(i=0;i<staff[temp].black_count;i++)
				{
					printf("staff[%d].black_list[%d]=%d\n",temp,i,staff[temp].black_list[i]);
				}
			}
			if(staff[temp].broad_id_count>0)
			{
				for(i=0;i<staff[temp].broad_id_count;i++)
				{
					printf("staff[%d].broad_id[%d]=%d\n",temp,i,staff[temp].broad_id[i]);
				}
			}
			
		}

		#if 0
		
		if(strcmp(buf_for_read_server,"1")==0)
		{
			//printf("%c %d\n",buf_for_read_server[0],(buf_for_read_server[0]-'0'));
			
			i=0;
			printf("%s");
			printf("staff[%d].friend_count=%d\n",temp,staff[temp].friend_count);
			while(staff[temp].friend[i]>0)
			{
			  printf("staff[%d].friend[i]=%d\n",temp,staff[temp].friend[i]);
			  i++;
			  if(i>100)
			  {
				break;
			  }
			}
			i=0;
			printf("staff[%d].black_count=%d\n",temp,staff[temp].black_count);
			while(staff[temp].black_list[i]>0)
			{
			  printf("staff[%d].black_list[i]=%d\n",temp,staff[temp].black_list[i]);
			  i++;
			  if(i>100)
			  {
				break;
			  }
			}
			i=0;
			printf("staff[%d].broad_id_count=%d\n",temp,staff[temp].broad_id_count);
			while(staff[temp].broad_id[i]>0)
			{
			  printf("staff[%d].friend[i]=%d\n",temp,staff[temp].broad_id[i]);
			  i++;
			  if(i>100)
			  {
				break;
			  }
			}
			
		#endif		
		sleep(1);
	}
}

int main(int argc,char *argv[])
{
	
	init_info_staff();
	pthread_create(&s_receive_data_thread_id_s, NULL, receive_data_thread_server, NULL);
	test_epoll();
	
	/******/
	
	//test_cmd_for_help();
	 //test_struct();
	 //init_staff_struct(10);
	 //test_epoll();  
	 //test_help_command();
	 //test_read_info_of_staff();
	 //test_read_staff_info();
	 //test_read_info_for_txt();	 
	 //test_read_staff_infomation();
	 
	//test_fread_file(); 
	
	//substr("aaa aaaa ./test.txt");

	

	
	 	
}


