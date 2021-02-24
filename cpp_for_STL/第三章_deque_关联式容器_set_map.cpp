/*
3.5序列式容器--deque(双端队列)类模板
"deque"--double-ended queue
模板类deque提供了对序列随机访问的功能,可以实现在序列两端进行快速插入和删除操作的功能,
并可以在需要时修改自身大小;容器deque是典型的双端队列,完成了标准C++数据结构中队列的所有功能;

容器deque采用动态数组来管理序列中的元素,提供随机存取,和vector具有几乎类似的接口;
模板类(容器)deque的最重要特征是在deque两端放置元素和删除元素时高效的,原因在于deque型序列
开放了序列的两端,即头尾均开放,可以实现在序列两端进行快速的插入和删除;当需要向序列
两端频繁地插入或删除数据元素时,最佳的容器为deque;

作为动态数组形式,容器deque在具有其优势的同时,必然存在其局限性;在deque型队列中间
插入元素是非常费时费力的,必须移动其他元素;

3.5.1容器deque和容器vctor的对比
容器deque和vector相比,具有诸多优越之处
1.>deque可以在两端迅速插入和删除元素,而vector只提供了成员函数push_back和pop_back();
2.>存取元素时,容器deque会稍慢一些;
3.>容器deque的迭代器指针是智能型指针;
4.>在内存区块受限的系统中,deque型容器可以包含更多元素,因为deque型容器使用
多块内存;
5.>容器deque不支持对容器和内存重分配时机的控制;
6.>deque的内存区块不使用时,会被释放;
7.>在序列中间插入和删除元素时,deque的速度很慢,需要移动相关的所有元素;
8.>容器deque的迭代器属于随机存取迭代器;

构造函数:
explicit deque(const A& al=A());
explicit deque(size_type n ,const T& v=T(),const A&a1=A());
deque(const deque&X);
deque(const_iterator first,const_iterator last,const A&a1=A());

deque<typename T>name;
deque<typename T>name(size);
deque<typename T>name(size,value);
deque<typename T>name(elsedeque);
deque<typename T>name(elsedeque.first(),elsedeque.last());

容量:
resize(size_type n,Tx=T());
max_size();
size();
3.5.3 deque容器基础成员函数
1.赋值
deque容器提供了两个数据成员函数push_front和push_back()用于
把新元素插入deque对象中;push_front用于在容器的头部插入新元素;
push_back()用于在容器的尾部插入新元素;
pop_front()和pop_back()分别用于获取容器的头,尾两个元素;
deque容器还提供了运算符[]'
const_reference operator[](size_type pos) const;
reference operator[](size_type pos);

2.迭代器相关函数
1.>begin,rbegin,end,rend;//返回值均为迭代器型
2.>back,front;//返回值为引用

const_iterator begin() const;
iterator begin();
const_reverse_iterator rbegin() const;
reverse_iterator rbegin();
const_iterator end() const;
iterator end();
const_reference back() const;
reference front();
const_reference front() const;
3.>判断迭代器是否为空
deque型容器提供了成员函数empty();如果容器为空,函数empty()返回值为真;
bool empty() const;
4.>元素的访问
deque型容器提供了用于随机访问容器中元素的成员函数at()
const_reference at(size_type pos) const;
reference at(size_type pos);

5.>deque序列的元素值重置技术
容器模板deque提供了函数assign(),函数assign()可以方便地重置deque中某个元素的数值;
void assign(const_iterator first,const_iterator last);
void assign(size_type n,const T&x=T());

3.5.4deque高级编程
Template <class T,class Allocator> void swap(deque<T,Allocator>& x,deque<T,Allocator>& y);
swap()既可以作为deque的成员函数来使用,还可以作为通用算法使用,两者功能一致;

3.6关联式容器概述
关联式容器由二叉树实作出来;在二叉树中,每个元素都有一个父节点和两个子节点;左子数的所有
元素都比自己小,右子树的所有元素都比自己大;关联式容器的差别在于元素的类型以及处理重复
元素的方式;

关联式容器的另一个优点:提供了对元素的快速访问,但是却不能实现任意位置的操作;
主要的关联式容器包括:set,multiset,map,multimap;
set可以视为一种特殊的map,其元素的值即键值;

set是一种随机存取的容器,其关键词和数据文件时同一个值;
set对象中的所有元素必须具有唯一值,即不能包含重复的元素;
set对象可以是程序按照次序来存储一组数值,在一个集合中元素
既作为被存储的数据有作为数据的关键值;集合的本质就是一个有序的排列;
multiset 是另一种类型的容器,其关键词和数据元素时同样的值;
与set不同的是,可以包含重复的元素;
multiset对象可以使程序按照次序存储一组数值;

map是一种关联数组容器,包含成对数据的容器,一个值是实际数据值,另一个值是
用来寻找数据的关键值,一个特定的关键词只能与一个元素相联系;
map是排序结构体,键值是独一无二的;
事实上,map的内部结构和set是一样的;set可以认为是一种特殊的map,其键值和实际值是同一个;

multimap是一种允许出现重复关键值的关联数组容器;与map对象不同,
一个关键词可以和多个元素相联系,multimap允许键值重复;

集合(set)型容器能顺序存储一组值;在一个集合中,集合元素既能充当存储的数据,又能充当数据的关键码;
集合更像一个有序链表,元素以升序的顺序存储;

template<class Key ,class Traits=less<Key>,class Allocator=allocator<Key>> class set;
参数Key是存储在集合中元素的数据类型;
参数Traits是用于实现集合内部排序的仿函数,默认为less<Key>;
参数Allocator代表集合的内存配置器,负责内存的分配和销毁;

explicit set(const Traits& _Comp);
explicit set(const Traits& _Comp,const Allocator& _A1);
set(const _set& _Right);

template<class InputIterator> set(InputIterator _First,InputIterator _Last);
template<class InputIterator> set(InputIterator _First,InputIterator _Last,const Traits& _Comp);
template<class InputIterator> set(InputIterator _First,InputIterator _Last,const Traits& _Comp,const Allocator& _A1);

实现排序准则时,有两种实现形式;第一:在模板中以参数形式实现;第二,以构造函数参数定义;
1.>std::set<int,std::greater<int>> s1;//第一种形式实现排序
2.> set<int> s2(less<int>());//第二种形式实现排序规则

3.7.2 set和multiset的容量,搜寻和统计
size_type size() const;
bool empty() const;
size_type max_size() const;
size_type count(const Key& _Key) const;
iterator find(const Key&_key) const;//返回键值为Key的元素的位置,函数返回值是迭代器类型
const_iterator find(const Key&_key) const;

const_iterator lower_bound(const Key&_key) const;//返回值类型是迭代器类型,该迭代器指向集合中键值大于等于参数Key的第一个元素;
iterator lower_bound(const Key&_key) const;

const_iterator upper_bound(const Key&_key) const;
iterator upper_bound(const Key&_key) const;

pair < const_iterator,const_iterator> equal_range(const Key&_key) const;
pair < iterator,iterator> equal_range(const Key&_key) const;
返回值类型是迭代器对(pair),该迭代器对(pair)的两个迭代器分别指向集合中键值大于并等于参数key的第一个元素
和集合中键值大于参数Key的第一个元素;

set和multiset无法调用变动性算法,不能使用remove()算法,
要移除元素只能使用他们自己的成员函数;

第一次使用了算法distance(),用于计算容器中两个元素的距离;
函数key_comp()用于键值比较,函数value_comp()用于实际值比较;
key_compare key_comp() const;//key_compare决定了集合中元素的排列顺序;
通过返回值的测试，可以确定序列排序形式;
value_compare value_comp() const;
---------------------------
关联式容器---map/multimap
template<class Key,class T,class Compare=less<Key>,class Allocator=allocator<pair<const Key,T>>> class map;
template<class Key,class T,class Compare=less<Key>,class Allocator=allocator<pair<const Key,T>>> class multimap;

key,T必须具备可赋值(assignable)和可复制(copyable)的性质,由于容器内部要排序,所以key必须是可以比较的(comparable);

4.元素大小比较
1.>键值比较
通过函数key_comp可以进行键值的比较,返回类型为key_comp,key_comp决定了map中元素的排列顺序;
key_compare key_comp() const;

5.获取内存分配器
函数get_allocate()用于返回map或者multimap的内存配置器,内存配置器类似指针的首地址,
用于指明对象的初始存储位置;
Allocator get_allocator() const;
函数只能读取内存分配器,不能改变内存分配器,即不能改变容器变量所存储的位置量;

7.通常数组可作为STL容器
string可以被视为容器,内元素均为字符;通常数组不是类,也不可能提供成员函数,但是可以通过普通指针,使用STL的算法
实现对普通数组的操作;

3.9 特殊容器用法
STL提供了部分比较特殊的容器,并涉及部分数据结构的算法,这些容器模板主要包括:位段类模板,
堆栈类模板,队列类模板和优先队列模板;


3.9.1 bitset类模板
bitset创造一个内含位或布尔值且大小固定的数组(array);
当需要管理各种标识,并且需要以标识的任意组合表现变量时,就可以使用bitset类模板;
在C/C++中,通常使用型别long来作为bits array,在通过&，！，~等位操作符,操作各个位;
bitset类的有点在于可容纳任意个数的位,并提供各项操作;
将bitset作为0和1组成的序列,进行读写;

对于既定的bitset变量或对象,其内位的个数是不能改变的;bitset类中变量或对象的位的数量
是由模板参数决定的;如果需要使用可变长度的容器,可考虑使用模板vector<bool>;
模板参数并不是一个型别,而是一个无符号型整数;

在对bitset型对象进行比较和组合时,两个对象或多个对象的位个数必须相同;
类模板bitset的构造函数包括以下形式:
bitset();
bitset(unsigned long val);//位段的构造函数,该数值的二进制形式对应的位为1;
explicit bitset(const string& str,size_t pos=0,size_t n=-1);//位段的构造函数


3.9.2 stack类模板
类模板stack(栈)(后进先出,LIFO)或者栈对象;
push()将任意数量的元素入栈(stack)中,pop()函数依次反序出栈;

namespace std{ template<class T,class Container=deque<T>>class stack;}

第一个template参数代表元素类型;默认第二个template参数用来定义stack内部存放元素所用的实际容器;
默认采用deque;采用deque(没有选择vector)的目的主要是因为deque移除元素时会释放内存,
并不必在重新分配时复制所有元素;

栈stack将各项操作转化为内部容器的对应调用,实际上可以使用任何列式容器(vector,list)
支持stack,并支持back(),push_back(),pop_back()
std::stack<int,std::vector<int>> sv;

*/
#include<iostream>
#include<bitset>
#include<deque>
#include<algorithm>
#include<set>
#include<map>
using namespace std;
typedef pair<int,double> customPair;
void print_map(map<int,double>&m)
{
	map<int,double>::iterator it_1;
	for(it_1=m.begin();it_1!=m.end();it_1++)
	{
		customPair p_1=(pair<int,double>)(*it_1);
		cout<<p_1.first<<",";
		cout<<p_1.second<<"; "<<endl;
		//cout<<std::fixed<<cout.precision(2)<<p_1.second<<"; "<<endl;
	}
}
void print_multimap(multimap<int,double>&m)
{
	multimap<int,double>::iterator it_1;
	for(it_1=m.begin();it_1!=m.end();it_1++)
	{
		customPair p_1=(pair<int,double>)(*it_1);
		cout<<p_1.first<<",";
		cout<<p_1.second<<"; "<<endl;
		//cout<<std::fixed<<cout.precision(2)<<p_1.second<<"; "<<endl;
	}
}
void print_greater_map(map<int,double,greater<int>>& m)
{
	map<int,double,greater<int>>::iterator it_1;
	for(it_1=m.begin();it_1!=m.end();it_1++)
	{
		customPair p_1=(pair<int,double>)(*it_1);
		cout<<p_1.first<<",";
		cout<<std::fixed<<cout.precision(2)<<p_1.second<<"; "<<endl;
	}
}
void print_bit_set( bitset<16>& b)
{
	int i=0;
	int bsize=b.size();
	for(int i=0;i<bsize;i++)
	{
		cout<<b[i];
	}
	cout<<endl;
	//cout<<"   :"<<"b.size()"<<bsize<<endl;
}
void print_set(set<int>&s)
{
	set<int>::iterator it_1;
	for(it_1=s.begin();it_1!=s.end();it_1++)
	{
		cout<<" "<<*it_1<<",";
	}
	cout<<endl;
}
void print_multiset(multiset<int> &s)
{
	multiset<int>::iterator it_1;
	for(it_1=s.begin();it_1!=s.end();it_1++)
	{
		cout<<" "<<*it_1<<",";
	}
	cout<<endl;
}
void print_int(int &ele)
{
	cout<<ele<<" ";
}
void print_double(double &ele)
{
	cout.width(5);
	cout.precision(1);
	cout<<std::fixed<<ele<<" ";
}
void test_deque_size()
{
	deque<int> deque_1;
	deque<int> deque_2(5);
	deque<int> deque_3(10,2),deque_31(10,3);
	deque<int> deque_4(deque_3);
	deque<int> deque_5(deque_31.begin(),deque_31.end());
	cout<<"deque_1:"<<endl;
	for_each(deque_1.begin(),deque_1.end(),print_int);
	cout<<endl;

	cout<<"deque_2:"<<endl;
	for_each(deque_2.begin(),deque_2.end(),print_int);
	cout<<endl;

	cout<<"deque_3:"<<endl;
	for_each(deque_3.begin(),deque_3.end(),print_int);
	cout<<endl;

	cout<<"deque_31:"<<endl;
	for_each(deque_31.begin(),deque_31.end(),print_int);
	cout<<endl;

	cout<<"deque_4:"<<endl;
	for_each(deque_4.begin(),deque_4.end(),print_int);
	cout<<endl;

	cout<<"deque_5:"<<endl;
	for_each(deque_5.begin(),deque_5.end(),print_int);
	cout<<endl;

	cout<<"the size of deque_2:"<<deque_2.size()<<endl;
	cout<<"the maxsize of deque_2: "<<deque_2.max_size()<<endl;

	deque_31.resize(5,'A');
	cout<<"deque_31:"<<endl;
	for_each(deque_31.begin(),deque_31.end(),print_int);
	cout<<endl;

	deque_31.resize(7,0);
	cout<<"deque_31:"<<endl;
	for_each(deque_31.begin(),deque_31.end(),print_int);
	cout<<endl;

}
void test_deque_iterator()
{
	deque<double>::iterator iter_1;
	deque<double>::reverse_iterator riter_1;
	deque<double> deque_1,deque_2,deque_3;
	for(int i=0;i<10;i++)
	{
		deque_1.push_front(90+i/10.0);
	}
	cout<<"all the element deque_1:"<<endl;
	for_each(deque_1.begin(),deque_1.end(),print_double);
	cout<<endl;
	iter_1=deque_1.begin();
	double begin=*iter_1;
	iter_1=deque_1.end();
	double end=*(--iter_1);

	riter_1=deque_1.rbegin();
	double rbegin=*(riter_1);
	riter_1=deque_1.rend();
	double rend=*(--riter_1);
	double front=deque_1.front();
	double back=deque_1.back();
	cout<<"begin:"<<begin<<",end:"<<end<<",front:"<<front<<",back:"<<back<<endl;
	cout<<"reverse begin:"<<rbegin<<"reverse end:"<<rend<<endl;
	if(deque_1.empty())
	{
		cout<<"deque_1.empty()"<<endl;
	}
	else
	{
		cout<<"deque_1.size"<<deque_1.size()<<endl;
	}
	cout<<"deque_1.at(5):"<<deque_1.at(5)<<endl;
	deque_2.assign(6,0);
	deque_3.assign(deque_1.begin(),deque_1.end());

	cout<<"all the element deque_2:"<<endl;
	for_each(deque_2.begin(),deque_2.end(),print_double);
	cout<<endl;

	cout<<"all the element deque_3:"<<endl;
	for_each(deque_3.begin(),deque_3.end(),print_double);
	cout<<endl;
}
void test_insert_clear_erase_swap()
{
	deque<double> deque_1,deque_2,deque_3;
	for(int i=0;i<10;i++)
	{
		deque_1.push_front(90+i/10.0);
	}
	for(int i=0;i<10;i++)
	{
		deque_2.push_front(80+i/10.0);
	}
	cout<<"all the element deque_1:"<<endl;
	for_each(deque_1.begin(),deque_1.end(),print_double);
	cout<<endl;

	cout<<"all the element deque_2:"<<endl;
	for_each(deque_2.begin(),deque_2.end(),print_double);
	cout<<endl;

	deque_1.swap(deque_2);
	cout<<"deque_1.swap(deque_2)"<<endl;
	cout<<"----"<<endl;
	cout<<"all the element deque_1:"<<endl;
	for_each(deque_1.begin(),deque_1.end(),print_double);
	cout<<endl;

	cout<<"all the element deque_2:"<<endl;
	for_each(deque_2.begin(),deque_2.end(),print_double);
	cout<<endl;

	deque_1.insert(deque_1.begin(),-1.0);
	deque_1.insert(deque_1.end(),-1.0);
	deque_1.insert(deque_1.begin()+6,-0.0);

	cout<<"deque_1.insert"<<endl;
	cout<<"----"<<endl;
	cout<<"all the element deque_1:"<<endl;
	for_each(deque_1.begin(),deque_1.end(),print_double);
	cout<<endl;

	deque_1.erase(deque_1.begin()+1);
	deque_1.erase(deque_1.begin()+10);
	cout<<"deque_1.erase"<<endl;
	cout<<"----"<<endl;
	cout<<"all the element deque_1:"<<endl;
	for_each(deque_1.begin(),deque_1.end(),print_double);
	cout<<endl;

	deque_2.clear();
	cout<<"deque_2.clear"<<endl;
	cout<<"----"<<endl;
	cout<<"all the element deque_2:"<<endl;
	for_each(deque_2.begin(),deque_2.end(),print_double);
	cout<<endl;
	//使用find算法
	deque<double>::iterator iter_1=find(deque_1.begin(),deque_1.end(),80.5);
	int temp=(iter_1-deque_1.begin());
	cout<<"find 80.5 in deque_1,its index:"<<temp<<", "<<endl;
}
void test_set_multiset()
{
	set<int> set_1;
	set_1.insert(10);
	set_1.insert(15);
	set_1.insert(25);
	set_1.insert(20);
	set_1.insert(30);
	set_1.insert(33);
	set_1.insert(5);
	set_1.insert(20);
	cout<<"set_1"<<endl;
	print_set(set_1);

	//set<int> set_2(less<int>());
	set<int> set_2;
	set_2.insert(10);
	set_2.insert(13);
	set_2.insert(11);
	set_2.insert(19);
	set_2.insert(17);
	set_2.insert(21);
	cout<<"set_2"<<endl;
	print_set(set_2);

	set<int>::allocator_type set_1_alloc;
	set_1_alloc=set_1.get_allocator();
	set<int> set_3(less<int>(),set_1_alloc);
	set_3.insert(1);
	set_3.insert(5);
	set_3.insert(2);
	cout<<"set_3"<<endl;
	print_set(set_3);
	set<int> set_4(set_1);
	cout<<"set_4"<<endl;
	print_set(set_4);

	multiset<int> multiset_1;

	multiset_1.insert(10);
	multiset_1.insert(15);
	multiset_1.insert(25);
	multiset_1.insert(20);
	multiset_1.insert(30);
	multiset_1.insert(33);
	multiset_1.insert(5);
	multiset_1.insert(20);
	cout<<"multiset_1"<<endl;
	print_multiset(multiset_1);
}
void test_set_fing_lower_bound()
{
	typedef set<int> SET;
	typedef multiset<int> MSET;

	SET set_1;
	MSET mset_2;

	SET::iterator iter_1;
	MSET::iterator m_iter;
	pair<SET::iterator,SET::iterator> p_1;
	pair<MSET::iterator,MSET::iterator> mp_1;

	set_1.insert(10);
	set_1.insert(15);
	set_1.insert(21);
	set_1.insert(17);

	mset_2.insert(11);
	mset_2.insert(16);
	mset_2.insert(20);
	mset_2.insert(18);
	mset_2.insert(20);

	cout<<"the set_1 is below:"<<endl;
	print_set(set_1);
	//for_each(set_1.begin(),set_1.end(),print_int);
	cout<<endl;

	cout<<"the mset_2 is below:"<<endl;
	print_multiset(mset_2);
	//for_each(mset_2.begin(),mset_2.end(),print_int);
	cout<<endl;

	cout<<"the size of set_1:"<<set_1.size()<<endl;
	cout<<"the size of mset_2:"<<mset_2.size()<<endl;

	cout<<"the max_size of set_1:"<<set_1.max_size()<<endl;
	cout<<"the max_size of mset_2:"<<mset_2.max_size()<<endl;

	cout<<"the count of 10 in set_1:"<<set_1.count(10)<<endl;
	cout<<"the count of 20 in mset_2:"<<mset_2.count(20)<<endl;

	cout<<"the element with a key 21 is "<<*(set_1.find(21))<<endl;
	cout<<"the element with a key 18 is  "<<*(mset_2.find(18))<<endl;

	if(set_1.lower_bound(15)==set_1.end())
	{
		cout<<"the element with set_1 doesnot  lower_bound exist"<<endl;
	}
	else
	{
		cout<<"the element with 15 set_1 is:"<<*(set_1.lower_bound(15))<<endl;
	}

	if(mset_2.lower_bound(16)==mset_2.end())
	{
		cout<<"the element with mset_2 doesnot lower_bound exist"<<endl;
	}
	else
	{
		cout<<"the element with 15 mset_2 is:"<<*(mset_2.lower_bound(16))<<endl;
	}
	cout<<"------"<<endl;

	if(set_1.upper_bound(15)==set_1.end())
	{
		cout<<"the element with set_1 doesnot upper_bound  exist"<<endl;
	}
	else
	{
		cout<<"the element with 15 set_1 is:"<<*(set_1.upper_bound(15))<<endl;
	}

	if(mset_2.upper_bound(16)==mset_2.end())
	{
		cout<<"the element with mset_2 doesnot upper_bound exist"<<endl;
	}
	else
	{
		cout<<"the element with 15 mset_2 is:"<<*(mset_2.upper_bound(16))<<endl;
	}
	cout<<"------"<<endl;

	//待续-----------------
	//if(set_1.equal_range(15)==set_1.end())
	//{
	//	cout<<"the element with set_1 doesnot equal_range exist"<<endl;
	//}
	//else
	//{
	//	cout<<"the element with 15 set_1 equal_range  is:"<<*(set_1.upper_bound(15))<<endl;
	//	cout<<"the element with 15 set_1 equal_range  is:"<<*(set_1.upper_bound(15))<<endl;
	//}

	//if(mset_2.equal_range(16)==mset_2.end())
	//{
	//	cout<<"the element with mset_2 equal_range  doesnot exist"<<endl;
	//}
	//else
	//{
	//	cout<<"the element with 15 mset_2  equal_range is:"<<*(mset_2.upper_bound(16))<<endl;
	//	cout<<"the element with 15 set_1 equal_range  is:"<<*(set_1.upper_bound(15))<<endl;
	//}
}
void test_set_swap_insert_erase_compare()
{
	set<int> set_1,set_2;
	multiset<int> mset_1;

	pair<set<int>::iterator,bool> pair_1;

	set<int,less<int>>::key_compare kc_1=set_1.key_comp();

	//multiset<int,greater<int>>::key_compare kc_2=mset_1.key_comp();

	mset_1.insert(1);
	mset_1.insert(2);
	mset_1.insert(3);
	mset_1.insert(4);

	set_1.insert(11);
	set_1.insert(21);
	set_1.insert(17);
	set_1.insert(19);
	set_1.insert(9);
	set_1.insert(13);
	cout<<"set_1"<<endl;
	print_set(set_1);
	set_2=set_1;
	set_2.insert(31);
	set_2.insert(24);
	cout<<"set_2"<<endl;
	print_set(set_2);

	set_1.swap(set_2);
	cout<<"---"<<endl;
	cout<<"set_1"<<endl;
	print_set(set_1);

	cout<<"set_2"<<endl;
	print_set(set_2);

	set<int>::iterator iter;
	set<int>::reverse_iterator riter;
	cout<<"the set_1.begin() "<<*(set_1.begin())<<endl;
	cout<<"the set_1.begin() "<<*(--set_1.end())<<endl;
	cout<<"the set_1.begin() "<<*(set_1.rbegin())<<endl;
	cout<<"the set_1.begin() "<<*(--set_1.rend())<<endl;

	cout<<"----set_1.insert---"<<endl;
	pair_1=set_1.insert(12);
	if(pair_1.second==true)
	{
		cout<<"insert successfully"<<endl;
		cout<<distance(set_1.begin(),pair_1.first)+1<<endl;
	}
	else
	{
		cout<<"insert failed,already exist"<<endl;
		cout<<distance(set_1.begin(),pair_1.first)+1<<endl;
	}
	cout<<"set_1"<<endl;
	print_set(set_1);
	pair_1=set_1.insert(17);
	if(pair_1.second==true)
	{
		cout<<"insert successfully"<<endl;
	}
	else
	{
		cout<<"insert failed,already exist"<<endl;
	}
	cout<<"----"<<endl;
	set_2.insert(25);

	cout<<"set_2"<<endl;
	print_set(set_2);
	
	set_2.erase(25);
	cout<<"set_2_after_erase:"<<endl;
	print_set(set_2);

	cout<<"key_compare:"<<endl;
	if(kc_1(2,3)==true)
	{
		cout<<"the function object of set_1 return true"<<endl;
	}
	else
	{
		cout<<"the function object of set_1 return false"<<endl;
	}
	//待续有问题-----------
	//if(kc_2(2,3)==true)
	//{
	//	cout<<"the function object of mset_1 return true"<<endl;
	//}
	//else
	//{
	//	cout<<"the function object of mset_1 return false"<<endl;
	//}

	cout<<"set_2.erase(++set_2.begin(),(--set_2.end())"<<endl;
	set_2.erase((++set_2.begin()),(--set_2.end()));
	print_set(set_2);
}
void test_map_insert()
{
	map<int,double>::iterator itm;
	map<int,double,greater<int>>::iterator itm_g;
	multimap<int,double> m_map;
	map<int,double> m_1;
	m_1.insert(customPair(0,2.9));
	m_1.insert(customPair(1,2.1));
	m_1.insert(customPair(2,2.2));
	m_1.insert(customPair(3,2.3));
	m_1.insert(customPair(4,2.4));
	m_1.insert(customPair(21,22.1));
	m_1.insert(customPair(22,22.2));
	m_1.insert(customPair(23,22.3));
	m_1.insert(customPair(24,22.4));
	cout<<"m_1"<<endl;
	cout<<"m_1.size():"<<m_1.size()<<endl;
	cout<<"m_1.max_size():"<<m_1.max_size()<<endl;
	print_map(m_1);

	m_map.insert(customPair(11,12.1));
	m_map.insert(customPair(12,12.2));
	m_map.insert(customPair(13,12.3));
	m_map.insert(customPair(14,12.4));
	m_map.insert(customPair(31,32.1));
	m_map.insert(customPair(32,32.2));
	m_map.insert(customPair(33,32.3));
	m_map.insert(customPair(34,32.4));
	cout<<"m_map"<<endl;
	cout<<"m_map.size():"<<m_map.size()<<endl;
	cout<<"m_map.max_size():"<<m_map.max_size()<<endl;
	print_multimap(m_map);

	cout<<"m_1.begin():"<<(*(m_1.begin())).first<<" "<<(*(m_1.begin())).second<<endl;
	cout<<"m_1.end():"<<(*(--m_1.end())).first<<" "<<(*(--m_1.end())).second<<endl;
	cout<<"m_1.rbegin():"<<(*(m_1.rbegin())).first<<" "<<(*(m_1.rbegin())).second<<endl;
	cout<<"m_1.rend()"<<(*(--m_1.rend())).first<<""<<(*(--m_1.rend())).second<<endl;

	cout<<"m_map.begin():"<<(*(m_map.begin())).first<<(*(m_map.begin())).second<<endl;
	cout<<"m_map.end():"<<(*(--m_map.end())).first<<" "<<(*(--m_map.end())).second<<endl;
	cout<<"m_map.rbegin():"<<(*(m_map.rbegin())).first<<" "<<(*(m_map.rbegin())).second<<endl;
	cout<<"m_map.rend():"<<(*(--m_map.rend())).first<<" "<<(*(--m_map.rend())).second<<endl;

	m_1.erase(0);
	cout<<"---"<<endl;
	print_map(m_1);
}
void test_key_comp()
{
	typedef map<int,double,less<int>> MAP;//true
	typedef multimap<int,double,greater<int>> M_MAP;//false--kc_2(5,4)的时候为true;
	MAP m_1;
	M_MAP m_2;
	MAP::key_compare kc_1=m_1.key_comp();
	M_MAP::key_compare kc_2=m_2.key_comp();
	bool r=kc_1(2,3);
	bool M_r=kc_2(3,4);
	if(r)
	{
		cout<<"kc_1(2,3)返回值为true."<<endl;
	}
	else
	{
		cout<<"kc_1(2,3)返回值为false."<<endl;
	}
	if(M_r)
	{
		cout<<"kc_2(3,4)返回值为true."<<endl;
	}
	else
	{
		cout<<"kc_2(3,4)返回值为false."<<endl;
	}

}
void test_get_allocator()
{
	typedef map<int,double> MAP;
	MAP::allocator_type m_1_alloc;
	MAP::allocator_type m_2_alloc;
	MAP::allocator_type m_3_alloc;
	MAP::allocator_type m_4_alloc;

	MAP m_1,m_2,m_3;
	m_1_alloc=m_1.get_allocator();
	m_2_alloc=m_2.get_allocator();
	m_3_alloc=m_3.get_allocator();
	MAP m_4(less<int>(),m_1_alloc);
	m_4_alloc=m_4.get_allocator();

	if(m_1_alloc==m_4_alloc)
	{
		cout<<"m_1_alloc==m_4_alloc"<<endl;
	}
	else
	{
		cout<<"m_1_alloc!=m_4_alloc"<<endl;
	}

	if(m_1_alloc==m_2_alloc)
	{
		cout<<"m_1_alloc==m_2_alloc"<<endl;
	}
	else
	{
		cout<<"m_1_alloc!=m_2_alloc"<<endl;
	}


}
//STL的算法实现对普通数组的操作
//通常数组可作为STL容器
//待续有问题------
//通过自定义类或者自定义类模板的形式,实现对数组的访问和操作;
void test_STL_array()
{
	int col[]={1,5,7,2,8};
	sort(col,col+5);
	//copy(col,col+5,ostream_iterator<int>(cout,""));
	cout<<endl;
}
void test_bitset()
{
	string str="001111111111111111000";
	bitset<16> b1;
	bitset<16> b2(25);//从右侧补零
	bitset<16> b3(str,2,16);
	print_bit_set(b1);
	print_bit_set(b2);
	print_bit_set(b3);

	cout<<"b1.size():"<<b1.count()<<endl;
	cout<<"b2.size():"<<b2.count()<<endl;
	cout<<"b3.size():"<<b3.count()<<endl;

	cout<<"b1.any():"<<b1.any()<<endl;//判断位段中是否至少包含一个"1"
	cout<<"b2.any():"<<b2.any()<<endl;
	cout<<"b3.any():"<<b3.any()<<endl;

	cout<<"b1.none():"<<b1.none()<<endl;//判断位段中是否全部0
	cout<<"b2.none():"<<b2.none()<<endl;
	cout<<"b3.none():"<<b3.none()<<endl;

	cout<<"b1.test():"<<b1.test(2)<<endl;//判断第2位是1还是0
	cout<<"b2.test():"<<b2.test(2)<<endl;
	cout<<"b3.test():"<<b3.test(2)<<endl;

	cout<<"set(5,1):"<<endl;//设置位
	b1.set(5,1);
	b2.set(5,1);
	b3.set(5,1);
	print_bit_set(b1);
	print_bit_set(b2);
	print_bit_set(b3);
	cout<<"reset(5):"<<endl;
	b1.reset(5);
	b2.reset(5);
	b3.reset(5);
	print_bit_set(b1);
	print_bit_set(b2);
	print_bit_set(b3);

	//转换成字符串
	cout<<"to_string:"<<endl;
	cout<<b1.to_string()<<endl;
	cout<<b2.to_string()<<endl;
	cout<<b3.to_string()<<endl;

	//尾段转换成数值
	cout<<b1.to_ulong()<<endl;
	cout<<b2.to_ulong()<<endl;
	cout<<b3.to_ulong()<<endl;
}

int main()
{
	test_bitset();
	system("pause");
	return 0;
}
