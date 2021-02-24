/*遍历的时候有问题*/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
using namespace std;

class node
{
public:
	node();
	node(int data);
	~node();
	static node* head;//链表头
	static node* tail;//链表尾

	/*向链表尾部添加结点*/
	static void addnode(int data)
	{
		if (head == NULL)
		{
			head = new node(data);
			tail = head;
			return;
		}
		tail->next = new node(data);
		tail = tail->next;
	}
	static void addnode(node *n)
	{
		if (head == NULL)
		{
			head = n;
			tail = head;
			return;
		}
		tail->next = n;
		tail = tail->next;
	}
	/*根据数据内容删除结点*/
	static bool deletnode(int data)
	{
		bool flag = false;
		if (head == NULL)
		{
			return flag;
		}
		/*遍历查找符合条件的结点*/
		node* temp=head;
		if (head->data== data)
		{
			temp = head->next;
			delete head;
			head = temp;
		}
		if (head == NULL)
		{
			return true;
		}
		node* move = head->next;
		while (move!=NULL)
		{
			if (move->data == data)
			{
				temp->next = move->next;
				delete move;
				move = temp->next;
			}
			else
			{
				/*移动迭代指针*/
				move = move->next;
				temp = temp->next;
			}
		}
		return flag;
	}
	static void getnodesmessage()
	{
		if (head == NULL)
		{
			printf("linked is empty\n");
			return;
		}
		node *move = head;
		while(move!=NULL)
		{
			printf("%d->",move->data);
			move=move->next;
		}
		printf("NULL\n");
	}

private:
	int data;
	node* next;
};

node::node()
{

}
node::node(int data)
{
	this->data = data;
	this->next = next;
}

node::~node()
{
}
node* node::head = NULL;
node* node::tail = NULL;
int main()
{
	node::getnodesmessage();
	cout << "add junction\n" << endl;

	node* n1 = new node(4);
	node* n2 = new node(*n1);

	node::addnode(n1);
	node::addnode(5);
	node::addnode(6);
	node::addnode(7);
	node::addnode(8);
	node::addnode(n2);
	
	node::getnodesmessage();
	printf("delete data==4\n");
	node::deletnode(4);
	node::getnodesmessage();

	system("pause");
	return 0;
}