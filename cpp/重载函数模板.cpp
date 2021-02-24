
/**有问题*/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
using namespace std;

template<class Type>
Type min(Type &a, Type &b)//定义函数模板
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
char min(char a, char b)//重载函数模板
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