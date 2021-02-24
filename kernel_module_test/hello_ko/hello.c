#include <linux/module.h>  //所有模块都必须包含的头文件
#include <linux/kernel.h> //一些宏定义，例如这里的KERN_INFO
#define DRIVER_AUTHOR "zyf"
#define DRIVER_DESC   "A sample driver"
static short int myshort = 1;
static int myint = 420;
static long int mylong = 9999;
static char *mystring = "blah";
static int myintArray[2] = {-1,-1};
static int arr_argc = 0;
//需要使用module_param来对参数进行说明，指明这个参数的类型，权限等charp是字符指针
//定义数组参数需要使用module_param_array
module_param(myshort,short,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);
MODULE_PARM_DESC(myshort,"A short integer");
module_param(myint,int,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
MODULE_PARM_DESC(myint,"A integer");
module_param(mylong,long,S_IRUSR);
MODULE_PARM_DESC(mylong,"A long integer");
module_param(mystring,charp,0000);
MODULE_PARM_DESC(mystring,"A character string");
module_param_array(myintArray,int,&arr_argc,0000);
MODULE_PARM_DESC(myintArray,"An array of integer");
/*
内核模块编程和应用程序编程的异同
•内核模块编程是不能去使用标准库(比如malloc free等)和一些第三方的库
•内核模块编程是没有内存保护的，如果内存访问错误，就会出现oops错误
•内核模块编程是没有main函数的，只有一个初始化函数，和一个提出函数
•内核模块编程需要使用内核提供的头文件和API
•内核模块编程的标准输出是输出到文件，而不是输出到屏幕
•内核模块编程的debug是不能使用gdb来进行调试的。
*/
#if 0
int init_module(void)
{
    printk(KERN_INFO "Hello world 1.\n");
    /*  
     * 返回非0表示模块初始化失败，无法载入
     */
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Goodbye world 1.\n");
}

//一个模块至少需要两个函数，一个初始化函数这里是init_module在载入内核的时候调用,
//一个结束函数，这里是cleannup_module在从内核中注销的时候调用


static int hello_2_init(void)
{
    printk(KERN_INFO "Hello,world 2\n");
    return 0;
}

static void  hello_2_exit(void)
{
    printk(KERN_INFO "Goodbye,world 2\n");
}

//这两个函数来注册模块初始化和模块结束
module_init(hello_2_init);
module_exit(hello_2_exit);

//模块的许可证 
MODULE_LICENSE("GPL");
//模块的作者
MODULE_AUTHOR(DRIVER_AUTHOR);
//模块的描述
MODULE_DESCRIPTION(DRIVER_DESC);
#endif

static int __init hello_5_init(void)
{
    int i;
    printk(KERN_INFO "Hello, world 5\n=============\n");
    printk(KERN_INFO "myshort is a short integer: %hd\n", myshort);
    printk(KERN_INFO "myint is an integer: %d\n", myint);
    printk(KERN_INFO "mylong is a long integer: %ld\n", mylong);
    printk(KERN_INFO "mystring is a string: %s\n", mystring);
    for (i = 0; i < (sizeof myintArray / sizeof (int)); i++)
    {
        printk(KERN_INFO "myintArray[%d] = %d\n", i, myintArray[i]);
    }
    printk(KERN_INFO "got %d arguments for myintArray.\n", arr_argc);
    return 0;
}

static void __exit hello_5_exit(void)
{
    printk(KERN_INFO "Goodbye,world 5\n");
}

module_init(hello_5_init);
module_exit(hello_5_exit);
/*

载入模块的时候，如果不指定参数就是上面的默认值，如果要指定参数的话
可以像下面这样来指定参数。insmod hello-5.ko mystring="superc" myint=444 

*/







