#define _CRT_SECURE_NO_WARNINGS
#include<dos.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<windows.h>
#include<conio.h>
#define SIZE 24
/*
��̬����Ͷ�̬���������
��̬����Ͷ�̬����Ĺ�ͬ���ǣ�����֮��"һ��һ"���߼���ϵ��������ָ��
(��̬�����г�Ϊ"�α�")��ά�֣����˶���;


��̬����:
ʹ�þ�̬����洢���ݣ���ҪԤ�������㹻���һ�����ڴ�ռ䣬Ҳ����˵����̬����洢����Ԫ�ص�
���������䴴������һ�̾��Ѿ�ȷ���������޷�����;
���磬���������̬����ʱֻ����洢10������Ԫ�صĿռ䣬��ô��ʹ�þ�̬����ʱ,
���ݵĴ洢�����Ͳ��ܳ���10�����������ͻᷢ������;
������ˣ���̬�����ڹ̶���С�Ĵ洢�ռ�������洢��������Ԫ�أ��������˾�̬��������Ҫʹ��
��һ������(��������),����¼�ռ�洢�ռ��λ�ã��Ա���ڷ���������Ԫ��ʹ�ã�
����ζ�ţ����ʹ�þ�̬����洢���ݣ���Ҫͨ���ٿ���������һ���洢����,
��һ���Ǽ�¼�ռ��λ��;

��̬����
ʹ�ö�̬����洢���ݣ�����ҪԤ�������ڴ�ռ䣬��������Ҫ��ʱ������ڴ�����;
Ҳ����˵����̬����洢����Ԫ�صĸ����ǲ��޵ģ������پʹ����;
ͬʱ��ʹ�ö�̬������������̣���Ҳֻ��Ҫ�ٿ�һ���洢���ݵ�����
��������ӻ���ɾ������Ԫ��ʱ��ֻ��Ҫʹ��malloc����free����������ͷſռ伴��;

*/

//static linked list
typedef struct
{
	int data;
	int cur;
}sll;

void reserved_sll(sll* array_2){
	int i=0;
	for(i=0;i<SIZE;i++)
	{
		array_2[i].cur=i+1;
	//	printf("reserved_sll:%d\n",array_2[i].cur);
	}
	array_2[SIZE-1].cur=0;
	//printf("reserved_sll:%d\n",array_2[SIZE-1].cur);

}
int get_null_sll(sll* array_3)
{
	int i=0;
	i=array_3[0].cur;
	if(i>0)
	{
		array_3[0].cur=array_3[i].cur;
	}
	return i;
}
int get_index_sll(sll* array_6,int tm)
{
	int i=0;
	int tmp=0;
	int ret=-1;
	for(i=0;i<SIZE;i++)
	{
		tmp=array_6[i].cur;
		//printf("%d==%d\n",tm,tmp);
		if(tm==tmp)
		{
			ret=i;
			break;
		}
	}
	return ret;
}
void init_sll(sll *array_1){
	int i=0;
	int j=0;
	int temp=1;
	int temp_backup=0;
	reserved_sll(array_1);
	//
	
	for(i=0;i<5;i++)
	{	
		temp=get_null_sll(array_1);
		temp_backup=temp;
		array_1[temp].data=i+10;
		array_1[0].cur=array_1[temp].cur;
		//temp=get_null_sll(array_1);
		//temp=array_1[temp_backup].cur;		
	}
	array_1[temp_backup].cur=0;
	array_1[SIZE].cur=0;
}
void dispaly_all(sll *array_4)
{	
	int i=0;
	printf("---\n");
	for(i=0;i<SIZE;i++)
	{
		printf("i:data:cur:%d,%d,%d\n",i,array_4[i].data,array_4[i].cur);
	}
}

