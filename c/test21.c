/*BIOS���벻ͨ������������������������*/
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
	int m, n;
	int ret;
	int min;
	double s, x, y;

	long origin, ne;
	origin = biostime(0,0);//����biostime(int cmd,long newtime)��������ȡʱ�ӵĵ�ǰֵ��
	printf("\n��ǰʱ��:%ld\n",origin);
	ne = biostime(1,500);//��cmdΪ1��ʱ������Ϊnewtimeֵ����cmdΪ0,��ȡ��ǰʱ��ֵ
	printf("\n��ǰʱ��:%ld\n", ne);
	//bios��ʱ����ÿ��18.2�������������У���ҹʮ������0��Ȼ�󲻶�����
	//struct date d;//����date�ṹ�����
	//struct time *T��//����time�ṹ�����
	//	getdate(&d);//��ȡϵͳ��ǰ���ڣ�
	//gettime(&T);//��ȡϵͳ��ǰʱ��
	//printf("day is :%d--%d--%d\n", d.da_year, d.da_mon, d.da_day);
	//printf("time is :%d--%d--%d\n", T.ti_hour, T.ti_min, T.ti_sec);
	time_t Time, end;//����TimeΪtime_t����
	struct tm *t, *gt;//����ָ��tΪtm�ṹ����
	Time = time(NULL);//��ȡ��ǰʱ����Ϣ
	Sleep(1000);
	end = time(NULL);
	//printf("run time is :%f(s)\n", difftime(end, Time));
	//����difftime�����������Time��end��������ʱ��
	t = localtime(&Time);//����localtime������ʱ��ֽ�
						 //printf("local time is:%s\n", asctime(t));//����asctime()�������Թ̶���ʽ��ʾʱ��

	gt = gmtime(&Time);//����ǰʱ��ת��Ϊ��������ʱ��
	printf("gelin time is:%s\n", asctime(gt));
	//int i = 0;
	//srand(time(0));
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