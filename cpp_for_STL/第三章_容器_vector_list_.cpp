/*
容器是管理序列的类,通过容器类提供的成员函数,实现各种对序列中元素的操作,
是一种高度的泛型抽象,部分发酸也可以应用于容器序列的控制;
STL提供了各种容器模板类,通常这些模板类包含:向量(vector),列表(list),双队列(deque),
集合(set),多重集合(multiset),映射(map),多重映射(multimap);

向量(vector)可以认为是包含一个或者N个更多元素的数组;
列表(list)是由节点组成的双向链表,每个节点包含一个元素;
双队列(deque)是包含N个连续的指向不同元素的指针组成的数组;
集合(set)是由节点组成的,每个节点包含一个元素,节点之间以
		某种谓词排序;
多重集合(multiset)是允许在两个次序相等的元素集合;
映射(map)是由{键,值}对组成的集合,同样以某种谓词排序,
		谓词和数据对有某种作用;
多重映射(multimap)是允许键对包含相等次序的映射;

STL在实现诸多容器类的同时,还实现了部分序列式容器的适配器(adapter);
容器的适配器是针对原有的基本容器的不足,对原有基本容器功能的补充;
所有的适配器不提供迭代器,元素访问通过专有的接口函数实现;
容器适配器严格的说,不是容器，而是使用容器的对象,是在容器的基础上发展出来的;

STL提供的每种容器,都提供了许多操作行为和成员;作为容器的成员,必须满足3个条件:
1.>元素必须是可复制的;所有容器均会产生1份元素副本,不是发生alias(佚名)现象;
所有容器操作行为传回的均是其元素的副本;这就导致复制构造函数的执行非常频繁;
2.>元素必须是可指派(assign)的;容器的成员函数以及STL的各种算法(algorithms)均可
利用assign()函数为元素设定新值;
3.>元素必须是可释放的(经过析构函数释放内存),使用者从容器中将元素删除时,容器
必须释放其元素所占的内存;按这种需求,析构函数不能设置为private类型;

作为容器的成员函数(操作),三种最重要的能力:

1.>容器均能提供value,而非reference(引用),涉及元素操作时,元素满足上述的三个条件;
2.>所有的元素自动形成顺序;即按此顺序可以多次遍历所有元素;这些容器均包含可返回
迭代器的函数,使用这些迭代器可遍历元素;这是算法和容器的关键接口实现;
3.>函数使用者必须确保传递的参数符合要求,否则,可能会导致未定义的行为,通常STL不会抛出异常;


STL容器通常分为3种:序列式容器,关联式容器,容器配接器;
1.>序列式容器(sequence容器),容器中的元素时有序的,但未排序;包括:vector动态数组,
deque双向队列,list双向串行;
2.>关联性容器,容器中的元素都经过排序;包括set,multiset,map,multimap和hash(哈希)table;
3.>容器配接器,是以某种STL容器作为底,修改其接口;具备各自的特点:包括stack,queue,priority_queue;


STL容器的数据结构也包括3种:string字符串,bitset,valarray;

1.>string字符串,其内保存字符;string不是真正的类,而是1个basic_string类的typedef;
2.>bitset,其内保存bits的结构体;每个bit表示1个标志(flag);其长度固定,长度便是模板的自变量;

3.2>序列式容器
对于基本容器,通过增加要求,实现对其的改进;序列是一种重要的改进,6种STL容器(deque,list,queue,
priority_queue,stack,vector)都是序列;
序列最终的特点就是可以在首端删除元素,在尾端添加元素;尤其是双向序列,允许在两端添加和删除元素;
序列中包含至少一种迭代器,从而保证元素按照特定的顺序排列,不会再两次迭代间发生变化;

数组和链表均是序列,但分支结构不是序列;序列中元素具有确定顺序,使用时可以将元素插入特定位置,
删除特定区间等操作;标准库提供的基本序列包括:vector,list,deque;
同时还包括3个适配器:stack,queue,priority_queue;

vector,list,deque 3种序列不可能互相实现,同时又不损失效率;另一方面,stack和queue都可以在
这3中基本序列的基础上高效实现;

vector,list,deque3中容器在使用时,需要分别包含相应的头文件;容器都是类模板,
要定义或实现某种特定的容器对象,必须在容器后加一对尖括号,括号中提供容器存放元素的数据类型;


#include<vector>
#include<list>
#include<deque>

vector <string> svec;
list <int> ilist;
deque <long> litem;

3.3序列式容器--vector类模板
template <class T,class Allocator=allocator<T>> class vector;
vector中的元素可以是任意类型T,必须具备可设置,可复制两个属性;模板的第二个参数是关于空间配置器设置的,用于
定义内存模型,默认内存模型是C++标准库提供的allocator,对于一般的程序员来说,可有可无;
vector是最简单的序列式容器,支持随机访问元素;有时候会显得效率低一些;vector的大小与容量之间有重要差别;
容量肯定是大于或者等于其大小;

vector就行一个动态数组,是典型的"将元素置于动态数组中加以管理"的抽象概念;在C++标准中,并未规定必须以
动态数组来实现vector,仅规定了相应的条件和操作复杂度;在程序开发过程中,程序员使用vector作为动态数组是非常
方便的;vector的迭代器是随机存起迭代器,对任何一个STL算法均奏效;
尤其在末端或删除元素时,vector性能相当好;

vector 可以实现数据结构中的队列,数组和堆栈的所有功能;vector一旦定义了类对象之后,就可以装东西了;

容器的大小和容量
vector类模板定了两个函数(size和capacity),实现统计容器元素的目的;还定义了两个函数(resize和reserve),
实现设置容器大小的目的;
size()和capacity()可以统计容器中元素的数量;size()函数返回容器中现有元素的数量;
capacity()函数返回容器中实际能够容纳的元素数量;
函数max_size()可以返回容器所能容纳的最大元素数量;
一般情况下,元素数量超越capacity()返回的数值时,vector有必要重新配置内存存储器;
函数reserve()可以预先设置容器的大小;函数resize()可以修改容器的大小;
函数reserve()可以保留适当的容量，避免重新配置内存;
在定义容器对象时,通过传递函数的形式,可以设置vector的起始大小;

遍历vector型容器
可以使用迭代器方法实现遍历,也可以通过使用at()函数和循环语句实现;

3.使用算法
使用STL vector, 还可以通过使用部分算法,实现对vector的操作;

3.3.3 vector高级编程
vector容器相关的元素访问方法,迭代器相关函数,元素查找和搜索,
vector型容器中的字符串处理,元素排序,插入元素,删除元素,对象交换;

2.迭代器相关函数
vector类模板提供部分常规函数来获取迭代器;迭代器是随机访问迭代器,通过迭代器
甚至可以操作所有算法;和迭代器相关的函数主要包括:begin(),end(),rbegin(),read();
其中begin()指向第一个元素;end()指向最后一个元素的下一个位置;rbegin()指向逆向迭代的
第一个元素;rend()指向逆向迭代的最后一个元素的下一个位置;
函数begin()和end()返回值类型均为迭代器类型;
函数rbegin()和rend()返回值类型的逆向迭代器;

3.元素查找和搜索
查找vector型容器中的元素,可以使用STL的通用算法find();
有条件搜索相关元素可以使用算法find_if();
这两个算法均可以使用迭代器,两个迭代器参数决定了搜索和查找
的范围;函数返回值均为迭代器类型;

template<class InputIterator,class T> inline InputIterator find(InputIterator first,
InputIterator last,const T&value);

template<class InputIterator,class T,class Predicate> inline InputIterator find(InputIterator first,
InputIterator last,const T&value,Predicate predicate);

3.3.4vector型容器中的字符串处理
使用vector管理字符串,可以处理字符串中的每个字符,并且vector可以自动管理内存;
字符串中的每一个字符作为向量vector容器的元素,使用容器的所有成员函数可以
方便完成字符串的操作;
3.3.5元素排序
实现对vector容器中元素的排序需要使用算法sort()或其他的排序算法;有些容器支持对特殊算法
的实现,使用算法排序,有助于提高计算性能;但vector向量没有提供具有排序算法的成员函数;

3.3.4插入元素
在现在的vector型容器中插入或增加一个新的元素,可以使push_back()函数将元素加入vector型对象(容器)的末尾;
还可以使用insert()函数将对象插入vector中的任意位置,即insert()函数可以实现在迭代器指向位置插入元素;
insert()函数返回值为迭代器,指向刚插入的元素;还可以再迭代器指定位置插入多个连续的不同元素,还可以插入
多个值相同的元素;函数push_back和函数insert()的原型如下:

template<class _TYPE,class_A>void vector::push_back(const _TYPE& X);//push_back()模型
iterator insert(iterator it,const T&x=Y());//insert()函数的3个模型
void insert(iterator it,size_type n,const T&x);
void insert(iterator it,const_iterator first,const_itearator last);

3.3.7删除元素
在定义vector型容器,需要初始化其元素;并且定义vector时同时使用另外STL容器中的区间数据来初始化;
该STL容器不必是vector型对象;只要元素的类型相同即可;

vector<int> Harry;
Harry.push_back(1);
Harry.push_back(2);
vector<int>Bill(Harry.begin(),Harry.end())

删除容器中的元素,可以使用3个成员函数:pop_back(),erase()和clear();还可以使用算法库
的算法remove()来实现;
pop_back()函数删除最后一个元素,函数erase()可以删除由迭代器指定的元素,也可以删除
区间范围的元素;clear()函数实现删除向量vector的所有元素,相当于erase(begin(),end());


3.3.8交换对象
vector类模板还提供了成员函数swap(),用于两个vector型容器之间的元素互相交换;如果两个参与交换
的vector类型相同,对象交换会瞬间完成;如果两个参与交换的vector对象的元素类型不同,在实现对象
交换的过程中,需要执行非常复杂的操作;
template<class T,class A> void swap(const vctor<T,A>&v1,const vector<T,A>&v2);

3.3.9vector<bool>类
C++标准程序库专门针对元素类别为bool的vector设计了特殊版本,目的是获取优化的vector;
其所占用的内存空间远小于一般的vector模板实例化的bool型向量(容器);
普通的vector类模板会分配1个byte空间;而vector<bool>只占用1个bit存储单个元素;
所占内存空间小8倍;
C++的最小寻址通常以byte为单位,在类vector<bool>中需针对reference和iterator进行特殊考虑;
类vector<bool>的操作要比普通的vector慢很多,所有元素操作必须转换为bit操作;
类vector<bool>不仅仅是向量型的容器类,还提供位操作,非常方便地操作"位"和"标志",
所有用于元素存取的函数,返回值均为应用型(reference);
vector<bool>类提供了位取反函数flip(),既可以实现对容器中所有元素取反,还可以对某"位"取反;
-----------------------
3.4序列式容器----list类模板
模板类list是一个容器,list是由双向链表来实现的,每个节点存储1个元素;list支持前后两种移动方向;
list和vector类似,提供了对元素的随机访问;list的优势在于任何位置执行插入和删除动作都非常迅速,
因为改变的仅仅是链接而已;在list中移动元素要比在vector和deque中快得多;
list模板类是定义于命名空间(namespace)std中的,该类模板的声明形式为:
template<class T,class Allocator=allocator<T>> class list;

使用list需要包含头文件<list>;任意型别T只要具备可设置性和可复制性,即可作为list元素;
模板的第二个参数可有可无,适用于指定内存模型;在模型中也指定了默认的内存模型为allocator;
List的内部结构和vector不同,存在较明显的区别;

1.>list不支持随机存取;
2.>在list的任何位置执行元素的插入和移除都非常快,可以快速实现;插入和删除动作不会影响指向
其他元素的指针,引用,迭代器不会噪声失效;
3.>list不支持随机存取,不提供下表操作符和at()函数;
4.>list没有提供容量,空间重新分配等操作函数;
5.>list也提供了特殊成员函数,专门用于移动元素,和同名的算法相比,速度更快;
list模板类实现了标准C++数据结构中链表的所有功能;list一旦定义了类对象之后,
就可以完成链表操作;

3.4.1 list的定义和容量
1.list的定义和构造函数
该模板类描述的对象控制是一个元素类型为T的可变长度序列;该序列以双向链表的方式存储,
链表中每个元素都包含一个类型为T的成员;list对象通过存储于其内部的一个类A的分配器对象进行
存储空间的分配和释放;该分配器对象必须拥有和模板类allocator同样的外部接口;

在头文件list中定义了4中构造函数
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
list<A> listname(elselist);//复制构造函数
list<A> listname(first,last);//创建一个list对象,并从其他list对象中复制由迭代器指定范围的多个元素;

2.元素的赋值
list模板类提供了两个成员函数push_front()和push_back(),用来把新的元素插入list对象中;
push_front()用来在容器中的头部插入新元素,由于vector在头部插入新元素的效率非常低,
所以只在list中存在该函数,另外还有两个函数pop_front()和pop_back()分别用于获取
容器的头和容器的尾元素;
void push_front(const T&x);
void push_back(const T&x);
void pop_front();
void pop_back();
3.4.3容器的容量
list对象作为容器,和其容量相关的成员函数包括:resize(),size(),max_size()
size_type size() const;
size_tye max_size() const;
void resize(size_type n,T x=T());
函数size()和max_size()的返回类型均为size_type型,即unsigned int类型;
size()用于返回list对象(容器)中元素的个数;max_size()用于返回list对象最大允许容量,
一般是一个非常大的整数,函数resize()用于重新调整list对象的大小;

3.4.4迭代器相关
list模板类包含和迭代器相关的函数主要有:begin(),front(),rbegin(),end,back(),rend();

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

3.4.2 list容器基础成员函数
list容器最基础的编程内容包括:判断list内容是否为空,元素存取,元素重置,交换两个容器内容,
list序列中元素的插入和删除等;
1.判断容器是否为空
如果list型容器为空,成员函数empty()返回true;函数empty()的原型为:
bool empty() const;
2.list型容器中元素的存取和访问
list型容器不提供成员函数at()和操作符operator[],对容器中的元素访问有些不便'
使用迭代器进行元素的访问;
3.元素重置
在list型容器中提供了可以重置元素值的成员函数assign();
使用函数assign()可以修改容器中任意元素的数值,甚至可以修改多个
连续元素的数值;assign()的原型:
void assign(const_iterator first,const_iterator last);
void assign(size_type n,const T&x=T());
4.交换两个list容器的内容
模板类list提供了成员函数swap();可以实现两个list型容器(对象)的内容交换;
通过swap()函数完成两个list容器中元素交换的同时,容器的大小也发生了变化;
在STL的算法库中,也提供了swap()函数;作为通用算法同样可以实现交换两个list
容器中的内容;

5.元素的插入和删除
模板list和其他型容器一样,提供了丰富而灵活的插入和删除元素操作;
尤其list型容器提供了较完善的插入和删除操作;list型容器可以在序列的
开头和队尾灵活的插入和删除元素;涉及的成员函数主要包括:push_back(),
push_front(),pop_back(),pop_front(),insert(),erase()和clear()
push_front和push_back()均可以轻松的插入元素至序列中,
pop_back()和pop_front()也可以轻松的实现从首端或尾端将元素
从序列中移除;

成员函数insert()的原型分为以下三种形式:

iterator insert(iterator it,const T&x=T());//在与把某个元素插入指定位置
void insert(iterator it,size_type n,const T&x);//把某个具体值的多个备份插入list中迭代器所指起始位置;
void insert(iterator it,const_iterator first,const_iterator last);//主要用于把一个指定范围的多个元素插入list中迭代器所指向的范围中;


iterator erase(iterator it);//删除迭代器所指向的元素
iterator erase(iterator first,iterator last);//删除迭代器所定义的范围；

clear()相当于使用erase()删除序列中的所有元素;erase(begin(),end());

3.4.3运算符函数
list型容器也提供了大量的模板函数,提供了大量运算符函数;
常见的包括:operator==,operator<,operator!=,operator<=,operator>,operator>=;

1.operator==
operator[]的基本使用方法主要是读取list中的元素,而云算法operator==则是判断语句,
用于判断两个list容器是否相等;如果相等返回,true;
bool operator==(const list<Type,Allocator>& _Left,const list<Type,Allocator>& _Right);
上式表明,参与比较的两个list对象的格式应该完全一样,不能使用两个类型不同的容器进行比较;

2.operator<
运算符operator<依然是用于判断,它用来判断两个list容器是否"前者小于后者",
如果是返回true,否则返回false;

bool operator<(const list<Type,Allocator>& _Left,const list<Type,Allocator>&_Right);

3.4.4其他重要成员函数
list型容器具有一些特殊函数:函数merge(),remove(),remove_if(),sort(),splice(),unique();

1.函数merge()和sort()
函数merge()可以实现将两个list型对象合并成一个list对象;函数的功能在于把原型中的list
容器对象作为函数参数,插入目标list(函数的调用者)中;合并之后的容器中元素是按从小到大
升排列的;
void merge(list &x);
void merge(list &x,greater<T>pr);
void sort();
void sort(greater<T>pr);

2.函数remove()和函数remove_if()
void remove(const Type& _Val);
可以实现删除list容器中某个具体的元素;remove()函数不需要指定具体位置,只要告诉需要
删除的元素的值,就可以直接删除所有相应的元素;remove()不改变容器中元素的顺序,
而且会删掉所有等于参数(指定数值_Val)的元素;
template <class Pred> void remove_if(Pred pr);
仅删除满足条件"Pred pr"的相应元素;
typedef binder2nd<not_equal_to<_Ty>> Pred;
只有当Pred pr为true时,才能正确执行删除操作;

3.splice()
void splice(iterator it,list& x);
void splice(iterator it,list& x,iterator first);
void splice(iterator it list& x,iterator first,iterator last);

4.函数unique()
成员函数unique()会移除重复元素仅留下一个;
void unique()
template<class BinaryPredicate>void unique(BinaryPredicate _Pred);
函数unique()嘉定容器中元素时已经排序的,因此所有相同的元素都是相邻的,不相邻的
重复元素不能移除;
unique()不能保证序列中元素值的唯一性,仅仅是将相邻的重复元素保留一个;
使用list容器的成员函数unique时,尽量先使用sort()对容器中的元素进行排序;

5.函数reverse()
reverse()实现将容器中所有元素与原来相反的顺序排序
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
//定义子进程
bool name_sort_less(const student& m,const student&n)
{
	return m.name<n.name;
}
//定义子进程
bool name_sort_greater(const student& m,const student&n)
{
	return m.name>n.name;
}
//定义子进程
bool score_sort(const student& m,const student&n)
{
	return m.score>n.score;
}
//定义子进程
void print_student(student& s)
{
	cout<<s.name<<"  "<<s.score<<endl;
}
//初始化
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
	bitset<10> bs1(7);//bitset中长度为10个bit;初始化为10进制的7;
	bitset<10> bs2(string("1000101011"));//初始化为10个字符长度的字符串
	cout<<bs1<<endl;
	cout<<bs2<<endl;
	return;
}
void test_3_2()
{
	valarray<int> va1(4);//包含4个元素,但是未指定元素的值;
	print_Valarray(va1);

	valarray<int> va2(3,4);//包含4个元素,其数值均为3
	print_Valarray(va2);

	int ia[]={1,2,3,4,5,6};//定义整数型数组
	valarray<int> va3(ia,sizeof(ia)/sizeof(ia[0]));//动态数组大小和 数组ia的元素个数相同
	print_Valarray(va3);

	valarray<int> va4(ia+1,4);//包含4个元素,其数值均为ia的前4个元素加1
	print_Valarray(va4);

	va1=(va2+va4)*va4;//
	print_Valarray(va1);
}
void test_vector_1()
{
	vector<string> my_vector;
	my_vector.reserve(4);//使用reverse()函数预先设置容器的大小
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
void print_ele(int &Ele)//输出元素
{
	cout<< Ele<<",";
}
void print_double(double &ele)
{
	cout.width(5);//格式化输出,宽度5个字符,保留1位小数点
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
//测试find_find_if有问题
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
	//cout<<"数字2的下标是:"<<(location_index-myvector.begin())<<endl;
	//location_index=find_if(myvector.begin(),myvector.end(),bind2nd(greater<int>(),5));
	//cout<<"大于5的下标是:"<<(location_index-myvector.begin())<<endl;
}
void test_vector_sort()
{
	vector<student> vect;
	Original_student(vect);
	cout<<"before sort"<<endl;
	for_each(vect.begin(),vect.end(),print_student);
	sort(vect.begin(),vect.end());//按score从小到大排序(使用operator<)
	cout<<"------"<<endl;
	cout<<"after sort by sort"<<endl;
	for_each(vect.begin(),vect.end(),print_student);

	sort(vect.begin(),vect.end(),name_sort_less);//按name从小到大排序
	cout<<"------"<<endl;
	cout<<"after sort by name_sort_less"<<endl;
	for_each(vect.begin(),vect.end(),print_student);

	sort(vect.begin(),vect.end(),score_sort);//按score从大到小排序
	cout<<"------"<<endl;
	cout<<"after sort by score_sort"<<endl;
	for_each(vect.begin(),vect.end(),print_student);

	sort(vect.begin(),vect.end(),name_sort_greater);//按score从大到小排序
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
	//待续-----
	//for_each(vt.begin(),vt.end(),print_bool);
	cout<<endl;
	vt[3]=bool(1);
	//待续------
	//for_each(vt.begin(),vt.end(),print_bool);
	cout<<endl;
}
void test_list_print()
{
	list<string> mylist_string;
	list<double> mylist_double(6);

	//初始化mylist_string
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
	//--输出各个容器中的元素
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
	//各容器的容量;
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
	//再次输出各点

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

	//使用迭代器相关的函数
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
	end()所指向的元素分别是容器中最后一个元素,程序输出end()返回的数值时,并不是最后一个元素的数值;
	同理rend*();
	在使用迭代器进行for循环时,一般循环终止条件时(iterator!=end()),即循环至end()返回值指向的位置时,
	(恰好是容器中最后一个元素的后面),停止循环;
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
	cout<<"list_1和list_2交换:"<<endl;
	cout<<"list_1"<<endl;
	print_list_T(list_1);
	cout<<"list_2"<<endl;
	print_list_T(list_2);
	//-----------
	cout<<"----"<<endl;
	swap(list_1,list_3);//使用swap()的算法形式进行两个list型容器的内容交换;
	cout<<"list_1和list_3交换:"<<endl;
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

	list_1.sort(greater<int>());//降序排序---函数的参数"greater<int>()"是STL中的预定义仿函数
	cout<<"list_1.sort(greater<int>):";
	for_each(list_1.begin(),list_1.end(),print_int);
	cout<<endl;

	list_1.sort();//默认从小到大排序
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

