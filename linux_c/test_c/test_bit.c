#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int a = 0;
	int b0 = 0; 
	int b1 = 0;
	int b2 = 0;
	int b3 = 0;
	int b4 = 0; 
	int b5 = 0;
	int b6 = 0;
	int b7 = 0;

	printf("a = %d\n",a);
	//(a) |= 0x1 << (4);
	//a = 400;
	printf("a = %x,a = %d\n",a,a);
	a |= 0x010000;
	printf("a = %x,a = %d\n",a,a);
	b0 = 400;
	printf("b0 = %x,%d\n",b0,b0);	
	(b0) |= 0x1 << (16);
	printf("b0 = %x,%d\n",b0,b0);
	(b1) |= 0x1 << (16);
	printf("b1 = %x,%d\n",b1,b1);
	b1 +=400;
	printf("b1 = %x,%d\n",b1,b1);
	(b2) |= 0x1 << (2);
	printf("b2 = %x,%d\n",b2,b2);
	(b3) |= 0x1 << (3);
	printf("b3 = %x,%d\n",b3,b3);

	(b4) |= 0x1 << (4);
	printf("b4 = %x,%d\n",b4,b4);
	(b5) |= 0x1 << (5);
	printf("b5 = %x,%d\n",b5,b5);
	(b6) |= 0x1 << (6);
	printf("b6 = %x,%d\n",b6,b6);
	(b7) |= 0x1 << (7);
	printf("b7 = %x,%d\n",b7,b7);

	return 0;	
}
