
//ubuntu1602_client ip:192.168.10.204
//ubuntu1602_server ip:192.168.10.230
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdlib.h"
#include "unistd.h"
#include "pthread.h"
#include "signal.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "sys/select.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include "sys/types.h"
#include "fcntl.h"
#include "errno.h"
#include "sys/stat.h"
#include "sys/termios.h"
#include "sys/ioctl.h"
#include "sys/msg.h"
#include <sys/epoll.h>

#include "sys/soundcard.h"
//#include "dirent.h"
//#include <net/if.h>
//#include <memory.h>
//#include <malloc.h>
//#include <sys/ioctl.h>
//#include <linux/i2c-dev.h>
//#include <linux/i2c.h>
//#include <sys/mman.h>
//#include <sys/time.h>
//#include <linux/rtc.h>
//#include <time.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <sys/un.h>

#define MAXSIZE 1024
#define IPADDRESS "192.168.10.230"
//#define IPADDRESS "127.0.0.1"
#define SERV_PORT 8888
#define FDSIZE 1024
#define EPOLLEVENTS 20






//char *cmd[20]={};

//接收的
char message_1[4];//命令字
char message_2[10];//目标id
char message_3[1000];//具体的消息内容或者或者文件名
char message_4[10];//源id-//源id				
char message_5[1000];//文件内容

int flag_for_message_or_file=0;//0-message   1--file
int  message_cut_count=0;

int file_name_length=0;
char login_id[20];
char login_password[20];
char login_yes[40];

char buffer_for_send_file[1024];

int space_count=0;
char string[]="2 zhangsan 89 99 90";
struct sockaddr_in client_for_debug;
static pthread_t s_station_broadcast_circle_thread_id;

int clientId=-1;
 
char cmd_for_4[10];
static char sub_str_3[10];

int fd_for_client=-1;//客户端
int is_ready_recv_file=1;
static pthread_t s_receive_data_thread_id_client;

//网络报文格式:[cmd] [dst_id] [source_id] [num_for_char] [message]
char num_to_char[3];
int char_to_num=0;
static int count_for_cmd_c=-1;

char *str_for_cut[30];

char cur_login_user[7];//当前登陆的用户
unsigned char is_login=0;//当前有没有用户登陆

unsigned char is_proccess=0;//

char login_success[100]="login success";
char register_success[100]="register success";

char message_for_cmd[7];
char message_for_dst_id[7];
char message_for_source_id[7];
char message_for_num_for_char[3];
char message_for_message[1000];

char mess_send_1[8];
char mess_send_2[8];
char mess_send_3[1000];


char buf_for_read[1024]; //从控制台stdin接收到的字符
char buf_for_send[1024]; //send的时候发送报文的buffer;

char buf[1024];//接受的时候的buffer


/******/
//analysis_message_send();cmd_1那里增加新的命令,然后需要修改analysis_message_send的函数
//adbd,一种是多人会话已经存在的,另外一种创建一个多人会话
char *cmd_1[20]=
{
	"help","show","bdsh","logn","send",
	"addf","adbd","ftpd","sdbd","stbl",
	"rgst","shbf"
};

//adbd--添加多人对话的时候不需要把自己也写上
//broad-多人会话
char *cmd_for_help_c[20]=
{
	//
	"help------------------------------------------------------show all command",//0
	"show-------------------------------------------------show your friend list",//1--待续	
	"bdsh---------------------------------------------show your broad list",	//2
	"logn [id] [password]------------------------------------------------login",//3
	"send [friend_id] [message]------------------------send your friend message",//4
	"addf [friend_id]-----------------------------------------------add a friend",
	"adbd [friend_id] [friend_id] [friend_id] [friend_id] [friend_id]-----add some friend to broad(at most 5)",//拉进多人会话//5
	"ftpd [frined_id] [file_name]-------------------transform your friend a file",//6
	"sdbd [broad_id]  [message]-----send message for all friend in broad",//7
	"stbl [friend_id]------------------------set someone in black list ",//8
	"rgst [id] [password]----------------------------------register a newer",//9
	"shbf [broad_id]-----------------------------------show broad member--"//10
};

	



