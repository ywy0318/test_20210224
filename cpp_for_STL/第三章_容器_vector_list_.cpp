/*
�����ǹ������е���,ͨ���������ṩ�ĳ�Ա����,ʵ�ָ��ֶ�������Ԫ�صĲ���,
��һ�ָ߶ȵķ��ͳ���,���ַ���Ҳ����Ӧ�����������еĿ���;
STL�ṩ�˸�������ģ����,ͨ����Щģ�������:����(vector),�б�(list),˫����(deque),
����(set),���ؼ���(multiset),ӳ��(map),����ӳ��(multimap);

����(vector)������Ϊ�ǰ���һ������N������Ԫ�ص�����;
�б�(list)���ɽڵ���ɵ�˫������,ÿ���ڵ����һ��Ԫ��;
˫����(deque)�ǰ���N��������ָ��ͬԪ�ص�ָ����ɵ�����;
����(set)���ɽڵ���ɵ�,ÿ���ڵ����һ��Ԫ��,�ڵ�֮����
		ĳ��ν������;
���ؼ���(multiset)������������������ȵ�Ԫ�ؼ���;
ӳ��(map)����{��,ֵ}����ɵļ���,ͬ����ĳ��ν������,
		ν�ʺ����ݶ���ĳ������;
����ӳ��(multimap)��������԰�����ȴ����ӳ��;

STL��ʵ������������ͬʱ,��ʵ���˲�������ʽ������������(adapter);
�����������������ԭ�еĻ��������Ĳ���,��ԭ�л����������ܵĲ���;
���е����������ṩ������,Ԫ�ط���ͨ��ר�еĽӿں���ʵ��;
�����������ϸ��˵,��������������ʹ�������Ķ���,���������Ļ����Ϸ�չ������;

STL�ṩ��ÿ������,���ṩ����������Ϊ�ͳ�Ա;��Ϊ�����ĳ�Ա,��������3������:
1.>Ԫ�ر����ǿɸ��Ƶ�;���������������1��Ԫ�ظ���,���Ƿ���alias(����)����;
��������������Ϊ���صľ�����Ԫ�صĸ���;��͵��¸��ƹ��캯����ִ�зǳ�Ƶ��;
2.>Ԫ�ر����ǿ�ָ��(assign)��;�����ĳ�Ա�����Լ�STL�ĸ����㷨(algorithms)����
����assign()����ΪԪ���趨��ֵ;
3.>Ԫ�ر����ǿ��ͷŵ�(�������������ͷ��ڴ�),ʹ���ߴ������н�Ԫ��ɾ��ʱ,����
�����ͷ���Ԫ����ռ���ڴ�;����������,����������������Ϊprivate����;

��Ϊ�����ĳ�Ա����(����),��������Ҫ������:

1.>���������ṩvalue,����reference(����),�漰Ԫ�ز���ʱ,Ԫ��������������������;
2.>���е�Ԫ���Զ��γ�˳��;������˳����Զ�α�������Ԫ��;��Щ�����������ɷ���
�������ĺ���,ʹ����Щ�������ɱ���Ԫ��;�����㷨�������Ĺؼ��ӿ�ʵ��;
3.>����ʹ���߱���ȷ�����ݵĲ�������Ҫ��,����,���ܻᵼ��δ�������Ϊ,ͨ��STL�����׳��쳣;


STL����ͨ����Ϊ3��:����ʽ����,����ʽ����,���������;
1.>����ʽ����(sequence����),�����е�Ԫ��ʱ�����,��δ����;����:vector��̬����,
deque˫�����,list˫����;
2.>����������,�����е�Ԫ�ض���������;����set,multiset,map,multimap��hash(��ϣ)table;
3.>���������,����ĳ��STL������Ϊ��,�޸���ӿ�;�߱����Ե��ص�:����stack,queue,priority_queue;


STL���������ݽṹҲ����3��:string�ַ���,bitset,valarray;

1.>string�ַ���,���ڱ����ַ�;string������������,����1��basic_string���typedef;
2.>bitset,���ڱ���bits�Ľṹ��;ÿ��bit��ʾ1����־(flag);�䳤�ȹ̶�,���ȱ���ģ����Ա���;

3.2>����ʽ����
���ڻ�������,ͨ������Ҫ��,ʵ�ֶ���ĸĽ�;������һ����Ҫ�ĸĽ�,6��STL����(deque,list,queue,
priority_queue,stack,vector)��������;
�������յ��ص���ǿ������׶�ɾ��Ԫ��,��β�����Ԫ��;������˫������,������������Ӻ�ɾ��Ԫ��;
�����а�������һ�ֵ�����,�Ӷ���֤Ԫ�ذ����ض���˳������,���������ε����䷢���仯;

����������������,����֧�ṹ��������;������Ԫ�ؾ���ȷ��˳��,ʹ��ʱ���Խ�Ԫ�ز����ض�λ��,
ɾ���ض�����Ȳ���;��׼���ṩ�Ļ������а���:vector,list,deque;
ͬʱ������3��������:stack,queue,priority_queue;

vector,list,deque 3�����в����ܻ���ʵ��,ͬʱ�ֲ���ʧЧ��;��һ����,stack��queue��������
��3�л������еĻ����ϸ�Чʵ��;

vector,list,deque3��������ʹ��ʱ,��Ҫ�ֱ������Ӧ��ͷ�ļ�;����������ģ��,
Ҫ�����ʵ��ĳ���ض�����������,�������������һ�Լ�����,�������ṩ�������Ԫ�ص���������;


#include<vector>
#include<list>
#include<deque>

vector <string> svec;
list <int> ilist;
deque <long> litem;

3.3����ʽ����--vector��ģ��
template <class T,class Allocator=allocator<T>> class vector;
vector�е�Ԫ�ؿ�������������T,����߱�������,�ɸ�����������;ģ��ĵڶ��������ǹ��ڿռ����������õ�,����
�����ڴ�ģ��,Ĭ���ڴ�ģ����C++��׼���ṩ��allocator,����һ��ĳ���Ա��˵,���п���;
vector����򵥵�����ʽ����,֧���������Ԫ��;��ʱ����Ե�Ч�ʵ�һЩ;vector�Ĵ�С������֮������Ҫ���;
�����϶��Ǵ��ڻ��ߵ������С;

vector����һ����̬����,�ǵ��͵�"��Ԫ�����ڶ�̬�����м��Թ���"�ĳ������;��C++��׼��,��δ�涨������
��̬������ʵ��vector,���涨����Ӧ�������Ͳ������Ӷ�;�ڳ��򿪷�������,����Աʹ��vector��Ϊ��̬�����Ƿǳ�
�����;vector�ĵ�������������������,���κ�һ��STL�㷨����Ч;
������ĩ�˻�ɾ��Ԫ��ʱ,vector�����൱��;

vector ����ʵ�����ݽṹ�еĶ���,����Ͷ�ջ�����й���;vectorһ�������������֮��,�Ϳ���װ������;

�����Ĵ�С������
vector��ģ�嶨����������(size��capacity),ʵ��ͳ������Ԫ�ص�Ŀ��;����������������(resize��reserve),
ʵ������������С��Ŀ��;
size()��capacity()����ͳ��������Ԫ�ص�����;size()������������������Ԫ�ص�����;
capacity()��������������ʵ���ܹ����ɵ�Ԫ������;
����max_size()���Է��������������ɵ����Ԫ������;
һ�������,Ԫ��������Խcapacity()���ص���ֵʱ,vector�б�Ҫ���������ڴ�洢��;
����reserve()����Ԥ�����������Ĵ�С;����resize()�����޸������Ĵ�С;
����reserve()���Ա����ʵ����������������������ڴ�;
�ڶ�����������ʱ,ͨ�����ݺ�������ʽ,��������vector����ʼ��С;

����vector������
����ʹ�õ���������ʵ�ֱ���,Ҳ����ͨ��ʹ��at()������ѭ�����ʵ��;

3.ʹ���㷨
ʹ��STL vector, ������ͨ��ʹ�ò����㷨,ʵ�ֶ�vector�Ĳ���;

3.3.3 vector�߼����
vector������ص�Ԫ�ط��ʷ���,��������غ���,Ԫ�ز��Һ�����,
vector�������е��ַ�������,Ԫ������,����Ԫ��,ɾ��Ԫ��,���󽻻�;

2.��������غ���
vector��ģ���ṩ���ֳ��溯������ȡ������;��������������ʵ�����,ͨ��������
�������Բ��������㷨;�͵�������صĺ�����Ҫ����:begin(),end(),rbegin(),read();
����begin()ָ���һ��Ԫ��;end()ָ�����һ��Ԫ�ص���һ��λ��;rbegin()ָ�����������
��һ��Ԫ��;rend()ָ��������������һ��Ԫ�ص���һ��λ��;
����begin()��end()����ֵ���;�Ϊ����������;
����rbegin()��rend()����ֵ���͵����������;

3.Ԫ�ز��Һ�����
����vector�������е�Ԫ��,����ʹ��STL��ͨ���㷨find();
�������������Ԫ�ؿ���ʹ���㷨find_if();
�������㷨������ʹ�õ�����,�������������������������Ͳ���
�ķ�Χ;��������ֵ��Ϊ����������;

template<class InputIterator,class T> inline InputIterator find(InputIterator first,
InputIterator last,const T&value);

template<class InputIterator,class T,class Predicate> inline InputIterator find(InputIterator first,
InputIterator last,const T&value,Predicate predicate);

3.3.4vector�������е��ַ�������
ʹ��vector�����ַ���,���Դ����ַ����е�ÿ���ַ�,����vector�����Զ������ڴ�;
�ַ����е�ÿһ���ַ���Ϊ����vector������Ԫ��,ʹ�����������г�Ա��������
��������ַ����Ĳ���;
3.3.5Ԫ������
ʵ�ֶ�vector������Ԫ�ص�������Ҫʹ���㷨sort()�������������㷨;��Щ����֧�ֶ������㷨
��ʵ��,ʹ���㷨����,��������߼�������;��vector����û���ṩ���������㷨�ĳ�Ա����;

3.3.4����Ԫ��
�����ڵ�vector�������в��������һ���µ�Ԫ��,����ʹpush_back()������Ԫ�ؼ���vector�Ͷ���(����)��ĩβ;
������ʹ��insert()�������������vector�е�����λ��,��insert()��������ʵ���ڵ�����ָ��λ�ò���Ԫ��;
insert()��������ֵΪ������,ָ��ղ����Ԫ��;�������ٵ�����ָ��λ�ò����������Ĳ�ͬԪ��,�����Բ���
���ֵ��ͬ��Ԫ��;����push_back�ͺ���insert()��ԭ������:

template<class _TYPE,class_A>void vector::push_back(const _TYPE& X);//push_back()ģ��
iterator insert(iterator it,const T&x=Y());//insert()������3��ģ��
void insert(iterator it,size_type n,const T&x);
void insert(iterator it,const_iterator first,const_itearator last);

3.3.7ɾ��Ԫ��
�ڶ���vector������,��Ҫ��ʼ����Ԫ��;���Ҷ���vectorʱͬʱʹ������STL�����е�������������ʼ��;
��STL����������vector�Ͷ���;ֻҪԪ�ص�������ͬ����;

vector<int> Harry;
Harry.push_back(1);
Harry.push_back(2);
vector<int>Bill(Harry.begin(),Harry.end())

ɾ�������е�Ԫ��,����ʹ��3����Ա����:pop_back(),erase()��clear();������ʹ���㷨��
���㷨remove()��ʵ��;
pop_back()����ɾ�����һ��Ԫ��,����erase()����ɾ���ɵ�����ָ����Ԫ��,Ҳ����ɾ��
���䷶Χ��Ԫ��;clear()����ʵ��ɾ������vector������Ԫ��,�൱��erase(begin(),end());


3.3.8��������
vector��ģ�廹�ṩ�˳�Ա����swap(),��������vector������֮���Ԫ�ػ��ཻ��;����������뽻��
��vector������ͬ,���󽻻���˲�����;����������뽻����vector�����Ԫ�����Ͳ�ͬ,��ʵ�ֶ���
�����Ĺ�����,��Ҫִ�зǳ����ӵĲ���;
template<class T,class A> void swap(const vctor<T,A>&v1,const vector<T,A>&v2);

3.3.9vector<bool>��
C++��׼�����ר�����Ԫ�����Ϊbool��vector���������汾,Ŀ���ǻ�ȡ�Ż���vector;
����ռ�õ��ڴ�ռ�ԶС��һ���vectorģ��ʵ������bool������(����);
��ͨ��vector��ģ������1��byte�ռ�;��vector<bool>ֻռ��1��bit�洢����Ԫ��;
��ռ�ڴ�ռ�С8��;
C++����СѰַͨ����byteΪ��λ,����vector<bool>�������reference��iterator�������⿼��;
��vector<bool>�Ĳ���Ҫ����ͨ��vector���ܶ�,����Ԫ�ز�������ת��Ϊbit����;
��vector<bool>�������������͵�������,���ṩλ����,�ǳ�����ز���"λ"��"��־",
��������Ԫ�ش�ȡ�ĺ���,����ֵ��ΪӦ����(reference);
vector<bool>���ṩ��λȡ������flip(),�ȿ���ʵ�ֶ�����������Ԫ��ȡ��,�����Զ�ĳ"λ"ȡ��;
-----------------------
3.4����ʽ����----list��ģ��
ģ����list��һ������,list����˫��������ʵ�ֵ�,ÿ���ڵ�洢1��Ԫ��;list֧��ǰ�������ƶ�����;
list��vector����,�ṩ�˶�Ԫ�ص��������;list�����������κ�λ��ִ�в����ɾ���������ǳ�Ѹ��,
��Ϊ�ı�Ľ��������Ӷ���;��list���ƶ�Ԫ��Ҫ����vector��deque�п�ö�;
listģ�����Ƕ����������ռ�(namespace)std�е�,����ģ���������ʽΪ:
template<class T,class Allocator=allocator<T>> class list;

ʹ��list��Ҫ����ͷ�ļ�<list>;�����ͱ�TֻҪ�߱��������ԺͿɸ�����,������ΪlistԪ��;
ģ��ĵڶ����������п���,������ָ���ڴ�ģ��;��ģ����Ҳָ����Ĭ�ϵ��ڴ�ģ��Ϊallocator;
List���ڲ��ṹ��vector��ͬ,���ڽ����Ե�����;

1.>list��֧�������ȡ;
2.>��list���κ�λ��ִ��Ԫ�صĲ�����Ƴ����ǳ���,���Կ���ʵ��;�����ɾ����������Ӱ��ָ��
����Ԫ�ص�ָ��,����,��������������ʧЧ;
3.>list��֧�������ȡ,���ṩ�±��������at()����;
4.>listû���ṩ����,�ռ����·���Ȳ�������;
5.>listҲ�ṩ�������Ա����,ר�������ƶ�Ԫ��,��ͬ�����㷨���,�ٶȸ���;
listģ����ʵ���˱�׼C++���ݽṹ����������й���;listһ�������������֮��,
�Ϳ�������������;

3.4.1 list�Ķ��������
1.list�Ķ���͹��캯��
��ģ���������Ķ��������һ��Ԫ������ΪT�Ŀɱ䳤������;��������˫������ķ�ʽ�洢,
������ÿ��Ԫ�ض�����һ������ΪT�ĳ�Ա;list����ͨ���洢�����ڲ���һ����A�ķ������������
�洢�ռ�ķ�����ͷ�;�÷������������ӵ�к�ģ����allocatorͬ�����ⲿ�ӿ�;

��ͷ�ļ�list�ж�����4�й��캯��
explicit list(const _A& _A1= _A()):allocator(_A1),_Head(_Buynode()),_Size(0)
{
	
}
explicit list(size_type_N,const_Ty&_V=_Ty(),const_A&_A1=_A()):allocate(_A1),
_Head(_Buynode()),_Size(0)
{
	insert(begin(),_N,_V);
}
list(const _My& _X):allocator(_X.allocator),_Head(_Buynode()),_Size(0)
{
	insert(begin(),_X.begin(),_X.end());
}
list(const _Ty*_F,const_Ty*_L,const _A&_A1=_A()):allocator(_A1),_Head(_Buynode()),_Size(0);
{
	insert(begin(),_F,_L);
}

list<A> listname;
list<A> listname(size);
list<A> listname(size,value);
list<A> listname(elselist);//���ƹ��캯��
list<A> listname(first,last);//����һ��list����,��������list�����и����ɵ�����ָ����Χ�Ķ��Ԫ��;

2.Ԫ�صĸ�ֵ
listģ�����ṩ��������Ա����push_front()��push_back(),�������µ�Ԫ�ز���list������;
push_front()�����������е�ͷ��������Ԫ��,����vector��ͷ��������Ԫ�ص�Ч�ʷǳ���,
����ֻ��list�д��ڸú���,���⻹����������pop_front()��pop_back()�ֱ����ڻ�ȡ
������ͷ��������βԪ��;
void push_front(const T&x);
void push_back(const T&x);
void pop_front();
void pop_back();
3.4.3����������
list������Ϊ����,����������صĳ�Ա��������:resize(),size(),max_size()
size_type size() const;
size_tye max_size() const;
void resize(size_type n,T x=T());
����size()��max_size()�ķ������;�Ϊsize_type��,��unsigned int����;
size()���ڷ���list����(����)��Ԫ�صĸ���;max_size()���ڷ���list���������������,
һ����һ���ǳ��������,����resize()�������µ���list����Ĵ�С;

3.4.4���������
listģ��������͵�������صĺ�����Ҫ��:begin(),front(),rbegin(),end,back(),rend();

const_iterator begin() const;
iterator begin();
reference front();
const_reference front() const;
const_reverse_iterator rebegin();
const_iterator end() const;
iterator end();
const_reference back() const;
const_reverse_iterator rend();
reverse_iterator rend();

3.4.2 list����������Ա����
list����������ı�����ݰ���:�ж�list�����Ƿ�Ϊ��,Ԫ�ش�ȡ,Ԫ������,����������������,
list������Ԫ�صĲ����ɾ����;
1.�ж������Ƿ�Ϊ��
���list������Ϊ��,��Ա����empty()����true;����empty()��ԭ��Ϊ:
bool empty() const;
2.list��������Ԫ�صĴ�ȡ�ͷ���
list���������ṩ��Ա����at()�Ͳ�����operator[],�������е�Ԫ�ط�����Щ����'
ʹ�õ���������Ԫ�صķ���;
3.Ԫ������
��list���������ṩ�˿�������Ԫ��ֵ�ĳ�Ա����assign();
ʹ�ú���assign()�����޸�����������Ԫ�ص���ֵ,���������޸Ķ��
����Ԫ�ص���ֵ;assign()��ԭ��:
void assign(const_iterator first,const_iterator last);
void assign(size_type n,const T&x=T());
4.��������list����������
ģ����list�ṩ�˳�Ա����swap();����ʵ������list������(����)�����ݽ���;
ͨ��swap()�����������list������Ԫ�ؽ�����ͬʱ,�����Ĵ�СҲ�����˱仯;
��STL���㷨����,Ҳ�ṩ��swap()����;��Ϊͨ���㷨ͬ������ʵ�ֽ�������list
�����е�����;

5.Ԫ�صĲ����ɾ��
ģ��list������������һ��,�ṩ�˷ḻ�����Ĳ����ɾ��Ԫ�ز���;
����list�������ṩ�˽����ƵĲ����ɾ������;list���������������е�
��ͷ�Ͷ�β���Ĳ����ɾ��Ԫ��;�漰�ĳ�Ա������Ҫ����:push_back(),
push_front(),pop_back(),pop_front(),insert(),erase()��clear()
push_front��push_back()���������ɵĲ���Ԫ����������,
pop_back()��pop_front()Ҳ�������ɵ�ʵ�ִ��׶˻�β�˽�Ԫ��
���������Ƴ�;

��Ա����insert()��ԭ�ͷ�Ϊ����������ʽ:

iterator insert(iterator it,const T&x=T());//�����ĳ��Ԫ�ز���ָ��λ��
void insert(iterator it,size_type n,const T&x);//��ĳ������ֵ�Ķ�����ݲ���list�е�������ָ��ʼλ��;
void insert(iterator it,const_iterator first,const_iterator last);//��Ҫ���ڰ�һ��ָ����Χ�Ķ��Ԫ�ز���list�е�������ָ��ķ�Χ��;


iterator erase(iterator it);//ɾ����������ָ���Ԫ��
iterator erase(iterator first,iterator last);//ɾ��������������ķ�Χ��

clear()�൱��ʹ��erase()ɾ�������е�����Ԫ��;erase(begin(),end());

3.4.3���������
list������Ҳ�ṩ�˴�����ģ�庯��,�ṩ�˴������������;
�����İ���:operator==,operator<,operator!=,operator<=,operator>,operator>=;

1.operator==
operator[]�Ļ���ʹ�÷�����Ҫ�Ƕ�ȡlist�е�Ԫ��,�����㷨operator==�����ж����,
�����ж�����list�����Ƿ����;�����ȷ���,true;
bool operator==(const list<Type,Allocator>& _Left,const list<Type,Allocator>& _Right);
��ʽ����,����Ƚϵ�����list����ĸ�ʽӦ����ȫһ��,����ʹ���������Ͳ�ͬ���������бȽ�;

2.operator<
�����operator<��Ȼ�������ж�,�������ж�����list�����Ƿ�"ǰ��С�ں���",
����Ƿ���true,���򷵻�false;

bool operator<(const list<Type,Allocator>& _Left,const list<Type,Allocator>&_Right);

3.4.4������Ҫ��Ա����
list����������һЩ���⺯��:����merge(),remove(),remove_if(),sort(),splice(),unique();

1.����merge()��sort()
����merge()����ʵ�ֽ�����list�Ͷ���ϲ���һ��list����;�����Ĺ������ڰ�ԭ���е�list
����������Ϊ��������,����Ŀ��list(�����ĵ�����)��;�ϲ�֮���������Ԫ���ǰ���С����
�����е�;
void merge(list &x);
void merge(list &x,greater<T>pr);
void sort();
void sort(greater<T>pr);

2.����remove()�ͺ���remove_if()
void remove(const Type& _Val);
����ʵ��ɾ��list������ĳ�������Ԫ��;remove()��������Ҫָ������λ��,ֻҪ������Ҫ
ɾ����Ԫ�ص�ֵ,�Ϳ���ֱ��ɾ��������Ӧ��Ԫ��;remove()���ı�������Ԫ�ص�˳��,
���һ�ɾ�����е��ڲ���(ָ����ֵ_Val)��Ԫ��;
template <class Pred> void remove_if(Pred pr);
��ɾ����������"Pred pr"����ӦԪ��;
typedef binder2nd<not_equal_to<_Ty>> Pred;
ֻ�е�Pred prΪtrueʱ,������ȷִ��ɾ������;

3.splice()
void splice(iterator it,list& x);
void splice(iterator it,list& x,iterator first);
void splice(iterator it list& x,iterator first,iterator last);

4.����unique()
��Ա����unique()���Ƴ��ظ�Ԫ�ؽ�����һ��;
void unique()
template<class BinaryPredicate>void unique(BinaryPredicate _Pred);
����unique()�ζ�������Ԫ��ʱ�Ѿ������,���������ͬ��Ԫ�ض������ڵ�,�����ڵ�
�ظ�Ԫ�ز����Ƴ�;
unique()���ܱ�֤������Ԫ��ֵ��Ψһ��,�����ǽ����ڵ��ظ�Ԫ�ر���һ��;
ʹ��list�����ĳ�Ա����uniqueʱ,������ʹ��sort()�������е�Ԫ�ؽ�������;

5.����reverse()
reverse()ʵ�ֽ�����������Ԫ����ԭ���෴��˳������
*/
#pragma warning(disable:4786)
#include<string>
#include<iostream>
#include<bitset>
#include<valarray>
#include<vector>
#include<algorithm>
#include<functional>
#include<list>
using namespace std;
vector<int> myvt;
template<class T> void print_list(const T& ele)
{
	cout<<" "<<ele<<";"<<endl;
}
template<class T>void print_list_T(list<T>& mylist)
{
	list<T>::iterator iter;
	mylist.reverse();
	for(iter=mylist.begin();iter!=mylist.end();iter++)
	{
		cout<<*iter<<",";
	}
	cout<<endl;
}
template <typename T> void print_Valarray(const valarray<T>& va)
{
	for ( int i=0;i<va.size();i++)
	{
		cout<<va[i]<<" ";
	}
	cout<<endl;
}
template<class T>void print_list(list<T>& mylist)
{
	list<T>::iterator iter;
	mylist.reverse();
	for(iter=mylist.begin();iter!=mylist.end();iter++)
	{
		cout<<*iter<<", ";
	}
	cout<<endl;
}
struct ST
{
	int id;
	double db;
};
class student
{
public:
	string name;
	double score;
	student(const string &a,double b ):name(a),score(b){}
	bool operator<(const student &m)const
	{
		return score<m.score;
	}

};
//�����ӽ���
bool name_sort_less(const student& m,const student&n)
{
	return m.name<n.name;
}
//�����ӽ���
bool name_sort_greater(const student& m,const student&n)
{
	return m.name>n.name;
}
//�����ӽ���
bool score_sort(const student& m,const student&n)
{
	return m.score>n.score;
}
//�����ӽ���
void print_student(student& s)
{
	cout<<s.name<<"  "<<s.score<<endl;
}
//��ʼ��
void Original_student(vector<student>& v)
{
	student st_1("Tom",74);
	v.push_back(st_1);

	st_1.name="Jimy";
	st_1.score=56;
	v.push_back(st_1);

	st_1.name="Mary";
	st_1.score=92;
	v.push_back(st_1);

	st_1.name="Jessy";
	st_1.score=85;
	v.push_back(st_1);

	st_1.name="Jone";
	st_1.score=56;
	v.push_back(st_1);

	st_1.name="Bush";
	st_1.score=52;
	v.push_back(st_1);

	st_1.name="Winter";
	st_1.score=77;
	v.push_back(st_1);

	st_1.name="Ander";
	st_1.score=63;
	v.push_back(st_1);

	st_1.name="Lily";
	st_1.score=76;
	v.push_back(st_1);

	st_1.name="Maryia";
	st_1.score=89;
	v.push_back(st_1);

}

