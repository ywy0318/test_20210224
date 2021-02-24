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
	int id;
	char name[20];
	virtual void  outputname() = 0;
private:

};
cempl::cempl()
{
}
cempl::~cempl()
{
}

class work:public cempl
{
public:
	work();
	~work();
	void outputname();

private:

};

work::work()
{
	strcpy(name, "oper");
}
void work::outputname()
{
	cout << "work name is :" << name << endl;
	//printf("name is %s \n",name);
	//cout << "1oper name is :" << name << endl;

}
work::~work()
{
	
	//strcpy(name,"work");
	//strcpy_s();
}

class oper:public cempl
{
public:
	oper();
	~oper();
	void outputname();
private:

};

oper::oper()
{
	strcpy(name,"osper");
}
void oper::outputname()
{
	cout << "oper name is :"<<"name"<< endl;
}
oper::~oper()
{
}

int main()
{
	cempl *ce;
	ce = new work;
	ce->outputname();
	cout << "***" << endl;
	delete ce;
	ce = NULL;

	cempl *df;
	df = new oper;
	df->outputname();
	cout << "%%%" << endl;
	
	delete df;
	df = NULL;
	system("pause");
	return 0;

	
}