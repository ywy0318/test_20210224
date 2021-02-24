#include<list>
#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include<algorithm>
#include<memory>
#define num 5
using namespace std;
/*
STL容器是同质的,存储的值类型相同;
算法是完成特定任务的处方,迭代器能够用来遍历容器的对象,
与能够遍历数组的指针类似,是广义指针;
仿函数是类似函数的对象,可以是类对象或者函数指针;
配置器是为容器开辟空间的;
*/
template <class T> void print(T& ii,T&jj)
{
	cout<<ii<<endl;
	cout<<jj<<endl;
}

template<class T1,class T2> void print_T1_T2(T1&ii,T2&jj)
{
	cout<<ii<<endl;
	cout<<jj<<endl;
}

void test_stack()
{
	stack<int>st;
	for(int i=0;i<10;i++)
	{
		st.push(i);
	}
	while(!st.empty())
	{
		cout<<st.top()<<" ";
		st.pop();
	}
	cout<<endl;
	return;
}
void test_vector()
{
	vector<string> names(num);
	vector<int> sexs(num);
}
//2.4.9字符串对迭代器的支持
void test_string_2_4_9()
{
	string s("the zip code of the Hondelage in Germany is 38108");
	cout<<"Original:"<<s<<endl;
	string sd(s.begin(),s.end());
	cout<<"Destination:"<<sd<<endl;
	//算法中使用迭代器(仿函数)
	transform(sd.begin(),sd.end(),sd.begin(),toupper);//全部变成大写
	cout<<"Destination(all toupper):"<<sd<<endl;
	string sd1;
	//append()函数中使用迭代器
	sd1.append(sd.begin(),(sd.end()-7));
	cout<<"Destination sd1:"<<sd1<<endl;

	string sd2;
	string::reverse_iterator iter_a;
	string temp="0";
	for(iter_a=sd.rbegin();iter_a!=sd.rend();iter_a++)
	{
		temp=*iter_a;
		sd2.append(temp);
	}
	cout<<"Destination sd2:"<<sd2<<endl;

	sd2.erase(0,15);
	cout<<"Destination sd2.erase(0,15):"<<sd2<<endl;

	string::iterator iter_b=sd2.begin();
	string sd3=string("12345678");
	sd2.insert(sd2.begin(),sd3.begin(),sd3.end());
	cout<<"Destination sd2.insert(Insert 8 chars):"<<sd2<<endl;

	sd2.replace(sd2.begin(),sd2.end(),"this is an example of replace!");
	cout<<"Destination sd2.replace:"<<sd2<<endl;
}
//字符串配置器
void test_string_2_4_10()
{
	string s("abcdef");
	basic_string<char> s1(s.get_allocator());//定义容器s1
	basic_string<char>::allocator_type aT=s1.get_allocator();
	string::size_type se =s1.size();
	cout<<se<<endl;
}
void main()
{
	string str_a("hello,beijing");
	string str_b("i am a programmer");
	int b=50;
	//print(str_a,str_b);
	//print_T1_T2(str_a,b);
	//test_stack();
	test_string_2_4_10();
	cin.get();
}