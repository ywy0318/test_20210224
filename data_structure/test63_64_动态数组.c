#define _CRT_SECURE_NO_WARNINGS
#include<dos.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<windows.h>
#include<conio.h>

//������̬����
//��ѭԭ��
//�����ʱ�����������,�������;
//�ͷŵ�ʱ����ڲ������,����ͷ�
//��������ָ��
//����һά��̬����,��Ҫһά����
//������ά������Ҫһά��άָ��
//��ά��Ҫһ����άָ��
//�������躯��
/*
void *malloc(unsigned int size)
�ɹ������������ٵ��׵�ַ,ʧ�ܷ��ؿ�ָ��
���ڴ�����size���ֽڵĶѿռ�

�涨Ϊvoid*���ͣ��Ⲣ����˵�ú������ú��޷���ֵ,
���Ƿ���һ���ڵ�ĵ�ַ���õ�ַ������Ϊvoid(�����ͻ������Ͳ�ȷ��),
��һ�δ洢�����׵�ַ������������޷�ȷ����ֻ��ʹ��ʱ���ݸ�����ֵ��ֵ��ȷ��
������ǿ��ת���ķ�������ת��Ϊ������ͣ�
����:double *pd=NULL;pd=(double *)calloc(10,sizeof(double));
��ʾ����ϵͳ����10��������double���͵Ĵ洢�ռ�,
����ָ��pd,ָ����������Ŀռ��׵�ַ,
������(double)��calloc()�ķ������ͽ���ת��,�Ա��double����
���ݵĵ�ַ��ֵ��ָ��pd

ʹ��sizeof��Ŀ������������һ�����͵�ռ�е��ֽ������Ա��ʺϲ�ͬ�ı�����
���ڶ�̬���䲻һ���ɹ�,Ϊ��Ҫ����һ���쳣�������,���³�������ʧ�ܣ�
ʹ�û���֪����,ͨ�������������쳣��������
if(p==NULL)
//if(!p)
{
	printf("��̬�����ڴ�ʧ��\n");
	exit(1);
}
��4������ͷ�ļ�����������
����Ķѿռ�û�����֣�ֻ��ͨ�����ص�ָ���ҵ���;
�����ܶԵö�̬����洢��ʹ��free,Ҳ���ܶ�
ͬ���ڴ���ͬʱ��free�ͷ�����;����:free(p);free(p)
����free()ʱ,����ָ��ָ����ڴ汻�ͷ�,�����ú�����ָ��ֵ����
���ֲ���,��Ϊp����Ϊ�βζ����ݸ�����,�ϸ�Ľ�,���ͷŵ�ָ��ֵ����Ч��,
��Ϊ���Ѳ���ָ����������ڴ���,��ʱ�������κ�ʹ�ñ���ܻ��������


malloc��calloc������
������malloc������ڴ�����,���ԭ��û�б�ʹ�ù�,�����е�ÿһλ���ܶ���0,
��֮,����ⲿ���ڴ�ռ�����������,�ͷź����·���,�����п����������ָ���������;
Ҳ����˵,ʹ��malloc()�����ĳ���ʼʱ(�ڴ�ռ仹û�б����·���)����������,
���ǹ�һ��ʱ���(�ڴ�ռ��Ѿ������·���)���ܻ��������;�����ʹ��ǰ�����Ƚ��Գ�ʼ��
(memset���������ʼ��Ϊ0),������calloc�������䵽�Ŀռ����ʱ���Ѿ�����ʼ��Ϊ0;
������calloc()����֮����ѡ��ʱ,����Ҫ�����Ƿ�Ҫ��ʼ����������ڴ�ռ�,
�Ӷ�ѡ����Ӧ�ĺ���

void *calloc(unsigned int num,unsigned int size)
�ɹ�:���������ٿռ��׵�ַ,ʧ�ܣ����ؿ�ָ��
������������size���ֽڵĶѿռ�

void free(void *p)
�޷���ֵ���ͷ�pָ��Ķѿռ�

void *realloc(void *p,unsigned int size)
�ɹ�:�����¿��ٿռ��׵�ַ,ʧ��:���ؿ�ָ��;
��pָ��Ķѿռ��Ϊsize


���幹������:
����ά��������array[n1][n2][n3]Ϊ��
����ѭ����㵽���,��������ԭ��
�����ָ����array,���Ǹ���άָ��,��ָ�����array[],
��Ϊ��άָ��,���Ը�array
�����ڴ�Ӧ:
array=(int**)calloc(n1,sizeof(int**))
�β�ָ����array[],���Ǹ���ά����,��ָ�����array[][],��Ϊһά����
���Ը�array[]
�����ڴ�Ӧ:
for(i=0;i<n1;i++)
{
	for(j=0;j<n2;j++)
	{
		array[i][j]=(int*)calloc(n3,sizeof(int));
	}
}

*/

void array_1()
{
	int i=0;
	int n1=10;
	int *array_1=(int *)calloc(n1,sizeof(int));
	printf("before:");
	for(i=0;i<n1;i++)
	{		
		printf("%d\n",array_1[i]);
	}
	printf("after\n");
	for(i=0;i<n1;i++)
	{
		array_1[i]=i+1;
		printf("%d\n",array_1[i]);
	}
	free(array_1);//�ͷ�һά����
	return ;
}


void array_2()
{
	int n2=4;
	int n3=5;
	int i=0,j=0;
	int **array_2;
	//array_2=(int **)calloc();
	array_2=(int **)malloc(n2*sizeof(int*));//��һά

	for(i=0;i<n2;i++)
	{
		array_2[i]=(int *)malloc(n3*sizeof(int));//�ڶ�ά
	}

	for(i=0;i<n2;i++)
	{
		for(j=0;j<n3;j++)
		{
			array_2[i][j]=i*n2+j+1;
			printf("%d\t",array_2[i][j]);
	    }
		printf("\n");
	}
	for(i=0;i<n2;i++)
	{
		free(array_2[i]);//�ͷŵڶ�άָ��
	}
	free(array_2);
	return ;
}

void array_3()
{
	int n1=5,n2=4,n3=3;
	int ***array_3;
	int i=0,j=0,k=0;
	printf("%d\n",sizeof(int**));
	array_3=(int ***)malloc(n1*sizeof(int **));//��һά
	for(i=0;i<n1;i++)
	{
		array_3[i]=(int**)malloc(n2*sizeof(int *));//�ڶ�ά
		for(j=0;j<n2;j++)
		{
			array_3[i][j]=(int *)malloc(n3*sizeof(int));//����ά
		}
	}
	printf("::\n");
	for(i=0;i<n1;i++)
	{
		for(j=0;j<n2;j++)
		{
			for(k=0;k<n3;k++)
			{
				array_3[i][j][k]=i+j+k+1;
				printf("%d\t",array_3[i][j][k]);
			}
			printf("\n");
		}
		printf("\n");
	}
	printf("free\n");
	for(i=0;i<n1;i++)
	{
		for(j=0;j<n2;j++)
		{
			free(array_3[i][j]);//�ͷŵ���άָ��
		}
	}
	for(i=0;i<n1;i++)
	{
		free(array_3[i]);//�ͷŵڶ�ά����
	}
	free(array_3);//�ͷŵ�һά����
	return;

}

int main()
{	
	/*int i,j,k;
	int n1=3;
	int n2=3;
	int n3=3;
	int *array_auto;
	array_auto=(int *)calloc(n1,sizeof(int));*/


	//array_1();
	//array_2();
	array_3();

	system("pause");
	return 0;
}