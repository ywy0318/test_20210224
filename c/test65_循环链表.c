#define _CRT_SECURE_NO_WARNINGS
#include<dos.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<windows.h>
#include<conio.h>

//ѭ������ֻ�ܴ�һ�������ϱ�����

/*
���۾�̬�����Ƕ�̬����,��ʱ�ڽ����������ʱ����Ҫ���Ƕ���ṹ������΢�ص���;
����,���԰��������ͷ���ӣ�ʹ���Ϊ��һ����״����ͨ����Ϊѭ������;
���������ֵı���һ����ֻ��Ҫ���������һ���ڵ��ָ��ָ��ͷ��㣬������ܳɻ�;
��Ҫע�����:��Ȼѭ������ɻ�״���������ϻ���������Ȼ�ܹ��ҵ�ͷָ�룬����Ԫ�ڵ��;
ѭ���������ͨ������ȣ�Ψһ�Ĳ�ͬ����ѭ��������λ��������������ȫһ��;
*/
/*
ѭ������ʵ��Լɪ��
Լɪ������,��һ�������ѭ����������,������:��֪n����(�ֱ��ñ��1,2,3,...n��ʾ)Χ����һ��Բ����Χ,
�ӱ��Ϊk���˿�ʼ˳���뱨��;����m���Ǹ��˳��У�������һ���ִ�1��ʼ������˳ʱ�뿪ʼ����������m��
�Ǹ��˳���,�����ظ���ȥ��֪��Բ����ʣ��һ���ˣ�
�����ʱԲ��Χ��5���ˣ�Ҫ��ӱ��Ϊ3��ʼ˳ʱ������������2���Ǹ��˳���;
���Ϊ3���˿�ʼ��1��Ȼ��4��ʼ��2������4����;
4�����Ժ󣬴�5��ʼ��1��1��2������1����;
1�����Ժ󣬴�2��ʼ��1��Ȼ��3��2������3����
3�����Ժ󣬴�5��ʼ��1��Ȼ��2��2������2����
���ֻʣ��5������5ʤ��;
Լɪ�����⣬�ж��ֱ���,����˳ʱ���Ϊ��ʱ�룬��Ȼ�����ϸ���ж��ֱ�����
��������������˼����һ���ģ�ʹ��ѭ������;

ѭ������Ͷ�̬����Ψһ��ͬ����������λ���ӣ���Ҳע������ʹ��ѭ������ʱ��
�������Ĳ������Ǳ�������,
�ڱ����Ĺ����У�����Ҫע��ѭ��������Ȼ��β����������������
������û�е�һ���ڵ�����һ���ڵ㣬���Բ�Ҫ����ı�ͷָ���ָ��;

*/


/***************����*******************/
#define N 5
typedef struct node
{
	int number;
	struct node *next;
}person;

//����ͷ�����headָ��
person *init_Link(int n)
{
	int i=0;
	
	person *cyclic=NULL;
	person *body=NULL;
	person *head =(person*)malloc(sizeof(person));
	head->number=1;
	head->next=NULL;
	//printf("%d\n",head->number);
	cyclic=head;
	printf("--init_start--\n");
	printf("%x,%x,%d\n",&cyclic,&head,cyclic->number);
	for(i=2;i<=n;i++)
	{
		body=(person*)malloc(sizeof(person));
		body->number=i;
		body->next=NULL;
		//
		cyclic->next=body;		
		cyclic=cyclic->next;
		printf("%x,%x,%d\n",&cyclic,&cyclic->next,cyclic->number);
		//printf("%d\n",cyclic->number);
	}
	//���һ����ʱ���ָ���л���head����,
	cyclic->next=head;
	printf("\n");
	printf("%x,%x %d\n",&cyclic,&cyclic->next,cyclic->number);
	printf("--init_end--\n");
	return cyclic;
	//return head;
}
void show_list(person *head_1)
{
	person *temp=head_1;
	int length=0;
	if(head_1==NULL)
	{
		printf("head is null\n");
		exit(-1);
	}
	printf("%d\n",temp->number);
	for(temp=head_1->next;temp!=head_1;temp=temp->next)
	{
		printf("%d\n",temp->number);
		length++;
	}
	printf("length=%d\n",length);
	printf("---\n");
}
void find_kill(person *head,int m,int k)
{
	person *tail=head;
	person *p=head;
	int i=1;
	//�ҵ������һ���ڵ����һ���ڵ㣬Ϊɾ��������׼��
	//while(1)
	//{
	//	if(tail->next==head)
	//	{
	//		break;
	//	}
	//	tail=tail->next;
	//}

	while(tail->next!=head)
	{
		tail=tail->next;
	}
	printf("tail->number:%d\n",tail->number);
	//while(1)
	//{
	//	printf("%p,%p\n",head,tail->next);
	//	if(tail->next!=head)
	//	{
	//		tail=tail->next;
	//	}
	//	else
	//	{
	//		break;
	//	}
	//}

	//�ҵ����Ϊk����
	while(p->number!=k)
	{
		tail=p;
		p=p->next;
	}
	printf("K:%d-%d\n",tail->number,p->number);
	
	//�ӱ��Ϊk���˿�ʼ��ֻ�з���p->next==pʱ,
	//˵�������г���p�ڵ����⣬���б�Ŷ�������;
	while(p->next!=p)
	{
		//�ҵ���p����1��ʼ����m���ˣ����һ�Ҫ֪����m-1���˵�λ��tail,
		//������ɾ������
		for(i=1;i<m;i++)
		{
			tail=p;
			p=p->next;
		}
		tail->next=p->next;//�������Ͻ�p�ڵ�ժ����
		printf("���е��˵ı��:%d\n",p->number);
		free(p);
		p=tail->next;//����ʹ��pָ��ָ���г���ŵ���һ����ţ���Ϸ����
	}
	printf("�����е��˵ı��:",p->number);
	free(p);
}

int main()
{	
	person *headp=init_Link(N);
	show_list(headp);
	find_kill(headp,N,3);
	
	system("pause");
	return 0;
}