//�������в������ݣ�body��ʾ�����ͷ����������е�λ�ã�add��ʾ����Ԫ�ص�λ�ã�a��ʾҪ���������
//void insertArr(component * array,int body,int add,char a)
//void insert(sll* array_5,int body,int add,char a)
//cur--�α��������һ����˳�����еĿ�����4-3-5
void insert(sll* array_5,int add,int a)
{
	//��Ҫ�Ķ������ط�����һ��֮ǰ��������������һ��ֵ,�ڶ���0������α�ֵ������Ҫ������������α�ֵ
	//body�������ṹ������ʹ�ã����ܾ�̬�����Ǵ�a[1]��ʼ�ģ�
	//
	//�ҵ�֮ǰ�İ�����Ч���ݵ������������Ȼ��׼���޸���������
	//�ҵ���ǰ��������Ϊ0��ʱ���Ӧ���α�ֵ�����Ӧ������һ�����õı�������
	int i=0;
	int index=0;
	int tmp=0;
	int tmp_for_add=-1;
	int tem_for_0=-1;
	int tmp_cur=0;
	int tmp_cur2=0;
	int cur_for_add=0;
	//��ȡ������������һ��ֵ
	
	tmp=get_index_sll(array_5,0);//�����������ת��0��
	if(tmp==-1)
	{
		printf("insert failed\n");
		exit(-1);
	}
	//printf("add\n");
	tmp_for_add=get_index_sll(array_5,add);//Ҫ������������α�ֵ
	if(tmp==-1)
	{
		printf("insert failed\n");
		exit(-1);
	}
	//tem_for_0=get_index_sll(array_5,0);//0���α�ֵ
	tem_for_0=array_5[0].cur;
	//��ȡ����֮ǰҪ�����������α�ֵ

	array_5[tmp].cur=add;
	array_5[tmp_for_add].cur=array_5[add].cur;
	array_5[add].cur=0;
	array_5[add].data=a;

	//tmp_cur=array_5[0].cur;//��ȡ��ǰ0������Ӧ�ı������������ֵ
	//tmp_cur2=array_5[tmp_cur].cur;//���֮ǰ��0ָ���
	//printf("%d-%d--%d--%d--%d--%d\n",tmp_for_add,tmp,tmp_cur,add,a,tem_for_0);	
	//array_5[0].cur=tmp_cur;
	////printf("%d=%d\n",array_5[tmp].cur,add);
	////array_5[tmp].cur=add;
	//array_5[tem_for_0].cur=add;
	////printf("%d=%d\n",array_5[tmp].cur,add);
	//array_5[add].data=a;
	//array_5[add].cur=0;
	return;

}
//���ӵ������
void delete_sll(sll* array_6,int b)
{
	int num=0;
	int before_cur=0;
	int after_cur=0;
	int cur_for_0=0;
	num=search_sll(array_6,b);
	if(num>=0)
	{
		before_cur=get_index_sll(array_6,num);
		after_cur=array_6[num].cur;
		array_6[num].data=0;
		array_6[before_cur].cur=after_cur;
		
		//����������ִ�в������
		//͵����ֱ�Ӱ�ɾ��֮��ı�����������ݷŵ���һ��
		cur_for_0=array_6[0].cur;
		array_6[0].cur=num;
		array_6[num].cur=cur_for_0;
		printf("del success\n");
	}
	else
	{
		printf("not find \n");
		return;
	}
}
//���ص�������ֵ,���������ֵ
int search_sll(sll* array_7,int c)
{
	//int i=1;
	int tmp=1;
	//tmp=array_7[1].cur;
	while((array_7[tmp].data)!=c)
	{
		//i++;
		tmp=array_7[tmp].cur;
		if(tmp==0)
		{
			//printf("search failed\n");
			return -1;
		}
	}
	//printf("search:%d\n",tmp);
	return tmp;
}

void update(sll* array_8,int old_c,int new_c)
{
	int num=-1;
	num=search_sll(array_8,old_c);
	if(num>=0)
	{
		array_8[num].data=new_c;
		return ;
	}
	else
	{
		printf("update failed for char is not found\n");
	}
}
static sll sl_list[SIZE];
int main()
{	
	//int i=1;
	//int temp=0;
	//sl_list[0].cur=1;
	////sl_list[1].data=10;
	//for(i=1;i<12;)
	//{
	//	temp=i;
	//	sl_list[i].data=10+i;
	//	sl_list[i].cur=temp+2;
	//	i+=2;
	//}

	init_sll(sl_list);
	dispaly_all(sl_list);
	//
	printf("---\n");
	insert(sl_list,10,333);
	dispaly_all(sl_list);


	printf("--ss-\n");
	insert(sl_list,11,222);
	dispaly_all(sl_list);

	if(search_sll(sl_list,11)>0)
	{
		printf("%d\n",search_sll(sl_list,11));
	}
	else
	{
		printf("search failed\n");
	}

	update(sl_list,11,11111);
	update(sl_list,10,333333);
	//char��int֮��ת��
	//printf("del---");
	//delete_sll(sl_list,11);
	//delete_sll(sl_list,12);
	dispaly_all(sl_list);

	system("pause");
	return 0;
}