static void handle_connection(int sockfd);
static void handle_events(int epollfd, struct epoll_event *events, int num, int sockfd, char *buf);
static void do_read(int epollfd, int fd, int sockfd, char *buf);
static void do_write(int epollfd, int fd, int sockfd, char *buf);
static void change_event(int epollfd, int fd, int state, int op);
/*
char型数字转换为int类型
转换方法 a[i]-'0'

int类型转换为char类型
转换方法a[i]+'0'
*/
void test_int_to_char(int num)
{
	int a=0,b=0,c=0;
	a=num/100;
	b=num%100/10;
	c=num%10;	
	char_to_num=num;
	message_for_num_for_char[0]=a+'0';
	message_for_num_for_char[1]=b+'0';
	message_for_num_for_char[2]=c+'0';
	printf("((%d)%c %c %c %d\n",__LINE__,message_for_num_for_char[0],message_for_num_for_char[1],message_for_num_for_char[2],char_to_num);
}

void test_char_to_int()
{
	int a=0;
	int b=0;
	int c=0;
	a=message_for_num_for_char[0]-'0';
	b=message_for_num_for_char[1]-'0';
	c=message_for_num_for_char[2]-'0';
	char_to_num=a*100+b*10+c;
	printf("(%d)%c %c %c %d\n",__LINE__,message_for_num_for_char[0],message_for_num_for_char[1],message_for_num_for_char[2],char_to_num);
}
//命令字之类的修改用户信息,查看查询用户状态的的报文信息,
//针对账号登陆者本身的功能;
//打包网络传输报文
//主要用于传输消息及文件传输等
//针对两个人的交互的功能;
void tar_message(int num)
{
	//if()
	test_int_to_char(num);	
	strncpy(buf_for_send, message_for_cmd, strlen(message_for_cmd));
	strcat(buf_for_send," ");
	strncpy(buf_for_send, message_for_dst_id, strlen(message_for_dst_id));
	strcat(buf_for_send," ");
	strncpy(buf_for_send, message_for_source_id, strlen(message_for_source_id));
	strcat(buf_for_send," ");
	strncpy(buf_for_send, message_for_num_for_char, strlen(message_for_num_for_char));
	strcat(buf_for_send," ");
	strncpy(buf_for_send, message_for_message, strlen(message_for_message));
	//strcat(buf_for_send," ");
}
//解压传输报文
void unzip_message(char *buf)
{
	int i=0;
	char *p=buf;
	while((*buf)!=' ')
	{
		message_for_cmd[i]=*buf;
		i++;
		buf++;
	}
	buf++;
	i=0;
	while((*buf)!=' ')
	{
		message_for_dst_id[i]=*buf;
		i++;
		buf++;
	}
	buf++;
	i=0;
	while((*buf)!=' ')
	{
		message_for_source_id[i]=*buf;
		i++;
		buf++;
	}
	buf++;
	i=0;
	//获取长度
	while((*buf)!=' ')
	{
		message_for_num_for_char[i]=*buf;
		i++;
		buf++;
	}
	buf++;
	i=0;
	//
	while((*buf)!='\0')
	{
		message_for_message[i]=*buf;
		i++;
		buf++;
	}
	test_char_to_int();
}


/*
help--打印所有命令
show--显示好友列表
showbroad--显示所有的多人会话id
login [id] [password]
send [id] [message]---发送单人消息
自动接收
add [id] [id] [id] 加入多人会话
send_broadcast [broad_id] [message]
ftp [id] [file_path]
多人会话
黑名单
*/
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
	//printf("%s\n",sub_str_3);
}


void test_pointer_array()
{
	int i;
	char *p1[5] = {
                "轮子工厂厂长招亲！",
                "身高不限",
                "肤色不限",
                "身材不限",
                "只要你不嫌弃厂长丑帅丑帅的~"
        };
    for (i = 0; i < 5; i++)
	{
      printf("%s\n", p1[i]);
    }    
	p1[0]="sssss";
	printf("%s\n", p1[0]);
}
int login(char * id_for_login,char * password_for_login)
{
	printf("%s(%d)-%s-%s\n",__FILE__,__LINE__,id_for_login,password_for_login);
	return 0;
}


void foreach_str_for_cut(int index)
{
	int i=0;
	for (i = index; i < space_count; i++)
	{
      printf("%s\n", str_for_cut[i]);
    }
	space_count=0;
}

//获取控制台输入的前四个字符
void cutString(char* string,int num)
{
	char *p_start = string;	    
    char newString[32];
	if(num>strlen(string))
	{
		printf("%s(%d)string is too short\n",__FILE__,__LINE__);
		is_proccess=0;
	}
	else 
	{
		is_proccess=1;
		strncpy(cmd_for_4, string, num);	
	}	
}



