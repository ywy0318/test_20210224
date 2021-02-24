#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include <signal.h>
void *g_ptChnAuthorityMem = NULL;
/*
Linux支持的信号列表如下。很多信号是与机器的体系结构相关的
信号值 默认处理动作 发出信号的原因


SIGHUP 1 A 终端挂起或者控制进程终止
SIGINT 2 A 键盘中断（如break键被按下）
SIGQUIT 3 C 键盘的退出键被按下
SIGILL 4 C 非法指令
SIGABRT 6 C 由abort(3)发出的退出指令
SIGFPE 8 C 浮点异常
SIGKILL 9 AEF Kill信号
SIGSEGV 11 C 无效的内存引用
SIGPIPE 13 A 管道破裂: 写一个没有读端口的管道
SIGALRM 14 A 由alarm(2)发出的信号
SIGTERM 15 A 终止信号
SIGUSR1 30,10,16 A 用户自定义信号1
SIGUSR2 31,12,17 A 用户自定义信号2
SIGCHLD 20,17,18 B 子进程结束信号
SIGCONT 19,18,25 进程继续（曾被停止的进程）
SIGSTOP 17,19,23 DEF 终止进程
SIGTSTP 18,20,24 D 控制终端（tty）上按下停止键
SIGTTIN 21,21,26 D 后台进程企图从控制终端读
SIGTTOU 22,22,27 D 后台进程企图从控制终端写

#include <signal.h>

#include <unistd.h>

#include <stdio.h>
信号处理例程，其中dunno将会得到信号的值 
void sigroutine(int dunno)

{ 

        switch (dunno) {

        case 1:

        printf("Get a signal -- SIGHUP ");

        break;

        case 2:

        printf("Get a signal -- SIGINT ");

        break;

        case 3:

        printf("Get a signal -- SIGQUIT ");

        break;

        }

        return;

}

 

int main() {

        printf("process id is %d ",getpid());

        signal(SIGHUP, sigroutine); //* 下面设置三个信号的处理方法

        signal(SIGINT, sigroutine);

        signal(SIGQUIT, sigroutine);

        for (;;) ;

}

 

其中信号SIGINT由按下Ctrl-C发出，信号SIGQUIT由按下Ctrl-发出。该程序执行的结果如下：
localhost:~$ ./sig_test
process id is 463
Get a signal -SIGINT //按下Ctrl-C得到的结果
Get a signal -SIGQUIT //按下Ctrl-得到的结果
//按下Ctrl-z将进程置于后台
 [1]+ Stopped ./sig_test
localhost:~$ bg
 [1]+ ./sig_test &
localhost:~$ kill -HUP 463 //向进程发送SIGHUP信号
localhost:~$ Get a signal – SIGHUP
kill -9 463 //向进程发送SIGKILL信号，终止进程
localhost:~$

*/

void sigroutine()
{
	printf("signal 11\n");
	return;
}

void test_void_ptr()
{
	unsigned int u32Rights = -1;
	
	printf("test_void_ptr 1\n");
	memcpy((unsigned int*)((unsigned int*)g_ptChnAuthorityMem+1),&u32Rights,4);
	printf("test_void_ptr 2\n");
}

int main()
{
	//signal(SIGSEGV, sigroutine);
	test_void_ptr();
	printf("finished main....\n");
}
