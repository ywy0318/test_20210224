/*����10����ͬ�����������*/

/***********************************/
/*a=rand()%100;printf("%d",a/100);*/
/*�����ȥ0��100��Ȼ�����100*/
/***********************************/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<windows.h>
#include<dos.h>
#define NUM 5
#define RANG 10
int main(){
	int i = 0;
	int m = 0;
	double ret;
	double f[1000];
	int n = 0;
	srand(time(0));
	for (i = 0; i < NUM;)
{
	//����С��
	ret = rand() /((double)(RAND_MAX)/100);

	//ret = rand() % 100;
	for (m = 0; m < i; m++)
	{
		if (f[m] == ret)
		{
			break;
		}
	}
	if (m == i)
	{
		printf("%lf ",ret);
		f[i] = ret*1.00;
		i += 1;
	}
}



printf("min\n");
for (n = 0; n < NUM; n++)
{
	//�������뱣����λС��
	printf("1:%d,%.2f\n", n, f[n]);
	printf("2:%d,%lf\n", n, f[n]);

}
system("pause");
return 0;

}