void cut_string_for_message_send_client(char * str)
{
	int i=0;		
	char *p=str;
	while((*str)!=' ')
	{
		mess_send_1[i]=*str;
		i++;
		str++;
	}
	str++;
	i=0;
	while((*str)!=' ')
	{
		mess_send_2[i]=*str;
		i++;
		str++;
	}
	str++;
	i=0;
	while((*str)!='\0')
	{
	mess_send_3[i]=*str;
	i++;
	str++;
	}	
	//printf("%s\n",mess_send_1);
	//printf("%s\n",mess_send_2);
	//printf("%s\n",mess_send_3);
}

//"send [friend_id] [message]------------------------send your friend message",
//"sdbd [broad_id]-----------------send message for all friend in broad",
//"ftpd [frined_id] [file_name]-------------------transform your friend a file",
/*
char message_1[4];//命令字
char message_2[10];//目标id
char message_3[100];//源id或者文件名
char message_4[1000];//具体的消息内容或者源id
char message_5[1000];//文件内容
int flag_for_message_or_file=0;//0-message   1--file
*/
//
void cut_string_for_message_file_recv_client(char *string,int flag)
{
	int i=0;
	char *p=string;
	while((*string)!=' ')
	{
		message_1[i]=*string;//命令字
		i++;
		string++;
	}
	string++;
	i=0;
	while((*string)!=' ')
	{
		message_2[i]=*string;//目标id
		i++;
		string++;
	}
	string++;
	i=0;
	while((*string)!=' ')
	{
		message_3[i]=*string;////具体的消息内容或者或者文件名
		i++;
		string++;
	}
	string++;
	i=0;

	if(flag)
	{
		while((*string)!=' ')
		{
			message_4[i]=*string;//者源id
			i++;
			string++;
		}
		string++;
		i=0;
		while((*string)!='\0')
		{
			message_5[i]=*string;//文件内容
			i++;
			string++;
		}
	}
	else
	{
		while((*string)!='\0')
		{
			message_4[i]=*string;//源id
			i++;
			string++;
		}
	}
		
}

void test_strtok_client(char * str)
{	
	space_count=0;		
	char *token=strtok(str," ");
	while(token!=NULL)
	{
		//printf("%s\t",token);
		str_for_cut[space_count]=token;
		space_count+=1;		
		token=strtok(NULL," ");
	}
	//printf("\n");
	//printf("space_count=%d\n",space_count); 
	//printf("\n");
	
}

void printf_send_message()
{
	printf("%s(%d) %s\n",__FILE__,__LINE__,buf_for_read);			
}
void printf_send_message_add(char *str_for_add)
{
	strcat(buf_for_read," ");
	strcat(buf_for_read,str_for_add);
	printf("%s(%d) %s\n",__FILE__,__LINE__,buf_for_read);
}
void send_socket_message(char *buf_for_send_message)
{
	int ret=-1;
	ret=send(clientId,buf_for_send_message,strlen(buf_for_send_message),0);
	//printf("%s(%d) (%d) %s\n",__FILE__,__LINE__,ret,buf_for_send_message);
   		if(ret<0)
   		{
	  		//perror("send");
	 		printf("%s(%d) send failed\n",__FILE__,__LINE__);
	  		//close(clientId);
	  		//continue;
		}
}

//addf bbbbb [source_id] [message]
//set  bbbbb [source_id] [message]
//addf stbl

void process_add_set_client_send()
{
	//
	if(cur_login_user==NULL)
	{
		printf_send_message_add("aaaaa");
	}
	else
	{
		printf_send_message_add(cur_login_user);	
	}
	send_socket_message(buf_for_read);
	
}
//----
void process_add_set_client_recv()
{
	if(strcmp(str_for_cut[0],cmd_1[5])==0)
	{
		//printf("%s(%d)%s %s\n",__FILE__,__LINE__,str_for_cut[2],str_for_cut[3]);
	}
	else if(strcmp(str_for_cut[0],cmd_1[9])==0)
	{
		//printf("%s(%d)%s %s\n",__FILE__,__LINE__,str_for_cut[2],str_for_cut[3]);
	}
	printf("%s(%d)%s %s\n",__FILE__,__LINE__,str_for_cut[2],str_for_cut[3]);
}


