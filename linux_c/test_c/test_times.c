#include<stdio.h>
#include <stdlib.h>
int main()
{
	while(1)
{
	static int itime = 0;
	itime++;
	if(itime%20==0)
	{
		printf("itime =%d \n",itime);
	}
	static int itime2 = 0;
	itime2++;
	if(itime2%22==0)
	{
		printf("itime2 =%d \n",itime2);
	}
		
	sleep(1);

}


}
