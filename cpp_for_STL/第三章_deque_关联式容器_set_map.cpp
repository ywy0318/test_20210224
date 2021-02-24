/*
3.5����ʽ����--deque(˫�˶���)��ģ��
"deque"--double-ended queue
ģ����deque�ṩ�˶�����������ʵĹ���,����ʵ�����������˽��п��ٲ����ɾ�������Ĺ���,
����������Ҫʱ�޸������С;����deque�ǵ��͵�˫�˶���,����˱�׼C++���ݽṹ�ж��е����й���;

����deque���ö�̬���������������е�Ԫ��,�ṩ�����ȡ,��vector���м������ƵĽӿ�;
ģ����(����)deque������Ҫ��������deque���˷���Ԫ�غ�ɾ��Ԫ��ʱ��Ч��,ԭ������deque������
���������е�����,��ͷβ������,����ʵ�����������˽��п��ٵĲ����ɾ��;����Ҫ������
����Ƶ���ز����ɾ������Ԫ��ʱ,��ѵ�����Ϊdeque;

��Ϊ��̬������ʽ,����deque�ھ��������Ƶ�ͬʱ,��Ȼ�����������;��deque�Ͷ����м�
����Ԫ���Ƿǳ���ʱ������,�����ƶ�����Ԫ��;

3.5.1����deque������vctor�ĶԱ�
����deque��vector���,���������Խ֮��
1.>deque����������Ѹ�ٲ����ɾ��Ԫ��,��vectorֻ�ṩ�˳�Ա����push_back��pop_back();
2.>��ȡԪ��ʱ,����deque������һЩ;
3.>����deque�ĵ�����ָ����������ָ��;
4.>���ڴ��������޵�ϵͳ��,deque���������԰�������Ԫ��,��Ϊdeque������ʹ��
����ڴ�;
5.>����deque��֧�ֶ��������ڴ��ط���ʱ���Ŀ���;
6.>deque���ڴ����鲻ʹ��ʱ,�ᱻ�ͷ�;
7.>�������м�����ɾ��Ԫ��ʱ,deque���ٶȺ���,��Ҫ�ƶ���ص�����Ԫ��;
8.>����deque�ĵ��������������ȡ������;

���캯��:
explicit deque(const A& al=A());
explicit deque(size_type n ,const T& v=T(),const A&a1=A());
deque(const deque&X);
deque(const_iterator first,const_iterator last,const A&a1=A());

deque<typename T>name;
deque<typename T>name(size);
deque<typename T>name(size,value);
deque<typename T>name(elsedeque);
deque<typename T>name(elsedeque.first(),elsedeque.last());

����:
resize(size_type n,Tx=T());
max_size();
size();
3.5.3 deque����������Ա����
1.��ֵ
deque�����ṩ���������ݳ�Ա����push_front��push_back()����
����Ԫ�ز���deque������;push_front������������ͷ��������Ԫ��;
push_back()������������β��������Ԫ��;
pop_front()��pop_back()�ֱ����ڻ�ȡ������ͷ,β����Ԫ��;
deque�������ṩ�������[]'
const_reference operator[](size_type pos) const;
reference operator[](size_type pos);

2.��������غ���
1.>begin,rbegin,end,rend;//����ֵ��Ϊ��������
2.>back,front;//����ֵΪ����

const_iterator begin() const;
iterator begin();
const_reverse_iterator rbegin() const;
reverse_iterator rbegin();
const_iterator end() const;
iterator end();
const_reference back() const;
reference front();
const_reference front() const;
3.>�жϵ������Ƿ�Ϊ��
deque�������ṩ�˳�Ա����empty();�������Ϊ��,����empty()����ֵΪ��;
bool empty() const;
4.>Ԫ�صķ���
deque�������ṩ�������������������Ԫ�صĳ�Ա����at()
const_reference at(size_type pos) const;
reference at(size_type pos);

5.>deque���е�Ԫ��ֵ���ü���
����ģ��deque�ṩ�˺���assign(),����assign()���Է��������deque��ĳ��Ԫ�ص���ֵ;
void assign(const_iterator first,const_iterator last);
void assign(size_type n,const T&x=T());

3.5.4deque�߼����
Template <class T,class Allocator> void swap(deque<T,Allocator>& x,deque<T,Allocator>& y);
swap()�ȿ�����Ϊdeque�ĳ�Ա������ʹ��,��������Ϊͨ���㷨ʹ��,���߹���һ��;

3.6����ʽ��������
����ʽ�����ɶ�����ʵ������;�ڶ�������,ÿ��Ԫ�ض���һ�����ڵ�������ӽڵ�;������������
Ԫ�ض����Լ�С,������������Ԫ�ض����Լ���;����ʽ�����Ĳ������Ԫ�ص������Լ������ظ�
Ԫ�صķ�ʽ;

����ʽ��������һ���ŵ�:�ṩ�˶�Ԫ�صĿ��ٷ���,����ȴ����ʵ������λ�õĲ���;
��Ҫ�Ĺ���ʽ��������:set,multiset,map,multimap;
set������Ϊһ�������map,��Ԫ�ص�ֵ����ֵ;

set��һ�������ȡ������,��ؼ��ʺ������ļ�ʱͬһ��ֵ;
set�����е�����Ԫ�ر������Ψһֵ,�����ܰ����ظ���Ԫ��;
set��������ǳ����մ������洢һ����ֵ,��һ��������Ԫ��
����Ϊ���洢����������Ϊ���ݵĹؼ�ֵ;���ϵı��ʾ���һ�����������;
multiset ����һ�����͵�����,��ؼ��ʺ�����Ԫ��ʱͬ����ֵ;
��set��ͬ����,���԰����ظ���Ԫ��;
multiset�������ʹ�����մ���洢һ����ֵ;

map��һ�ֹ�����������,�����ɶ����ݵ�����,һ��ֵ��ʵ������ֵ,��һ��ֵ��
����Ѱ�����ݵĹؼ�ֵ,һ���ض��Ĺؼ���ֻ����һ��Ԫ������ϵ;
map������ṹ��,��ֵ�Ƕ�һ�޶���;
��ʵ��,map���ڲ��ṹ��set��һ����;set������Ϊ��һ�������map,���ֵ��ʵ��ֵ��ͬһ��;

multimap��һ����������ظ��ؼ�ֵ�Ĺ�����������;��map����ͬ,
һ���ؼ��ʿ��ԺͶ��Ԫ������ϵ,multimap�����ֵ�ظ�;

����(set)��������˳��洢һ��ֵ;��һ��������,����Ԫ�ؼ��ܳ䵱�洢������,���ܳ䵱���ݵĹؼ���;
���ϸ���һ����������,Ԫ���������˳��洢;

template<class Key ,class Traits=less<Key>,class Allocator=allocator<Key>> class set;
����Key�Ǵ洢�ڼ�����Ԫ�ص���������;
����Traits������ʵ�ּ����ڲ�����ķº���,Ĭ��Ϊless<Key>;
����Allocator�����ϵ��ڴ�������,�����ڴ�ķ��������;

explicit set(const Traits& _Comp);
explicit set(const Traits& _Comp,const Allocator& _A1);
set(const _set& _Right);

template<class InputIterator> set(InputIterator _First,InputIterator _Last);
template<class InputIterator> set(InputIterator _First,InputIterator _Last,const Traits& _Comp);
template<class InputIterator> set(InputIterator _First,InputIterator _Last,const Traits& _Comp,const Allocator& _A1);

ʵ������׼��ʱ,������ʵ����ʽ;��һ:��ģ�����Բ�����ʽʵ��;�ڶ�,�Թ��캯����������;
1.>std::set<int,std::greater<int>> s1;//��һ����ʽʵ������
2.> set<int> s2(less<int>());//�ڶ�����ʽʵ���������

3.7.2 set��multiset������,��Ѱ��ͳ��
size_type size() const;
bool empty() const;
size_type max_size() const;
size_type count(const Key& _Key) const;
iterator find(const Key&_key) const;//���ؼ�ֵΪKey��Ԫ�ص�λ��,��������ֵ�ǵ���������
const_iterator find(const Key&_key) const;

const_iterator lower_bound(const Key&_key) const;//����ֵ�����ǵ���������,�õ�����ָ�򼯺��м�ֵ���ڵ��ڲ���Key�ĵ�һ��Ԫ��;
iterator lower_bound(const Key&_key) const;

const_iterator upper_bound(const Key&_key) const;
iterator upper_bound(const Key&_key) const;

pair < const_iterator,const_iterator> equal_range(const Key&_key) const;
pair < iterator,iterator> equal_range(const Key&_key) const;
����ֵ�����ǵ�������(pair),�õ�������(pair)�������������ֱ�ָ�򼯺��м�ֵ���ڲ����ڲ���key�ĵ�һ��Ԫ��
�ͼ����м�ֵ���ڲ���Key�ĵ�һ��Ԫ��;

set��multiset�޷����ñ䶯���㷨,����ʹ��remove()�㷨,
Ҫ�Ƴ�Ԫ��ֻ��ʹ�������Լ��ĳ�Ա����;

��һ��ʹ�����㷨distance(),���ڼ�������������Ԫ�صľ���;
����key_comp()���ڼ�ֵ�Ƚ�,����value_comp()����ʵ��ֵ�Ƚ�;
key_compare key_comp() const;//key_compare�����˼�����Ԫ�ص�����˳��;
ͨ������ֵ�Ĳ��ԣ�����ȷ������������ʽ;
value_compare value_comp() const;
---------------------------
����ʽ����---map/multimap
template<class Key,class T,class Compare=less<Key>,class Allocator=allocator<pair<const Key,T>>> class map;
template<class Key,class T,class Compare=less<Key>,class Allocator=allocator<pair<const Key,T>>> class multimap;

key,T����߱��ɸ�ֵ(assignable)�Ϳɸ���(copyable)������,���������ڲ�Ҫ����,����key�����ǿ��ԱȽϵ�(comparable);

4.Ԫ�ش�С�Ƚ�
1.>��ֵ�Ƚ�
ͨ������key_comp���Խ��м�ֵ�ıȽ�,��������Ϊkey_comp,key_comp������map��Ԫ�ص�����˳��;
key_compare key_comp() const;

5.��ȡ�ڴ������
����get_allocate()���ڷ���map����multimap���ڴ�������,�ڴ�����������ָ����׵�ַ,
����ָ������ĳ�ʼ�洢λ��;
Allocator get_allocator() const;
����ֻ�ܶ�ȡ�ڴ������,���ܸı��ڴ������,�����ܸı������������洢��λ����;

7.ͨ���������ΪSTL����
string���Ա���Ϊ����,��Ԫ�ؾ�Ϊ�ַ�;ͨ�����鲻����,Ҳ�������ṩ��Ա����,���ǿ���ͨ����ָͨ��,ʹ��STL���㷨
ʵ�ֶ���ͨ����Ĳ���;

3.9 ���������÷�
STL�ṩ�˲��ֱȽ����������,���漰�������ݽṹ���㷨,��Щ����ģ����Ҫ����:λ����ģ��,
��ջ��ģ��,������ģ������ȶ���ģ��;


3.9.1 bitset��ģ��
bitset����һ���ں�λ�򲼶�ֵ�Ҵ�С�̶�������(array);
����Ҫ������ֱ�ʶ,������Ҫ�Ա�ʶ��������ϱ��ֱ���ʱ,�Ϳ���ʹ��bitset��ģ��;
��C/C++��,ͨ��ʹ���ͱ�long����Ϊbits array,��ͨ��&������~��λ������,��������λ;
bitset����е����ڿ��������������λ,���ṩ�������;
��bitset��Ϊ0��1��ɵ�����,���ж�д;

���ڼȶ���bitset���������,����λ�ĸ����ǲ��ܸı��;bitset���б���������λ������
����ģ�����������;�����Ҫʹ�ÿɱ䳤�ȵ�����,�ɿ���ʹ��ģ��vector<bool>;
ģ�����������һ���ͱ�,����һ���޷���������;

�ڶ�bitset�Ͷ�����бȽϺ����ʱ,����������������λ����������ͬ;
��ģ��bitset�Ĺ��캯������������ʽ:
bitset();
bitset(unsigned long val);//λ�εĹ��캯��,����ֵ�Ķ�������ʽ��Ӧ��λΪ1;
explicit bitset(const string& str,size_t pos=0,size_t n=-1);//λ�εĹ��캯��


3.9.2 stack��ģ��
��ģ��stack(ջ)(����ȳ�,LIFO)����ջ����;
push()������������Ԫ����ջ(stack)��,pop()�������η����ջ;

namespace std{ template<class T,class Container=deque<T>>class stack;}

��һ��template��������Ԫ������;Ĭ�ϵڶ���template������������stack�ڲ����Ԫ�����õ�ʵ������;
Ĭ�ϲ���deque;����deque(û��ѡ��vector)��Ŀ����Ҫ����Ϊdeque�Ƴ�Ԫ��ʱ���ͷ��ڴ�,
�����������·���ʱ��������Ԫ��;

ջstack���������ת��Ϊ�ڲ������Ķ�Ӧ����,ʵ���Ͽ���ʹ���κ���ʽ����(vector,list)
֧��stack,��֧��back(),push_back(),pop_back()
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
	//ʹ��find�㷨
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

	//����-----------------
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
	//����������-----------
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
	typedef multimap<int,double,greater<int>> M_MAP;//false--kc_2(5,4)��ʱ��Ϊtrue;
	MAP m_1;
	M_MAP m_2;
	MAP::key_compare kc_1=m_1.key_comp();
	M_MAP::key_compare kc_2=m_2.key_comp();
	bool r=kc_1(2,3);
	bool M_r=kc_2(3,4);
	if(r)
	{
		cout<<"kc_1(2,3)����ֵΪtrue."<<endl;
	}
	else
	{
		cout<<"kc_1(2,3)����ֵΪfalse."<<endl;
	}
	if(M_r)
	{
		cout<<"kc_2(3,4)����ֵΪtrue."<<endl;
	}
	else
	{
		cout<<"kc_2(3,4)����ֵΪfalse."<<endl;
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
//STL���㷨ʵ�ֶ���ͨ����Ĳ���
//ͨ���������ΪSTL����
//����������------
//ͨ���Զ���������Զ�����ģ�����ʽ,ʵ�ֶ�����ķ��ʺͲ���;
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
	bitset<16> b2(25);//���Ҳಹ��
	bitset<16> b3(str,2,16);
	print_bit_set(b1);
	print_bit_set(b2);
	print_bit_set(b3);

	cout<<"b1.size():"<<b1.count()<<endl;
	cout<<"b2.size():"<<b2.count()<<endl;
	cout<<"b3.size():"<<b3.count()<<endl;

	cout<<"b1.any():"<<b1.any()<<endl;//�ж�λ�����Ƿ����ٰ���һ��"1"
	cout<<"b2.any():"<<b2.any()<<endl;
	cout<<"b3.any():"<<b3.any()<<endl;

	cout<<"b1.none():"<<b1.none()<<endl;//�ж�λ�����Ƿ�ȫ��0
	cout<<"b2.none():"<<b2.none()<<endl;
	cout<<"b3.none():"<<b3.none()<<endl;

	cout<<"b1.test():"<<b1.test(2)<<endl;//�жϵ�2λ��1����0
	cout<<"b2.test():"<<b2.test(2)<<endl;
	cout<<"b3.test():"<<b3.test(2)<<endl;

	cout<<"set(5,1):"<<endl;//����λ
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

	//ת�����ַ���
	cout<<"to_string:"<<endl;
	cout<<b1.to_string()<<endl;
	cout<<b2.to_string()<<endl;
	cout<<b3.to_string()<<endl;

	//β��ת������ֵ
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
