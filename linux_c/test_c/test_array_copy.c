#include "stdio.h"
#include "stdlib.h"
#include "string.h"
void test_array_copy(int disk_array[4])
{
	int disk[4]={0};
	char* test = NULL;
	disk[0] = 100;
	disk[1] = 101;
	disk[2] = 102;
	disk[3] = 103;
	memcpy(disk_array,disk,sizeof(disk));
	printf("sizeof(disk) = %d\n",sizeof(disk));
	printf("sizeof(disk_array) = %u\n",sizeof(disk_array));
	printf("sizeof(char* test) = %u\n",sizeof(*test));
	printf("sizeof(char test) = %u\n",sizeof(test));
	return ;
}

int main()
{
	int i = 0;
	int aaa[4] = {-1};
	for( i =0;i<4;i++)
	{
		printf("aaa[%d] = %d\n",i,aaa[i]);
	}
	test_array_copy(aaa);
	for(i =0;i<4;i++)
	{
		printf("aaa[%d] = %d\n",i,aaa[i]);
	}
	return 0;
}
