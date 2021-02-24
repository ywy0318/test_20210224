#define _CRT_SECURE_NO_WARNINGS
#include<dos.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<windows.h>
#include<conio.h>

//˳��洢�ṹ����ʽ�洢�ṹ(���Ա�洢���ݿ��Է�Ϊ����:�������ͱ���һ��)
//������һ�δ洢�����������������ڴ��У����ִ洢�ṹ��Ϊ˳��洢�ṹ(���˳���)
//���ݷ�ɢ�Ĵ洢������ռ���(�ڴ��ַ������),ͨ��һ���߱���������֮����߼���ϵ,���ִ洢�ṹ��Ϊ��ʽ�洢�ṹ(����)

//ָ����=����������*��realloc��Ҫ�ı��ڴ��С��ָ�������µĴ�С����
//�µĴ�С�ɴ��С������µĴ�С����ԭ�ڴ��С�����·��䲿�ֲ��ᱻ��ʼ��������µĴ�СС��ԭ�ڴ��С�����ܻᵼ�����ݶ�ʧ [1-2]  ��


#define SIZE 5
typedef struct Table
{
	int *head;//������һ����Ϊhead�ĳ��Ȳ��������飬Ҳ�ж�̬����
	int length;//��¼��ǰ˳���ĳ���
	int size;//��¼˳������Ĵ洢����
}table;

//��ʼ��
table init_table()
{
	table t;
	t.head=(int*)malloc(SIZE*sizeof(int));//����һ���յ�˳���,��̬����洢�ռ�
	if(!t.head)
	{
		printf("init table failed!\n");
		exit(0);
	}
	t.length=0;//�ձ�ĳ�ʼ������Ϊ0
	t.size=SIZE;//�ձ�ĳ�ʼ���ռ�ΪSIZE
	return t;
}
void display_table(table t)
{
	int i=0;
	//printf("start\n");
	for( i<0;i<t.length;i++)
	{		
		printf("%d  ,0x%x\n",t.head[i],&t.head[i]);
	}
	//printf("end\n");
}
//���뺯��,Ҫ�����table,Ԫ�أ�λ��index�������еڼ���Ԫ�ض�������ֵ
table insert_table(table t_for_insert,int element,int index_for_insert)
{
	int i=0;
	//�жϲ��뱾���Ƿ��������,(�������Ԫ��λ�ñ����ű�ĳ���+1����(��ȣ���β������)),
	//���߲����λ�ñ������ڣ�������ʾ���Զ��˳�
	if((index_for_insert>t_for_insert.size+1)||(index_for_insert<1))
	{
		printf("����λ��������");
		return t_for_insert;
	}
	//�������ʱ,������Ҫ����˳������Ƿ��ж���Ŀؼ��ṩ���룬���û�ж���ģ���������
	if(t_for_insert.length==t_for_insert.size)
	{
		t_for_insert.head=(int *)realloc(t_for_insert.head,sizeof(int)*(t_for_insert.size+1));
		if(!t_for_insert.head)
		{
			printf("realloc failed\n");
			return t_for_insert;
		}
		t_for_insert.size+=1;
	}
	////�������,��Ҫ��Ҫ�����λ�ú����Ԫ�أ������ƶ�
	//for(i=t_for_insert.length-1;i>=index_for_insert-1;i--)
	//{
	//	t_for_insert.head[i+1]=t_for_insert.head[i];
	//}

	//���Ʋ���,�������Ҫ����Ԫ�صĸ���index_for_insert���Ϊ�ڼ���Ԫ��,
	//֮ǰ��length��Ԫ��,��Ҫ�ƶ�����Ԫ��length-(index_for_insert-1)
	//ʵ���ƶ�index_for_insert-1Ԫ��������	
	for(i=0;i<t_for_insert.length-index_for_insert+1;i++)
	{
		t_for_insert.head[t_for_insert.length-i]=t_for_insert.head[t_for_insert.length-1-i];
	}

	//display_table(t_for_insert);
	//
	t_for_insert.head[index_for_insert-1]=element;
	
	t_for_insert.length+=1;
	//display_table(t_for_insert);
	return t_for_insert;
}
//index_for_del��ɾ���ڼ���Ԫ�ز�������
table delete_table(table t_for_del,int index_for_del)
{
	int i=0;
	if((index_for_del>t_for_del.length)||(index_for_del<1))
	{
		printf("��ɾ����Ԫ������");
		exit(0);
	}
	//ֱ�ӰѺ������ǰ�ƶ���ֱ�Ӹ���
	for(i=index_for_del-1;i<(t_for_del.length-1);i++){
		t_for_del.head[i]=t_for_del.head[i+1];
	}
	t_for_del.length-=1;

	return t_for_del;
}

//�޸ģ��Ҳ����˳�
table update_table(table t_for_up,int old_element,int new_element)
{
	int ret=-1;
	ret=search_table(t_for_up,old_element);
	if(ret<0)
	{
		printf("Ԫ�ز�����");
		exit(0);
	}
	else
	{
		t_for_up.head[ret-1]=new_element;
	}
	return t_for_up;
}
//���� �����ڷ���-1,���ڷ��صڼ�������
int search_table(table t_for_table,int element_for_search)
{
	int i=0;
	for(i=0;i<t_for_table.length;i++)
	{
		if(t_for_table.head[i]==element_for_search)
		{
				return i+1;
		}
	}
	return -1;
}

int main()
{	
	int j=0;
	int ret=-1;
	table t=init_table();
	//��˳��������Ԫ��
	for(j=0;j<t.size;j++)
	{
		t.head[j]=j;
		t.length++;
	}
	printf("%d\n",t.length);
	printf("display_table:\n");
	display_table(t);
	printf("insert\n");
	ret=search_table(t,22);
	if(ret>0)
	{
		printf("serach::%d\n",ret);
	}
	else
	{
		printf("search failed\n");
	}
	t=update_table(t,1,102);
	//t = delete_table(t,1);
	//t=insert_table(t,444,6);
	printf("after insert:\n");
	display_table(t);

	system("pause");
	return 0;
}