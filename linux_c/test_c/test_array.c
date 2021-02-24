#include "stdio.h"
#include "stdlib.h"

void test_array(int *arr,int size)
{
	int array[100] = {2};
	
	for(int j = 0;j<10;j++)
	{
	printf("%s %s line=(%d) YWY........array[%d]=%d \n",__FILE__,__FUNCTION__,__LINE__,j,array[j]);	
	}
	memcpy(array,arr,size);
	for(int j = 0;j<10;j++)
	{
	printf("%s %s line=(%d) YWY.ddd.......array[%d]=%d \n",__FILE__,__FUNCTION__,__LINE__,j,array[j]);	
	}

	printf("%s %s (%d) YWY........size = %d \n",__FILE__,__FUNCTION__,__LINE__,size);
	return;
}
int main()
{
	int test_arr[5]={0};
	for(int i = 0;i<5;i++)
	{
		test_arr[i] = i;
		printf("%s %s line=(%d) YWY........test_arr[%d]=%d \n",__FILE__,__FUNCTION__,__LINE__,i,test_arr[i]);
	}
	printf("%s %s (%d) YWY........ \n",__FILE__,__FUNCTION__,__LINE__);
	test_array(test_arr,sizeof(test_arr));
	printf("%s %s (%d) YWY........ sizeof(test_arr) = %d\n",__FILE__,__FUNCTION__,__LINE__,sizeof(test_arr));
	return 0;
}