//查询好友及所有的多人会话的编号
void process_show__bdsh_client_send()
{
	//printf("111\n");
	if(cur_login_user==NULL)
	{
		printf_send_message_add("aaaaa");
	}
	else
	{
		printf_send_message_add(cur_login_user);	
	}
	send_socket_message(buf_for_read);
}
void process_show__bdsh_client_recv()
{
	int i=0;
	//test_strtok_client(char * str);
	//str_for_cut
	//显示好友列表
	if(strcmp(cmd_for_4,cmd_1[1])==0)
	{
		if(space_count>1)
		{
			printf("%s(%d) friend list:\n",__FILE__,__LINE__);
			foreach_str_for_cut(2);
		}
		else
		{
			printf("%s(%d) friend list null\n",__FILE__,__LINE__);
			printf("please use addf [friend_id]--add a friend\n");
		}
	}
	//显示当前登陆用户多人会话的所有id号
	else if(strcmp(cmd_for_4,cmd_1[2])==0)
	{
		//test_strtok_client(buf_1);
		if(space_count>1)
		{
			printf("%s(%d) broad list:\n",__FILE__,__LINE__);
			foreach_str_for_cut(2);
		}
		else
		{
			printf("%s(%d) broad  null\n",__FILE__,__LINE__);
			printf("adbd [friend_id] [friend_id]-----add some friend to broad(at most 3)\n");
		}
	}
}

