#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include"head.h"
//gcc -c *.c -I ../include/
//ar rcs libCalc.a *.o
//gcc main.c -o main -I include/ -L ./lib -lCalc
//nm mingling cha kan wenjian neirong
int main()
{
	printf("%d+%d is %d\n",10,10,add(10,10));
	printf("%d-%d is %d\n",10,10,sub(10,10));
}
