/*��ͬ������ʾ�������벻ͨ��*/
/*whileѭ��ע���±����ӵ�λ�ã�����������������������������*/
/*strdup����ָ����ԣ�����������������������������*/
/*(*p��ʾ��ʱ��ʹ��%c�Ϳ�����ʾ��)*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<windows.h>
#include<dos.h>
#include<conio.h>
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
	int m = 0, n;
	int ret;
	int min;
	char st[30] = "ABCDABCDFGGGFGFGG";// ;
	char a[10] = "ABCD";
	char b[10] = "FGG";
	char *p, *s;
	//gets(st);
	//a = st[2];
	_clrsrc();//��������
	highvideo();//���ú����ַ��Ը�����ʾ
	gotoxy(10,1);//������ƶ���ָ��λ��;(0,0)Ϊ���Ͻ�
	_cprintf("highvideo");//��ʽ���������Ļ

	lowvideo();//���ú����ַ��Ե�����ʾ
	gotoxy(10, 10);
	_cprintf("highvideo");

	normvideo();//���ú����ַ�������ʾ
	gotoxy(10, 20);
	_cprintf("highvideo");

	p = strspn(st, a);/*��st���ҵ���һ��������a�ַ����е��ַ�λ��,
					  ���ص�һ����ƥ����±�*/
	s = strstr(st, b);/*��st��Ѱ��b�ַ�����λ�ã����ظ�λ�õ�ָ��*/

	//printf("2:%d,%p,%c\n", p, s, *s);

	//printf("0��%c,%p\n", a, &a);
	//printf("1:%s\n", st);

	//p = _strdup(st);//char *strdup(char *st) �Ȱ����ַ����������ڴ��з���ռ䡣
	//���ַ���st�����ݸ��Ƶ��ÿռ���
	//_strlwr(st);//��д��Сд
	//printf("2:%s\n", p);
	//printf("3:%p,%p,%c\n", p, st, *p);
	//printf("4:%p,%p,%c,%c\n", p, st, *p, *st);
	//printf("5:%p,%p,%c,%c\n", p + 1, st + 1, *(p + 1), *(st + 1));
	while (st[m] != '\0')
	{

		st[m] -= 32;
		m++;
		//m += 1;
	}
	//printf("3:%s\n", st);
	m = 0;
	while (st[m] != '\0')
	{

		st[m] += 32;
		m += 1;
	}
	//printf("4:%s\n", st);

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