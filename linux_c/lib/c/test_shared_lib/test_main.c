#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include"head.h"
//gcc -fPIC -c *.c -I ../include/
//gcc -shared -o libCalc.so *.o
//gcc main.c -o main -I include/ -L ./lib -lCalc
//cannot open shared object file:No such file or directory
//1. copy to /lib(拷贝到/lib下（不允许，容易与别人库命名重合）)
//2.(将库路径增加到环境变量LD_LIBRARY_PATH中（不是特别推荐）)
//export LD_LIBRARY_PATH=/home/xuejiale/src/calc/lib/:$LD_LIBRARY_PATH
//3.配置/etc/ld.so.conf文件，增加 /home/xuejiale/src/calc/lib/ 路径，执行 ldconfig -v，并执行main
//nm mingling cha kan wenjian neirong
int main()
{
	printf("%d+%d is %d\n",10,10,add(10,10));
	printf("%d-%d is %d\n",10,10,sub(10,10));
	while(1)
	{
		printf("%d+%d is %d\n",10,10,add(10,10));
		printf("%d-%d is %d\n",10,10,sub(10,10));
		sleep(2);	
		
	}
	return 0;
}
