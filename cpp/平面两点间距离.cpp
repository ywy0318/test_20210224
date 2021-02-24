#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
using namespace std;
class point
{
public:
	point();
	point(double a, double b);
	~point();
	double x;
	double y;
	double getdis(point& p)
	{
		double dx = this->x - p.x;
		double dy = this->y - p.y;
		return sqrt(dx*dx + dy*dy);	
	}

private:

};
point::point(double a, double b)
{
	x = a;
	y = b;
}
point::point()
{
	//this->x = 0;
	//this->y = 0;
	x = 0;
	y = 0;
}

point::~point()
{
}
int main()
{
	
	point p0;
	point p1(3.3, 3.3);
	point p2(6.3,7.3);
	double d1;
	double d2;
	d1 = p1.getdis(p0);
	d2 = p2.getdis(p1);
	cout << d1 << " : " << d2 << endl;
	system("pause");
	return 0;
}