void test_bitset()
{
	bitset<10> bs1(7);//bitset�г���Ϊ10��bit;��ʼ��Ϊ10���Ƶ�7;
	bitset<10> bs2(string("1000101011"));//��ʼ��Ϊ10���ַ����ȵ��ַ���
	cout<<bs1<<endl;
	cout<<bs2<<endl;
	return;
}
void test_3_2()
{
	valarray<int> va1(4);//����4��Ԫ��,����δָ��Ԫ�ص�ֵ;
	print_Valarray(va1);

	valarray<int> va2(3,4);//����4��Ԫ��,����ֵ��Ϊ3
	print_Valarray(va2);

	int ia[]={1,2,3,4,5,6};//��������������
	valarray<int> va3(ia,sizeof(ia)/sizeof(ia[0]));//��̬�����С�� ����ia��Ԫ�ظ�����ͬ
	print_Valarray(va3);

	valarray<int> va4(ia+1,4);//����4��Ԫ��,����ֵ��Ϊia��ǰ4��Ԫ�ؼ�1
	print_Valarray(va4);

	va1=(va2+va4)*va4;//
	print_Valarray(va1);
}
void test_vector_1()
{
	vector<string> my_vector;
	my_vector.reserve(4);//ʹ��reverse()����Ԥ�����������Ĵ�С
	my_vector.push_back("1.beijing");
	my_vector.push_back("2.tianjin");
	my_vector.push_back("3.shanghai");
	my_vector.push_back("4.chongqing");
	cout<<"OK!"<<endl;
	cout<<endl;
	vector<string>::iterator it;
	for(it=my_vector.begin();it!=my_vector.end();it++)
	{
		cout<<*it<<endl;
	}

	cout<<"my_vector.size(): "<<my_vector.size()<<endl;
	cout<<"my_vector.capacity():"<<my_vector.capacity()<<endl;
	cout<<"my_vector.max_size(): "<<my_vector.max_size()<<endl;

	my_vector.resize(10);
	cout<<"---"<<endl;
	cout<<"my_vector.size(): "<<my_vector.size()<<endl;
	cout<<"my_vector.capacity():"<<my_vector.capacity()<<endl;

	for(it =my_vector.begin();it!=my_vector.end();it++)
	{
		if(*it=="")
		{
			cout<<"***"<<endl;
			cout<<*it<<endl;

		}
	}
}
void Iter_for(vector<ST>& vt)
{
	ST temp_1;
	vector<ST>::iterator iter;
	for(iter=vt.begin();iter!=vt.end();iter++)
	{
		temp_1=*iter;
		cout<<"id :"<<temp_1.id<<", db :"<<temp_1.db<<endl;
	}
}
void at_for(vector<ST>& vt)
{
	ST temp_2;
	int i=0;
	int m=vt.size();
	for(int i=0;i<m;i++)
	{
		temp_2=vt.at(i);
		cout<<"id :"<<temp_2.id<<", db :"<<temp_2.db<<endl;
	}
}
void Origin(int num,vector<ST>& vt)
{
	int m=num;
	ST temp;
	for(int i=0;i<m;i++)
	{
		temp.id=i+1;
		temp.db=(i+1)*10;
		vt.push_back(temp);
	}
}
void out(ST &st_1)
{
	cout<<"id_out: "<<st_1.id<<"db_out: "<<st_1.db<<endl;
}
void print(int &temp)
{
	cout<<temp<<endl;
}
bool is_Even(int &ele)
{
	return(ele%2==1);
}
void print_bool(bool &ele)
{
	cout<<ele;
}
void test_vector_is_empty()
{
	ST tmp;
	vector<ST> myvt;
	Origin(5,myvt);
	int size=myvt.size();
	cout<<"myvt.size():"<<myvt.size()<<endl;

	cout<<"at_for"<<endl;
	at_for(myvt);
	cout<<"Iter_for"<<endl;
	Iter_for(myvt);
	cout<<"for_each():"<<endl;
	for_each(myvt.begin(),myvt.end(),out);
	cout<<"empty()"<<endl;
	while(!myvt.empty())
	{
		tmp=myvt.back();
		cout<<"id :"<<tmp.id<<", db :"<<tmp.db<<endl;
		myvt.pop_back(); 
	}
	
}
void print_ele(int &Ele)//���Ԫ��
{
	cout<< Ele<<",";
}
void print_double(double &ele)
{
	cout.width(5);//��ʽ�����,���5���ַ�,����1λС����
	cout.precision(1);
	cout<<std::fixed<<ele<<",";
}
void print_int(int &ele)
{
	cout<<ele<<", ";
}

