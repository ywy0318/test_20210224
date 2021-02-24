/*定义重载成员函数*/

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
using namespace std;

class cempl
{
public:
	cempl();
	~cempl();
	int m_ID;
	char m_name[20];
	char m_depart[20];
	void outputname()
	{
		cout << "cempl::name is:" << m_name << endl;
	}
private:	
};

cempl::cempl()
{
	memset(m_name,0,20);
	memset(m_depart,0,20);
	cout << "cempl():" << endl;
}

cempl::~cempl()
{
	cout << "~cempl():" << endl;
}

class coperator :public cempl
{
public:
	coperator();
	~coperator();
	char password[20];

	bool login()
	{
		cout << "cempl::name is:" << m_name << endl;
		cout << "cempl::m_depart is:" << m_depart << endl;
		//cout << "cempl::name is:" << m_name << endl;
		if ((strcmp(m_name,"MR")==0)&&
			(strcmp(password, "MR") == 0))
		{
			cout << "login success" << endl;
			return true;
		}
		else
		{
			cout << "login success" << endl;
			return false;
		}
	}
	void outputname()
	{
		cout << "coperator::name is:" << m_name << endl;
	}
private:
};

coperator::coperator()
{
	cout << "coperator():" << endl;
}

coperator::~coperator()
{
	cout << "~coperator():" << endl;
}

int main()
{
	coperator cop;
	strcpy(cop.m_name, "MR");
	strcpy(cop.password,"MR");
	cop.login();
	cop.outputname();
	cop.cempl::outputname();
	//while (1);
	system("pause");
	//Sleep(1000*6);
	return 0;
}