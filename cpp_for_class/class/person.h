#pragma once

#ifndef __PERSON_H__
#define __PERSON_H__
#include<iostream>
using namespace std;

namespace output
{
	int op( int a);
}

class cperson
{
	cperson *ano;//ֻ�ܶ����Լ�����ָ�룬���ܰ����Լ����ࣻ
	static cperson bol;//��̬�����Լ�����

public:
	cperson(cperson & copyperson);
	cperson();//Ĭ�Ϲ��캯��
	cperson::cperson(int index,short age,double sal,char *buf);
	~cperson();
	//
	static int m_nd;

	/**��ԱΪ��ǰ�࣬��ָ�룬��̬��ԱΪ��ǰ��*/
	//cperson m_person;
	static cperson m_per;
	cperson *m_pson;
	/**��ԱΪ��ǰ�࣬��ָ�룬��̬��ԱΪ��ǰ��*/


	int m_index;
	char m_name[20];
	short m_age;
	double m_salary;
	int getindex();
	int setindex(int index);
	short getage();
	short setage(int age);
	char *getname();
	int setname(char name[]);
	double getsalary();
	double setsalary(double sala);
	static void outputinfo() ;
	//static void outputinfo() const;//��̬��Ա��������ʹ��const�ؼ���
	void otptinfo(int data = m_nd)
	{
		cout << data << endl;
	}
	/*void otptpage(int dta = m_age)
	{
		cout << dta << endl;
	}*/
private:

};

#endif