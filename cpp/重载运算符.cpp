#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
using namespace std;
class book
{
public:
	int m_page;
	book();
	book(int page)
	{
		m_page = page;
	}


	~book();

	int add(book a)
	{
		return m_page + a.m_page;
	}

	/*book operator+(book b)
	{
		return book(m_page + b.m_page);
	}*/

	book operator+(const int page)
	{
		book bk20;
		bk20.m_page = m_page + page;
		return bk20;
	}
	int  operator =(const int pg)
	{
		m_page = pg;
		return m_page;
	}

	void display()
	{
		cout << m_page << endl;
	}
	
private:
protected:
	

};

book::book()
{
	m_page = 0;
}

book::~book()
{
}
int main()
{
	book bk11,bk13;
	book bk12;
	bk12 = bk11 + 90;
	book bk1(100);
	book bk2(200);
	book tem(0);
	bk13 = 99;
	//tem = bk1 + bk2;
	//tem.display();
	//cout << bk1.add(bk2) << endl;
	bk13.display();
	//bk12.display();
	system("pause");
	return 0;
}