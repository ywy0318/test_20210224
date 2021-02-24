#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
using namespace std;

template<typename T>
T const& max_element(T const*l, unsigned sz)
{
	T const *max_value(l);//´ýÐø
	for (unsigned i = 0; i < sz; ++i)
	{
		if (l[i] > *max_value)
		{
			max_value = &(l[i]);
		}
	}
	return *max_value;
}

/***/
template<typename T0,
	typename T1,
	typename T2,
	typename T3,
	typename T4>
	T2 fun(T1 v1, T3 v3, T4 v4);

int main()
{
	int l[] = { 2,5,8,6,9,10,3 };
	char cl[] = "August";
	double sv2;
	//sv2 = fun(double, int, int)(1, 2, 3);
	//cout << "\tsv2:" << sv2 << endl;
	//cout << max_element<int>(l, 7) << endl;
	//cout << max_element<char>(cl, 6) << endl;
	system("pause");
	return 0;
}