void test_insert()
{
	
	for(int i=0;i<10;i++)
	{
		myvt.push_back(i);
	}
	myvt.insert(myvt.begin(),-1);
	for_each(myvt.begin(),myvt.end(),print_ele);
	cout<<endl;
	myvt.insert(myvt.end(),-2);
	for_each(myvt.begin(),myvt.end(),print_ele);
	cout<<endl;

	vector<int> vt_2;
	vt_2.push_back(-8);
	vt_2.push_back(-9);

	myvt.insert(myvt.end(),vt_2.begin(),vt_2.end());
	for_each(myvt.begin(),myvt.end(),print_ele);
	cout<<endl;

	myvt.insert(myvt.begin(),3,0);
	for_each(myvt.begin(),myvt.end(),print_ele);
	cout<<endl;

}
void test_bill()
{
	test_insert();
	myvt.clear();
	cout<<"clear()"<<endl;
	for(int j=0;j<10;j++)
	{
		myvt.push_back(j);
	}
	for_each(myvt.begin(),myvt.end(),print_ele);
	cout<<endl;
	cout<<"----"<<endl;
	while(!myvt.empty())
	{
		myvt.erase(myvt.begin());
		for_each(myvt.begin(),myvt.end(),print_ele);
		cout<<endl;
	}
}
//����find_find_if������
void test_find()
{
	int IntArray[]={1,2,3,4,4,5,6,7};
	vector<int> myvector;
	int* location_index = NULL;
	for(int i=0;i<8;i++)
	{
		myvector.push_back(IntArray[i]);
	}
	for_each(myvector.begin(),myvector.end(),print);
	//location_index=find(myvector.begin(),myvector.end(),2);
	//cout<<"����2���±���:"<<(location_index-myvector.begin())<<endl;
	//location_index=find_if(myvector.begin(),myvector.end(),bind2nd(greater<int>(),5));
	//cout<<"����5���±���:"<<(location_index-myvector.begin())<<endl;
}
void test_vector_sort()
{
	vector<student> vect;
	Original_student(vect);
	cout<<"before sort"<<endl;
	for_each(vect.begin(),vect.end(),print_student);
	sort(vect.begin(),vect.end());//��score��С��������(ʹ��operator<)
	cout<<"------"<<endl;
	cout<<"after sort by sort"<<endl;
	for_each(vect.begin(),vect.end(),print_student);

	sort(vect.begin(),vect.end(),name_sort_less);//��name��С��������
	cout<<"------"<<endl;
	cout<<"after sort by name_sort_less"<<endl;
	for_each(vect.begin(),vect.end(),print_student);

	sort(vect.begin(),vect.end(),score_sort);//��score�Ӵ�С����
	cout<<"------"<<endl;
	cout<<"after sort by score_sort"<<endl;
	for_each(vect.begin(),vect.end(),print_student);

	sort(vect.begin(),vect.end(),name_sort_greater);//��score�Ӵ�С����
	cout<<"------"<<endl;
	cout<<"after sort by name_sort_greater"<<endl;
	for_each(vect.begin(),vect.end(),print_student);

}
void test_swap()
{
	vector<int> ci,cd;
	for(int i=0;i<10;i++)
	{
		ci.push_back(i);
		cd.push_back(i*3);
	}
	cout<<"vector-ci-below"<<endl;
	for_each(ci.begin(),ci.end(),print_ele);
	cout<<endl;
	cout<<"vector-cd-below"<<endl;
	for_each(cd.begin(),cd.end(),print_ele);
	cout<<endl;

	ci.swap(cd);
	cout<<"---"<<endl;
	cout<<"vector-ci-below"<<endl;
	for_each(ci.begin(),ci.end(),print_ele);
	cout<<endl;
	cout<<"vector-cd-below"<<endl;
	for_each(cd.begin(),cd.end(),print_ele);
	cout<<endl;
}
void test_vector_bool()
{
	int x[]={1,0,1,0,0,0,1,1,1};
	vector<bool> vt;
	vector<bool>::iterator it;
	for(int i=0;i<9;i++)
	{
		vt.push_back(bool(x[i]));
	}
	//����-----
	//for_each(vt.begin(),vt.end(),print_bool);
	cout<<endl;
	vt[3]=bool(1);
	//����------
	//for_each(vt.begin(),vt.end(),print_bool);
	cout<<endl;
}
void test_list_print()
{
	list<string> mylist_string;
	list<double> mylist_double(6);

	//��ʼ��mylist_string
	mylist_string.push_front("1:jack");
	mylist_string.push_front("2:Tom");
	mylist_string.push_front("3:Mike");

	//mylist_double
	mylist_double.push_front(10.0);
	mylist_double.push_front(20.0);
	mylist_double.push_front(30.0);
	mylist_double.push_front(40.0);
	mylist_double.push_front(50.0);

	list<int> mylist_int(6,0);
	list<double>mylist_double_2(6,0.0);
	list<int> else_list(mylist_int);
	list<double>Iter_list(mylist_double.begin(),mylist_double.end());

	list<string>::iterator iter_String;
	//--������������е�Ԫ��
	cout<<"the string list:mylist_string is below:"<<endl;
	
	for(iter_String=mylist_string.begin();iter_String!=mylist_string.end();iter_String++)
	{
		string temp=*iter_String;
		print_list(temp);
	}
	cout<<"the double list-mylist_double is below:"<<endl;
	for_each(mylist_double.begin(),mylist_double.end(),print_double);
	cout<<endl;

	cout<<"the double list-mylist_double_2 is below:"<<endl;
	for_each(mylist_double_2.begin(),mylist_double_2.end(),print_double);
	cout<<endl;


	cout<<"the double list-Iter_list is below:"<<endl;
	for_each(Iter_list.begin(),Iter_list.end(),print_double);
	cout<<endl;

	cout<<"the double list-mylist_int is below:"<<endl;
	for_each(mylist_int.begin(),mylist_int.end(),print_int);
	cout<<endl;

	cout<<"the double list-else_list is below:"<<endl;
	for_each(else_list.begin(),else_list.end(),print_int);
	cout<<endl;

	cout<<"-----------------------------------------"<<endl;
	//������������;
	int size=mylist_string.size();
	int maxsize=mylist_string.size();
	mylist_string.resize(5);
	size=mylist_double.size();
	maxsize=mylist_double.max_size();
	mylist_double.resize(5);
	//-------------
	size=mylist_double_2.size();
	maxsize=mylist_double_2.max_size();
	mylist_double_2.resize(5);
	
	size=Iter_list.size();
	maxsize=Iter_list.max_size();
	Iter_list.resize(5);

	size=mylist_int.size();
	maxsize=mylist_int.max_size();
	mylist_int.resize(5);

	size=else_list.size();
	maxsize=else_list.max_size();
	else_list.resize(5);
	//--------------------------------------------
	//�ٴ��������

	cout<<"the string list:mylist_string is below:"<<endl;
	//list<string>::iterator iter_String;
	for(iter_String=mylist_string.begin();iter_String!=mylist_string.end();iter_String++)
	{
		string temp=*iter_String;
		print_list(temp);
	}

	cout<<"the double list-mylist_double is below:"<<endl;
	for_each(mylist_double.begin(),mylist_double.end(),print_double);
	cout<<endl;

	cout<<"the double list-mylist_double_2 is below:"<<endl;
	for_each(mylist_double_2.begin(),mylist_double_2.end(),print_double);
	cout<<endl;


	cout<<"the double list-Iter_list is below:"<<endl;
	for_each(Iter_list.begin(),Iter_list.end(),print_double);
	cout<<endl;

	cout<<"the double list-mylist_int is below:"<<endl;
	for_each(mylist_int.begin(),mylist_int.end(),print_int);
	cout<<endl;

	cout<<"the double list-else_list is below:"<<endl;
	for_each(else_list.begin(),else_list.end(),print_int);
	cout<<endl;

	//ʹ�õ�������صĺ���
	list<double>::iterator iter_d;
	list<double>::reverse_iterator iter_rd;
	double temp=0.0;

	iter_d=mylist_double.begin();
	temp=*iter_d;
	cout<<"the beginning element of the mylist_double:"<<endl;
	cout<<temp<<endl;

	iter_rd=mylist_double.rbegin();
	temp=*iter_rd;
	cout<<"the reverse beginning element of the mylist_double:"<<endl;
	cout<<temp<<endl;
	//cout<<"??"<<endl;
	//-------------
	/*
	end()��ָ���Ԫ�طֱ������������һ��Ԫ��,�������end()���ص���ֵʱ,���������һ��Ԫ�ص���ֵ;
	ͬ��rend*();
	��ʹ�õ���������forѭ��ʱ,һ��ѭ����ֹ����ʱ(iterator!=end()),��ѭ����end()����ֵָ���λ��ʱ,
	(ǡ�������������һ��Ԫ�صĺ���),ֹͣѭ��;
	*/
	//iter_d=mylist_double.end();
	temp=*iter_d;
	cout<<"the ending element of the mylist_double:"<<endl;
	cout<<temp<<endl;

	//iter_rd=mylist_double.rend();
	temp=*iter_rd;
	cout<<"the reverse ending element of the mylist_double:"<<endl;
	cout<<temp<<endl;

	temp=mylist_double.front();
	cout<<"the front element of the mylist_double:"<<endl;
	cout<<temp<<endl;

	temp=mylist_double.back();
	cout<<"the back element of the mylist_double:"<<endl;
	cout<<temp<<endl;
}
void test_list_empty()
{
	list<double>mylist;
	mylist.push_back(10.2);
	bool empty=1;
	if(mylist.empty())
	{
		cout<<"the list is empty"<<endl;
	}
	else
	{
		empty=mylist.empty();
		cout<<mylist.front()<<", "<<empty<<endl;

	}
}
void test_list_visit()
{
	list<double> my_list;
	my_list.push_back(11.1);
	my_list.push_back(21.5);
	my_list.push_back(31.6);
	my_list.push_back(41.7);
	int count=my_list.size();
	for_each(my_list.begin(),my_list.end(),print_double);
	list<double>::iterator iter_s;
	iter_s=my_list.begin();
	cout<<endl;
	cout<<"the third element is "<<*iter_s<<endl;
	cout<<"the third element is "<<*(++iter_s)<<endl;
	cout<<"the third element is "<<*iter_s<<endl;
	cout<<"the third element is "<<*((++iter_s))<<endl;
	cout<<"the third element is "<<*iter_s<<endl;
	cout<<"the third element is "<<*((++iter_s))<<endl;
	cout<<"the third element is "<<*iter_s<<endl;
}
void test_list_assign()
{
	list<double> list_one,list_two,list_three;
	double ele=0.0;
	for(int i=0;i<10;i++)
	{
		ele=i+i/10.0;
		list_one.push_front(ele);
	}
	print_list(list_one);
	list_two.assign(5,5.6);
	print_list(list_two);
	list_three.assign(list_one.begin(),list_one.end());
	print_list(list_three);
}
void test_list_swap()
{
	list<double> list_1,list_2,list_3;
	double ele=0.0;
	for(int i=0;i<10;i++)
	{
		ele=i+i/10.0;
		list_1.push_front(ele);
	}
	cout<<"list_1"<<endl;
	print_list_T(list_1);
	list_2.assign(5,5.6);
	cout<<"list_2"<<endl;
	print_list_T(list_2);
	list_3.assign(list_1.begin(),list_1.end());
	cout<<"list_3"<<endl;
	print_list_T(list_3);
	//------------
	cout<<"----"<<endl;
	list_1.swap(list_2);
	cout<<"list_1��list_2����:"<<endl;
	cout<<"list_1"<<endl;
	print_list_T(list_1);
	cout<<"list_2"<<endl;
	print_list_T(list_2);
	//-----------
	cout<<"----"<<endl;
	swap(list_1,list_3);//ʹ��swap()���㷨��ʽ��������list�����������ݽ���;
	cout<<"list_1��list_3����:"<<endl;
	cout<<"list_1"<<endl;
	print_list_T(list_1);
	cout<<"list_3"<<endl;
	print_list_T(list_3);
}
void test_list_erase_clear()
{
	list<int> mylt;
	for(int i=0;i<10;i++)
	{
		mylt.push_back(i);
	}
	for_each(mylt.begin(),mylt.end(),print_int);
	cout<<endl;
	cout<<"------"<<endl;
	while(!mylt.empty())
	{
		mylt.pop_back();
		for_each(mylt.begin(),mylt.end(),print_int);
		cout<<endl;
	}	
	mylt.clear();
	for(int j=0;j<10;j++)
	{
		mylt.push_back(j*2);
	}
	for_each(mylt.begin(),mylt.end(),print_int);
	cout<<endl;
	cout<<"------"<<endl;
	while(!mylt.empty())
	{
		mylt.erase(mylt.begin());
	}
	for_each(mylt.begin(),mylt.end(),print_int);
	cout<<endl;
}
void test_list_operator()
{
	list<int> list_1,list_2;
	list_1.push_back(1);
	list_1.push_back(2);
	list_2.assign(list_1.begin(),list_1.end());
	cout<<"list_1:";
	for_each(list_1.begin(),list_1.end(),print_int);
	cout<<endl;
	cout<<"list_2:";
	for_each(list_2.begin(),list_2.end(),print_int);
	cout<<endl;
	if(list_1==list_2)
	{
		cout<<"list_1==list_2"<<endl;
	}
	else
	{
		cout<<"list_1!=list_2"<<endl;
	}
	list_1.push_back(1);
	list_2.push_back(3);
	cout<<"list_1:";
	for_each(list_1.begin(),list_1.end(),print_int);
	cout<<endl;
	cout<<"list_2:";
	for_each(list_2.begin(),list_2.end(),print_int);
	cout<<endl;
	if(list_1<list_2)
	{
		cout<<"list_1<list_2"<<endl;
	}
	else if(list_1>list_2)
	{
		cout<<"list_1>list_2"<<endl;
	}
	if(list_1!=list_2)
	{
		cout<<"list_1!=list_2"<<endl;
	}
}
void test_list_merge_sort()
{
	list<int> list_1,list_2,list_3;
	list<int>::iterator iter_1,iter_2,iter_3;
	list_1.push_back(1);
	list_1.push_back(5);
	list_2.push_back(2);
	list_2.push_back(3);
	list_3.push_back(7);
	list_3.push_back(8);

	cout<<"list_1:";
	for_each(list_1.begin(),list_1.end(),print_int);
	cout<<endl;

	cout<<"list_2:";
	for_each(list_2.begin(),list_2.end(),print_int);
	cout<<endl;

	cout<<"list_3:";
	for_each(list_3.begin(),list_3.end(),print_int);
	cout<<endl;

	list_1.merge(list_2);
	list_1.merge(list_3);

	cout<<"list_1_merge_list_2_list_3:";
	for_each(list_1.begin(),list_1.end(),print_int);
	cout<<endl;

	list_1.sort(greater<int>());//��������---�����Ĳ���"greater<int>()"��STL�е�Ԥ����º���
	cout<<"list_1.sort(greater<int>):";
	for_each(list_1.begin(),list_1.end(),print_int);
	cout<<endl;

	list_1.sort();//Ĭ�ϴ�С��������
	cout<<"list_1.sort():";
	for_each(list_1.begin(),list_1.end(),print_int);
	cout<<endl;
}
void Origin_list(list<int>& list_1,int num)
{
	int temp;
	list_1.clear();
	for(int i=0;i<num;i++)
	{
		temp=i+1;
		list_1.push_back(temp);
	}
	for_each(list_1.begin(),list_1.end(),print_int);
	cout<<endl;
}
void test_list_remove_remove_if()
{
	list<int> list_1;
	Origin_list(list_1,9);
	//int temp=9;
	list_1.push_back(9);
	list_1.push_back(8);
	cout<<"output the list_1:"<<endl;
	for_each(list_1.begin(),list_1.end(),print_int);
	cout<<endl;
	list_1.remove(9);
	cout<<"after_remove output the list_1:"<<endl;
	for_each(list_1.begin(),list_1.end(),print_int);
	cout<<endl;

	list_1.remove_if(bind2nd(not_equal_to<int>(),1));
	cout<<"after remove_if output the list_1:"<<endl;
	for_each(list_1.begin(),list_1.end(),print_int);
	cout<<endl;
}
void test_splice()
{
	list<int> list_0,list_1,list_2,list_3;
	list<int>::iterator iter_0,iter_1,iter_2;

	list_0.push_back(9);
	list_0.push_back(-1);
	list_1.push_back(1);
	list_1.push_back(5);
	list_2.push_back(2);
	list_2.push_back(3);
	list_3.push_back(7);
	list_3.push_back(8);

	cout<<"output the list_0:"<<endl;
	for_each(list_0.begin(),list_0.end(),print_int);
	cout<<endl;

	cout<<"output the list_1:"<<endl;
	for_each(list_1.begin(),list_1.end(),print_int);
	cout<<endl;

	cout<<"output the list_2:"<<endl;
	for_each(list_2.begin(),list_2.end(),print_int);
	cout<<endl;

	cout<<"output the list_3:"<<endl;
	for_each(list_3.begin(),list_3.end(),print_int);
	cout<<endl;

	cout<<"output the list_1.splice(list_1.end(),list_2):"<<endl;
	list_1.splice(list_1.end(),list_2);
	for_each(list_1.begin(),list_1.end(),print_int);
	cout<<endl;

	cout<<"output the list_2:"<<endl;
	for_each(list_2.begin(),list_2.end(),print_int);
	cout<<endl;

	cout<<"output the list_1.splice(list_1.end(),list_0,(++list_0.begin())):"<<endl;
	list_1.splice(list_1.end(),list_0,(++list_0.begin()));
	for_each(list_1.begin(),list_1.end(),print_int);
	cout<<endl;

	cout<<"output the list_0:"<<endl;
	for_each(list_0.begin(),list_0.end(),print_int);
	cout<<endl;

	list_1.splice(list_1.end(),list_3,list_3.begin(),list_3.end());
	cout<<"output the llist_1.splice(list_1.end(),list_3,list_3.begin(),list_3.end()):"<<endl;
	for_each(list_1.begin(),list_1.end(),print_int);
	cout<<endl;

	cout<<"output the list_3:"<<endl;
	for_each(list_3.begin(),list_3.end(),print_int);
	cout<<endl;

	list_1.sort(greater<int>());
	cout<<"output the list_1.sort(greater<int>()):"<<endl;
	for_each(list_1.begin(),list_1.end(),print_int);
	cout<<endl;

	list_1.sort();
	cout<<"output the list_1.sort():"<<endl;
	for_each(list_1.begin(),list_1.end(),print_int);
	cout<<endl;

}
void test_unique()
{
	list<int> list_2,list_1;
	not_equal_to<int> Pred;
	list_1.push_back(1);
	list_1.push_back(2);
	list_1.push_back(3);
	list_1.push_back(1);
	list_1.push_back(2);
	list_1.push_back(3);
	list_1.push_back(5);
	list_1.push_back(7);
	list_2.assign(list_1.begin(),list_1.end());
	for_each(list_1.begin(),list_1.end(),print_int);
	cout<<endl;
	for_each(list_2.begin(),list_2.end(),print_int);
	cout<<endl;
	list_1.sort();
	list_1.unique();
	for_each(list_1.begin(),list_1.end(),print_int);
	cout<<endl;
	list_2.sort();
	list_2.unique(Pred);
	for_each(list_2.begin(),list_2.end(),print_int);
	cout<<endl;


}

void main()
{
	//test_bitset();
	//test_3_2();
	//test_vector_1();
	//test_find();
	//test_vector_sort();
	//test_insert();
	//test_bill();
	//test_list_print();
	test_unique();
	//test_vector_bool();
	//test_swap();
	//test_vector_is_empty();
	cin.get();
}

