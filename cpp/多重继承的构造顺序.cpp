#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
using namespace std;

class cbycycle
{
public:
	cbycycle();
	~cbycycle();
	int age;
	char name[5];
	char part[20];
	virtual void outputname()
	{
		cout << "cbycycle name is :" << endl;
	}
private:

};

cbycycle::cbycycle()
{
	memset(name, 0, sizeof(name));
	strcpy(name,"LOL");
	cout << "cbycycle construct: "<< name << endl;
}

cbycycle::~cbycycle()
{
}

class cairplane
{
public:
	cairplane();
	~cairplane();

private:

};

cairplane::cairplane()
{
	cout << "cairplane construct" << endl;
}

cairplane::~cairplane()
{
}
class MyClass:public cbycycle
{
public:
	MyClass();
	~MyClass();
	int id;
	void outputname()
	{
		cout << "myclass is name :" << name << endl;
	}
private:

};

MyClass::MyClass()
{
	cout << "myclass construct:" << endl;
}

MyClass::~MyClass()
{
}

class u:public MyClass
{
public:
	u();
	~u();
	int usd;
	void outputname()
	{
		cout << "u is name :" << name << endl;
	}

private:

};

u::u()
{
	cout << "u construct" << endl;
}

u::~u()
{
}
int main()
{
	MyClass my;
	strcpy(my.name, "SD");
	my.outputname();
	

	//strcpy(my.name, "SD");
	cout << "***" << endl;
	u e;
	strcpy(e.name, "EE");
	e.outputname();

	system("pause");
	return 0;
}