//注册及登陆
//logn aaaaa a_password [message]
//register aaaaa a_password [message]
void process_register_client_send()
{	
	printf_send_message();
	send_socket_message(buf_for_read);
#if 0
	int ret=0;	
	ret=search(cmd[1]);
	if(ret>=0)
	{
		//用户名已经存在,请重新输入
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
#endif	
}
//char login_success[100]="login success";
//char register_success[100]="register success";
void process_rgsr_logn_client_recv()
{
	//printf("%s(%d)(%d)(%d)%s-%s\n",__FILE__,__LINE__,strlen(str_for_cut[2]),strlen(login_success),str_for_cut[2],login_success);



	if(strcmp(str_for_cut[0],"logn")==0)
	{
		if((strcmp(str_for_cut[3],"success")==0))
		//if((strcmp(str_for_cut[2],"suceesee")==0)||(strcmp(str_for_cut[2],register_success)==0))
		{
			is_login=1;
			//printf("%s(%d)(%d)\n",__FILE__,__LINE__,strlen(str_for_cut[1]));
			strcat(cur_login_user,str_for_cut[1]);
			//strncpy(cur_login_user,str_for_cut[1],strlen(str_for_cut[1]));	
			printf("%s(%d)%s\n",__FILE__,__LINE__,cur_login_user);
		}
		printf("%s(%d)%s %s  %s\n",__FILE__,__LINE__,str_for_cut[0],str_for_cut[1],str_for_cut[3]);	
	}
	else if(strcmp(str_for_cut[0],"rgst")==0)
	{
		if(strcmp(str_for_cut[2],"success")==0)
		{
			is_login=1;
			strcat(cur_login_user,str_for_cut[1]);
			printf("%s(%d)%s\n",__FILE__,__LINE__,cur_login_user);
		}
		printf("%s(%d)%s %s %s\n",__FILE__,__LINE__,str_for_cut[0],str_for_cut[1],str_for_cut[2]);	
	}
	
}
// adbd [friend_id] [friend_id] [friend_id] [friend_id] [friend_id]-----add some friend to broad(at most 5) 
void process_adbd_friend_cilent_send()
{
	if(cur_login_user==NULL)
	{
		printf_send_message_add("aaaaa");
	}
	else
	{
		printf_send_message_add(cur_login_user);	
	}
	send_socket_message(buf_for_read);
}
void process_adbd_friend_cilent_recv()
{
	//printf("%s(%d)%s %s\n",__FILE__,__LINE__,str_for_cut[1],str_for_cut[3]);
	int i=0;
	printf("%s(%d)  ",__FILE__,__LINE__);
	while(i<space_count)
	{
		printf(" %s ",str_for_cut[i]);
		i++;
	}
	printf("\n");
	
}
//
void process_recv_client(int num)
{
	//int flag_for_message_or_file=0;//0-message   1--file
	FILE *fq_rc;
	int ret=-1;
	char file_name[100];
	
	if(num==7)
	{
		cut_string_for_message_file_recv_client(buf,1);
		//接收文件
		memset(file_name,0,100);
		strcat(file_name,message_4);
		strcat(file_name,"_");
		strcat(file_name,message_2);
		strcat(file_name,"_");
		strcat(file_name,message_3);
		fq_rc=fopen(file_name,"w");
		if(fq_rc!=NULL)
		{
			//ssize_t write(int fd, void *buf, size_t count);
			
			ret=fwrite(message_5,strlen(message_5),1,fq_rc);
			if(ret>0)
			{
				printf("%s(%d) fwrite success \n",__FILE__,__LINE__);
				fclose(fq_rc);
			}
			else
			{
				printf("%s(%d) fwrite failed \n",__FILE__,__LINE__);
				fclose(fq_rc);
			}
		}
	}
	else 
	{	
		cut_string_for_message_file_recv_client(buf,0);
		if(num==4)
		{
			//printf("%s(%d) send\n",__FILE__,__LINE__);
			printf("%s(%d)  (%s) send %s\n",__FILE__,__LINE__,message_4,message_3);
		}
		else if(num==8)
		{
			//printf("%s(%d) (sdbd) send broad\n",__FILE__,__LINE__);
			printf("%s(%d) (broad:%s) (%s) sdbd %s\n",__FILE__,__LINE__,message_2,message_4,message_3);
		}
	}
	
}
//sdbd 977 xxx
//send bbbbb xxxxx
//ftp bbbbb test.txt
//ftp bbbbb test.txt aaaaa file_
void process_send_client(int num)
{
	FILE *fq;
	int len=-1;	
	cut_string_for_message_send_client(buf_for_read);
	//cut_string_for_message_file_recv_client(buf_for_read,1);
	//memset(buf_for_read,0,1024);	
	//strcat(buf_for_read,mess_send_1);
	//strcat(buf_for_read," ");
	//strcat(buf_for_read,mess_send_2);
	
	strcat(buf_for_read," ");	
	if(cur_login_user!=NULL)
	{
		strcat(buf_for_read,cur_login_user);
	}
	else
	{
		strcat(buf_for_read,"aaaaa");
	}	
	
	if(num==7)
	{
		
		strcat(buf_for_read," ");	
		//发送文件
		file_name_length=strlen(buf_for_read);
				
			if((fq=fopen(mess_send_3,"rb"))==NULL)
			{
				printf("%s(%d) file open.\n",__FILE__,__LINE__);
				return;
			}
			bzero(buffer_for_send_file,sizeof(buffer_for_send_file));
			//printf("%s(%d) send file\n",__FILE__,__LINE__);
			while(!feof(fq))
			{
				len=fread(buffer_for_send_file,1,(1024-file_name_length),fq);
				if(len>0)
				{
					strcat(buf_for_read,buffer_for_send_file);
					send_socket_message(buf_for_read);
				}
				else
				{	
					//strcat(buf_for_read,"\0");
					//send_socket_message(buf_for_read);
					break;
				}
				/*
				if(len!=write(clientId,buffer_for_send_file,len))
				{
					break;
				}
				*/
			}
			fclose(fq);
		
	}
	else 
	{		
		//strcat(buf_for_read,mess_send_3);
		send_socket_message(buf_for_read);
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

void test_help_command()
{
	//printf("%d\n",strlen(cmd_for_help));
	int i=0;
	//count_for_cmd_c;
	if(is_login==0)
	{
		printf("%s\n",cmd_for_help_c[0]);
		printf("%s\n",cmd_for_help_c[3]);
		printf("%s\n",cmd_for_help_c[10]);
	}
	else
	{
		while((cmd_for_help_c[i])!=NULL)
		{
			if((i!=3)||(i!=10))
			{
				printf("%s\n",cmd_for_help_c[i]);
				printf("\n");
			}			
			i++;	
		}
	}
	#if 0
	while((cmd_for_help_c[i])!=NULL)
	{
		printf("%s\n",cmd_for_help[i]);
		printf("\n");
		i++;	
	}
	#endif
}

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
        {
			return count - nleft;
		}
            
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
ssize_t readline(int sockfd, char *buf, size_t maxline)
//ssize_t readline(int sockfd, void *buf, size_t maxline)
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


#if 0
int register(){
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

void *receive_data_thread( void *param )
{
	//printf("122\n");
	while(1)
	{
		
	}
}


/* According to POSIX.1-2001 */
#include <sys/select.h>
/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
int select(int nfds, fd_set *readfds, fd_set *writefds,fd_set *exceptfds, struct timeval *timeout);
void FD_CLR(int fd, fd_set *set);//测试某个描述符是否在集合内
int  FD_ISSET(int fd, fd_set *set);//从集合内把一个描述符移除
void FD_SET(int fd, fd_set *set);//把一个描述符加入集合
void FD_ZERO(fd_set *set);//清空描述符集合

#endif


//Socket套接字编程（I/O复用 select）
int test_socket_select()
{
	char sendbuf[1024]= {0},revbuf[1024]= {0};
	
	signal(SIGPIPE,SIG_IGN);
    fd_set rset;
    FD_ZERO(&rset);
    struct sockaddr_in user;
    user.sin_family = AF_INET;
    user.sin_port = htons(8001);
	//user.sin_addr.s_addr = inet_addr("127.0.0.1");
    user.sin_addr.s_addr = inet_addr("192.168.10.230");
    int sockfd,stdinfd,maxfd;
    
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

void test_epoll_client()
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
void analysis_message_recv_client()
{
	
}
//flag=1的时候发送
void analysis_message_client(int flag)
{
	//if(strcmp(buf_for_read,"quit")==0)
	//printf("%s-%s\n",cmd[0],cmd_1[i]);
	int i=0;
	int count_for_cmd=-1;
	int cmd_num=20;
	
	while((cmd_1[i])!=NULL)
	{
		i++;
	}
	count_for_cmd=i;
	i=0;
	while(i<count_for_cmd)
	{			
		if(strncmp(cmd_for_4,cmd_1[i],4)==0)		
		{			
			//printf("%s(%d)-%s\n",__FILE__,__LINE__,cmd[0]);
			cmd_num=i;
			break;
		}
		i++;			
	}
	//printf("%s(%d) cmd_num=%d,is_login=%d\n",__FILE__,__LINE__,cmd_num,is_login);

	if(is_login==0)
	{
		
		switch(cmd_num)
	    {
			/*************修改及查询自身状态*********/
			case 3:	//printf("%s(%d) (logn) login\n",__FILE__,__LINE__);
				//process_login(); 
				//break;
			case 10: 
				//printf("register\n");
				//printf("%s(%d) ",__FILE__,__LINE__);
				//printf("%s\n",buf_for_read);
				printf("%s(%d) %s\n",__FILE__,__LINE__,buf);
				test_strtok_client(buf);
				//printf("%s(%d)(%d)\n",__FILE__,__LINE__,space_count);
				if(flag)
				{
				   process_register_client_send(); 
				}
				else
				{
					
					process_rgsr_logn_client_recv();
				}
				
				//break;
				//send_socket_message(buf_for_read);
				break;
	        
			
	        /******不发送消息直接在客户端打印的**********/        				
	        default:
				printf("%s(%d) help\n",__FILE__,__LINE__); 			
				printf("command not found\n");
				test_help_command(); 
				break;
		}
	}
	else
	{	

		switch(cmd_num)
		{
			case 1://printf("%s(%d) (show) show your friend list\n",__FILE__,__LINE__); 
			case 2://printf("%s(%d) (bdsh) showbroad\n",__FILE__,__LINE__); 	
				//printf("show\n");
				test_strtok_client(buf);
				if(flag)
				{
					process_show__bdsh_client_send();
				}
				else
				{
					process_show__bdsh_client_recv();
				}
				

				
				break;
	        
				//printf("showbroad\n");
							
				//break;
	        

		   case 9://printf("%s(%d) (stbl) setblacklist\n",__FILE__,__LINE__);
		   case 5://printf("%s(%d) (addf) add a friend\n",__FILE__,__LINE__);	 
				  //printf("setblacklist\n");
				  test_strtok_client(buf);
				  if(flag)
				  {
					process_add_set_client_send();	
				  }
				  else
				  {
				  	process_add_set_client_recv();
					
				  }
	  			  break;
	         
				//printf("add\n");
				 
				//break;

		   
	        case 6: 
				//printf("add_broad\n");
				//printf("%s(%d)(adbd) add broad\n",__FILE__,__LINE__);
				test_strtok_client(buf);
				if(flag)
				{
					process_adbd_friend_cilent_send();
				}
				else
				{
					//process_adbd_friend_cilent_send();
					process_adbd_friend_cilent_recv();
				}
				break;
			
			/*********两人及交互信息**************/
			case 7://printf("%s(%d) (ftpd) ftp file\n",__FILE__,__LINE__); 
			case 8://printf("%s(%d) (sdbd) send broad\n",__FILE__,__LINE__);
			case 4: 
				//printf("send\n");
				//printf("%s(%d) send\n",__FILE__,__LINE__);
				//printf("%s(%d) (sdbd) send broad\n",__FILE__,__LINE__);
				if(flag)
				{
					process_send_client(cmd_num);	
				}
				else
				{
					process_recv_client(cmd_num);
				}
								
				break;
	        
				//printf("ftp\n");
				
				//pthread_create(&s_station_broadcast_circle_thread_id, NULL, station_broadcast_circle_thread, NULL);
				//pthread_create(&s_thread_id, NULL, station_thread, NULL);
				//break;
			 
				//printf(" sdbd sendbroad\n"); 
				
				//break;
		 	 /******不发送消息直接在客户端打印的**********/        				
	        default:
				printf("%s(%d) help\n",__FILE__,__LINE__); 			
				printf("command not found\n");
				test_help_command(); 
				break;
		}
		
	}
	
	
	
	//if(i>=11){		
		//printf("command not found\n");
		//printf("please input help to get all cmd\n");
		//test_help_command();
	//}	
}


void *station_broadcast_circle_thread( void *param )
{
	pthread_detach(pthread_self());
	sleep(3);
	//printf("%s(%d) %s\n",__FILE__,__LINE__,file);
	//while(is_ready_recv_file);
	int len=0;
	FILE *fq;
	if((fq=fopen("./test.txt","rb"))==NULL)
	{
		printf("%s(%d) file open.\n",__FILE__,__LINE__);
		exit(1);
		//return;
	}
	bzero(buffer_for_send_file,sizeof(buffer_for_send_file));
	printf("%s(%d) send file\n",__FILE__,__LINE__);
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
	//return;
	
}

//接受控制台输入stdin,人机交互界面的协议解析
void *receive_data_thread_client( void *param )
{
	int ret=-1;
	int i=0;
	int len;
	FILE *fq;
	//sleep(5);
	while(1)
	{
	  //gets(buf_for_read);
	  memset(buf_for_read,0,1024);
	  i=0;
	  fgets(buf_for_read,1024,stdin);
	  while(buf_for_read[i]!='\n')
		{
			i++;
		}
	  buf_for_read[i]='\0';
	  //printf("%s\n",buf_for_read);
	  //fgets(buf_for_read,1024,stdin);
	  //printf("%s\n",buf);
      if(strcmp(buf_for_read,"quitquit")==0)
       {
          break;
          //continue;
       }
	  
	  cutString(buf_for_read,4);
	  if(is_proccess==1)
	  {
	  	is_proccess=0;
		analysis_message_client(1);	
	  }
	  
	  
		
#if 0
	  //ftp aaaaa test.txt
	  if(strcmp(string_cmd,"ftp")==0)
	  {	  	
		//printf("%s(%d)transform a file...\n",__FILE__,__LINE__);
		memset(string_cmd,0,sizeof(string_cmd));
		file_name_length=strlen(buf_for_read)+5;
		test_int_to_char(file_name_length);
		strcat(buf_for_read," ");
		strcat(buf_for_read,num_to_char);
		strcat(buf_for_read," ");
		test_strtok(buf_for_read);
		if(cmd[2]!=NULL)
		{
			strcat(file,cmd[2]);
		}
		if((fq=fopen(file,"rb"))==NULL)
		{
			printf("%s(%d) file open.\n",__FILE__,__LINE__);
			return;
		}
		printf("%s(%d)\n",__FILE__,__LINE__);
		while(!feof(fq))
		{
			len=fread(buffer_for_send_file,1,(1024-file_name_length),fq);
			ret=send(clientId,buf_for_read,sizeof(buf_for_read),0);
			if((len+file_name_length)<ret)
			{
				break;
			}
			
		}		
		ret=send(clientId,buf_for_read,sizeof(buf_for_read),0);
   		if(ret<0)
   		{
	  		//perror("send");
	 		printf("%s(%d) send failed\n",__FILE__,__LINE__);
	  		//close(clientId);
	  		continue;
		}
		
		fclose(fq);
		
		//printf("%s(%d) %s\n",__FILE__,__LINE__,buf_for_read);		
		//test_strtok(buf_for_read);	
		
		if(cmd[2]!=NULL)
		{
			//printf("%s(%d)\n",__FILE__,__LINE__);
			//strcpy(file,cmd[2]);
			//printf("%s(%d)file name is %s\n",__FILE__,__LINE__,file);			
			//pthread_create(&s_station_broadcast_circle_thread_id, NULL, station_broadcast_circle_thread, NULL);
		}
		

		//bzero(buffer,sizeof(buffer));
		/*
		if((fq=fopen("./test.txt","rb"))==NULL)
		{
			printf("open file failed\n");
		}
		
		
		while(!feof(fq))
			{
			len=fread(buffer,1,sizeof(buffer),fq);
			if(len!=write(clientId,buffer,len))
				{
				printf("write...\n");
				break;
			}
		}
		*/
		
	  }
	  else
	  {
	 	ret=send(clientId,buf_for_read,sizeof(buf_for_read),0);
   		if(ret<0)
   		{
	  		//perror("send");
	 		printf("%s(%d) send failed\n",__FILE__,__LINE__);
	  		//close(clientId);
	  		continue;
		}  
	  }
#endif

	    
  	  
	}
}

int test_tcp_socket_send()
{
	int ret=-1;
	//定义Internet协议结构,客户端的IP信息
     struct sockaddr_in myaddr,localaddr;
     memset(&myaddr,0,sizeof(myaddr));
     myaddr.sin_family = PF_INET;
     myaddr.sin_port = htons(8888);
     myaddr.sin_addr.s_addr = inet_addr("192.168.10.230");
	
	socklen_t len=sizeof(localaddr);
	
  //1.创建套接字
   clientId = socket(PF_INET,SOCK_STREAM,0);
   if(clientId<0)
   {
    perror("socket\n");
    return  -1;
   }
   printf("socket ok\n");
  //2发起链接请求
   ret = connect(clientId,(struct sockaddr *)&myaddr,sizeof(myaddr));
  if(ret <0)
  {
    perror("connect\n");
    close(clientId);
    return -1;
  }
  printf("connect ok\n");
  ret=-1;
  ret=getsockname(clientId,(struct sockaddr*)&localaddr, &len);
  if(ret!=0)
  {
  		perror("getsockname");
  }
  else
  {
  		printf("%s(%d)port: %d\n",__FILE__,__LINE__,ntohs(localaddr.sin_port));	
  }
  //setsockopt(socket,SOL_SOCKET,SO_RCVTIMEO, (char *)&timeout,sizeof(struct timeval));
  //printf("port=%d\n",);
  
  // 3接收消息
  
  
  while(1)
  {
      
      memset(buf,0,1024);
#if 1	  
      ret = recv(clientId,buf,sizeof(buf),0);
      if(ret<0)
      {
          perror("recv\n");
          close(clientId);
          return -1;
      }
	  else if(ret>0)
	  {
	  	//printf("%s(%d)received from xldserver:%s\n",__FILE__,__LINE__,buf);
		//cutString(buf_for_read,3);
		cutString(buf,4);
		
		analysis_message_client(0);
#if 0
		if(strcmp(string_cmd,"ftp")==0)
		{
			memset(string_cmd,0,sizeof(string_cmd));
		}
		else
		{
			printf("%s\n",buf);
		}	
#endif	
		//strtok_2(buf);
	  	//printf("received message from %s:%s\n",mess_1,mess_2);
      	memset(buf,0,1024);
	  	
	  }
	  else
	  {
	  	//printf("%s(%d)received from xldserver:null\n",__FILE__,__LINE__);
	  }
      sleep(1);
	  //
      //printf("xldclient: ");
#endif	  
      
  }

  //4.关闭套接字
  close(clientId);
  return 0;
	
	
	 
}

int main()
{
	int ret=-2;
	//char buf[100]="aa aaa zz";

	num_to_char[0]='9';
	num_to_char[1]='9';
	num_to_char[2]='9';
	//启动之后,
	//询问是否注册,不注册，直接登陆
	//登陆以后//获取字符根据字符判断
	printf("welcom to tiandy QQ ^-^!\n");
	//printf("%s\n",buf);
	memset(login_id,0,20);		
	memset(login_password,0,20);	
	memset(login_yes,0,20);	

	ret=0;	
	while((cmd_for_help_c[ret])!=NULL)
	{
		ret++;
	}
	count_for_cmd_c=ret;
	
	
	//pthread_create(&s_receive_data_thread_id, NULL, receive_data_thread, NULL);

	//usleep(1000);
	//printf("please input your id:");
	 
	//gets(login_id);

	//ret=strcmp(login_id,"login");

	
	//发送给服务器,
	//printf("please input your password:");
	
	//gets(login_password);
	//执行登陆
	//login(login_id,login_password);
	//登陆成功以后
	//登陆失败以后    
	//test_strtok();	
	//test_pointer_array();	
	//test_socket_select();
	//test_epoll_client();	
	//strtok_2(buf);	
	//test_int_to_char(999);
	//test_char_to_int();
	
	/**************/
	pthread_create(&s_receive_data_thread_id_client, NULL, receive_data_thread_client, NULL);
	test_tcp_socket_send();
	while(1)
	{
		usleep(100);
		//gets(login_id);
		//test_strtok(login_id);
		//strcat(login_id,"$^-^$");
	    //puts(login_id);
		
	}	

}
//执行注册











