/*��ά���鸳ֵ���*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<windows.h>
#include<dos.h>
//#include<bios.h>
void isprime_self(int m)
{
	int i = 2;
	for (i = 2; i < m / 2; m++)
	{
		if (m%i == 0)
		{
			printf("%d,NO!", i);
			//break;
			return 0;
		}


	}

}
int cifang(int m, int n)
{
	int i = 1;
	int sum = 1;
	for (i = 1; i <= n; i++)
	{
		sum = sum*m;
	}
	return sum;
}



int main()
{
	int m = 0, n = 0, i = 0;
	int ret;
	int min = 0;
	double s, x, y;
	int f[30], g[20];
	int flag = 0;
	/*int a[3][3];*/
	srand(time(0));
	//for (i = 0; i < 10; )
	//{
	//	ret = rand() % 10 + 1;
	//	g[i] = ret;
	//	for (m = 0; m < i; m++)
	//	{
	//		if (f[m] == ret)
	//		{
	//			flag = 1;
	//			//continue;
	//			break;
	//		}
	//	}
	//	if (flag == 0)
	//	{
	//		f[i] = ret;
	//		i++;
	//	}
	//	flag = 0;

	//}
	while (1)
	{
		ret = rand() % 10 + 1;
		g[i] = ret;
		for (m = 0; m < i; m++)
		{
			if (f[m] == ret)
			{
				flag = 1; break;
			}
		}
		if (flag == 0)
		{
			f[i] = ret;
			i += 1;
		}
		flag = 0;
		if (i == 10)
		{
			break;
		}
	}
	printf("min\n");
	for (n = 0; n < 10; n++)
	{
		printf("%d,%d\n", n, f[n]);

	}
	printf("miin\n");
	for (n = 0; n < 20; n++)
	{
		printf("%d,%d\n", n, g[n]);

	}

	/*for (m = 0; m <= 2; m++)
	{
	for (n = 0; n < 3; n++)
	{
	a[m][n] = rand() % 9 + 1;
	printf("a[%d][%d]is %d\n", m, n, a[m][n]);
	}
	}
	for (m = 0; m <= 2; m++)
	{
	for (n = 0; n < 3; n++)
	{
	min += a[m][n];
	}
	}*/


	//printf("%d\n", min);

	//time_t Time, end;//����TimeΪtime_t����
	//struct tm *t, *gt;//����ָ��tΪtm�ṹ����
	//Time = time(NULL);//��ȡ��ǰʱ����Ϣ
	//time(&Time);
	//printf("\n time is :%s\n",ctime(&Time));//��ʱ�������ת��Ϊ�ַ���
	//Sleep(1000);
	//end = time(NULL);


	//min = biosmemory();
	//printf("\n:%d KB\n",min);
	//printf("run time is :%f(s)\n", difftime(end, Time));
	//����difftime�����������Time��end��������ʱ��

	//int i = 0;
	//
	//m = rand() % 5 + 2;
	//n = rand() % 5 + 2;
	//printf("%d\n", m);
	//printf("%d\n", n);
	//isprime_self(m);
	//s = sqrt(5);
	//printf("%lf\n", sqrt(4.0));
	//printf("%lf\n", sqrt(5));
	//y = modf(s, &x);
	//printf("%lf\n", x);
	//printf("%lf\n", y);
	//for (i = 0; i < 5; i++)
	//{
	//	ret = cifang(m, n + i);
	//	printf("%d\n", ret);
	//}
	system("pause");
	return 0;

}