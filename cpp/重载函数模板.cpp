
/**������*/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
using namespace std;

template<class Type>
Type min(Type &a, Type &b)//���庯��ģ��
{
	if (a>b)
	{
		return b;
	}
	else
	{
		return a;
	}
}
char min(char a, char b)//���غ���ģ��
{
	if (strcmp(&a, &b))
	{
		return b;
	}
	else
	{
		return a;
	}
}

int main()
{
	cout << "min: " << min(10, 1) << endl;
	cout << "***" << endl;
	cout << "min ::" << min('a', 'b') << endl;

	system("pause");
	return 0;

}