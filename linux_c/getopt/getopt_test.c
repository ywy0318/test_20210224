/*
Linux-C getopt命令行参数解析
 Linux-C getopt命令行参数解析
一、简述

       记--C语言 getopt命令行参数解析，有时候需要在调用应用程序时传入不同的参数来实现不同版本效果，比如新旧版本兼容，设置调试等级、程序使用方法，程序版本等。。。

二、getopt()

2.1 getopt函数说明

功能	用来解析命令行参数、命令行选项
头文件	#include <unistd.h>
原型	int getopt(int argc, char * const argv[], const char *optstring);
参数	argc	main函数的argc，参数个数
argv	main函数的argv，实际命令行参数
optstring	要解析的选项 "a:b:c:d" 表示解析-a -b -c -d 后面有一个冒号的表示附带参数，比如-a 100表示-a选项参数时100
返回值	
如果成功找到optstring中的选项，则返回选项字符。如果所有命令行选项都已解析完成，则返回-1。如果解析到一个选项

不在optstring中的字符，会返回'?'。如果遇到缺少参数的选项，则返回值取决于optstring中的第一个字符：如果是

':'，则返回':'；否则返回'?'。

说明	更多请查看man手册，man 3 getopt
*/
#include <unistd.h>
#include <stdio.h>
 
extern char *optarg;
extern int optind, opterr, optopt;
	  
void printUsage()
{
	printf("getopt_test - V0.0.1 (2020.11.29)\r\n");
	printf("usage: getopt_test [arguments]\r\n");
	printf("arguments:\r\n");
	printf("\t-a\r\n");
	printf("\t-b\r\n");
	printf("\t-c\r\n");
	printf("\t-d\r\n");
	printf("\t-h \tPrint Help (this message) and exit\r\n");
	printf("\t-v \tPrint Help (this message) and exit\r\n");
}	
	  
void printVersion()
{
	printf("getopt_test\r\n");
	printf("version:V0.0.1\r\n");
	printf("date:2020.11.29\r\n");
}  
	  
int main(int argc, char * argv[])
{    
    int opt;
	const char *optstring = "a:bc:d::hv"; //-a 100 -b -c 200 -d //b后面没有冒号说明不带参数，d后面有两个参数，说明参数可选 a、c后面带一个参数说明要带参数
    printf("optind:%d，opterr：%d\r\n", optind, opterr);//在unistd.h
	printf("===========================================\r\n");
	while (-1 != (opt = getopt(argc, argv, optstring))) {
		printf("optind: %d\r\n", optind);
		switch (opt) {
			case 'a':
				printf("option: -%c, optarg: %s\r\n", opt, optarg);
				break;
			case 'b':
				printf("option: -%c\r\n", opt);
				break;
			case 'c':
				printf("option: -%c, optarg: %s\r\n", opt, optarg);
				break;
			case 'd':
				printf("option: -%c, optarg: %s\r\n", opt, optarg);
				break;
			case 'h':
				printUsage();
				break;
			case 'v':
				printVersion();
				break;
			case '?'://未定义参数项
				printf("arg err:\r\n");
				printf("Try 'getopt_test --h' for more information.\r\n");
				break;
			default:
				printf("getopt_test: invalid option -- '%c'\r\n", opt);
				printf("Try 'getopt_test --h' for more information.\r\n");
				break;
		}
	}
	printf("===========================================\r\n");
	return 0;
}