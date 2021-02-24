#define _CRT_SECURE_NO_WARNINGS
#include<dos.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<windows.h>
#include<conio.h>

int get_serious_fault_id(int value)
{
    int i=0;
    while(1)
        {
            if(i>7)
            {
               return 0;
            }
            if((value&(0x01<<i))!=0)
            {
               return (i+1);
			   printf("value&\n");
            }
            else
            {
               i++;
			   printf("i=%d\n",i);
            }
            
    }
}




int main()
{	
	printf("%d\n",0x01<<1);
	printf("%d\n",6&1);
	printf("%d\n",get_serious_fault_id(28));
	system("pause");
	return 0;
}