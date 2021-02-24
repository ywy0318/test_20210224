#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
using namespace std;
class bird
{
public:
	bird();
	~bird();
	void flyinsky()
	{
		cout << "bird can fly insky" << endl;
	}
	void breathe()
	{
		cout << "bird can breathe" << endl;
	}

private:

};
bird::bird()
{
}
bird::~bird()
{
}

class fish
{
public:
	fish();
	~fish();
	void swiminsea()
	{
		cout << "fish can swim in sea" << endl;
	}
	void breathe()
	{
		cout << "fish can breathe in sea" << endl;
	}
private:

};

fish::fish()
{
}

fish::~fish()
{
}

//野鸭类、天鹅、海鸥类、信天翁
class waterbird :public bird, public fish
{
public:
	waterbird();
	~waterbird();
	void action()
	{
		cout << "both can swim and fly" << endl;
	}

private:

};

waterbird::waterbird()
{
}

waterbird::~waterbird()
{
}

int main()
{
	waterbird wb;
	wb.flyinsky();
	wb.swiminsea();
	wb.action();
	//
    wb.fish::breathe();
	wb.bird::breathe();
	system("pause");
	return 0;
}