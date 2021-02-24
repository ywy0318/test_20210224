#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
using namespace std;
const double PI=3.14;
class cfigure
{
public:
	cfigure();
	~cfigure();
	virtual double getarea() = 0;
private:

};

cfigure::cfigure()
{
}

cfigure::~cfigure()
{
}

class ccircle:public cfigure
{
public:
	ccircle();
	ccircle(double dr);
	~ccircle();
	double m_dradius;
	double getarea();

	

private:

};

ccircle::ccircle()
{
	
}
ccircle::ccircle(double dr)
{
	m_dradius = dr;
}
double ccircle::getarea()
{
	return m_dradius*m_dradius*PI;
}
ccircle::~ccircle()
{
}
class crect:public cfigure
{
public:
	crect();
	crect(double m_width, double m_length);
	~crect();
	double width;
	double length;
	double getarea();

private:

};

crect::crect()
{
}
crect::crect(double m_width, double m_length)
{
	width = m_width;
	length = m_length;

}
crect::~crect()
{
}
double crect::getarea()
{
	return length*width;
}

int main()
{
	//cfigure cf0;
	cfigure *cf1;
	cf1 = new crect(4.0, 5.0);
	cout << cf1->getarea() << endl;
	cfigure *cf2;
	cf2 = new ccircle(1.0);
	cout << cf2->getarea() << endl;
	delete cf1, cf2;

	system("pause");
	return 0;
}