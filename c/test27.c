/*��ά���鸳ֵ���,�Խ������,����Խ���������*/
/*ģ��������,����ת��*/
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
	int m=0, n=0,i=0;
	int ret;
	int temp;
	int min = 0;
	int max = 0;
	double s, x, y;
	int a[4][4];//7��ѡ�֣�5������
	int b[4][4];
	srand(time(0));
	for (m = 0; m <= 3; m++)
	{
		for (n = 0; n < 4; n++)
		{
			a[m][n] = rand() % 10 + 1;
			//printf("a[%d][%d]is %d\n", m, n, a[m][n]);
			printf("%d   ",a[m][n]);
		}
		printf("\n");
	}
	printf("\n");
	printf("\n");

	/*for (m = 0; m < 7; m++)
	{
		a[m][5] = 0;
			for (n = 0; n < 5; n++)
			{
				a[m][5]+=a[m][n];
			}
	}
	printf("%d ,%d ,%d\n", a[0][5], a[1][5], a[2][5]);
	printf("%d ,%d ,%d ,%d\n", a[3][5], a[4][5], a[5][5], a[6][5]);*/


	//for (m = 0; m <= 3; m++)
	//{
	//	for (n = 0; n < 4; n++)
	//	{
	//		//b[n][m] = a[m][n];
	//		temp = a[m][n];
	//		a[m][n] = a[n][m];
	//		a[n][m] = temp;
	//		//
	//	}
	//	//
	//}



	for (m = 0; m <4; m++)
	{
		for (n = 0; n < 4; n++)
		{
			if (m > n) 
			{

			//b[n][m] = a[m][n];
			temp = a[m][n];
			a[m][n] = a[n][m];
			a[n][m] = temp;
			}
			
			//
		}
		//
	}
	for (m = 0; m < 4; m++)
	{
		for (n = 0; n < 4; n++)
		{
			printf("%d   ", a[m][n]);
		}
		printf("\n");
	}
	//printf("%d ,%d\n",min,max);
	
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