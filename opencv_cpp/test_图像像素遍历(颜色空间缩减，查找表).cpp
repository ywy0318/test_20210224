#include<iostream>
#include<opencv2\opencv.hpp>
#include "highgui.h"
#include"cvaux.h"
#include"cxcore.h"
#include"opencv2/imgproc.hpp"
#include<string>
#include<cstring>
using namespace std;
using namespace cv;
/*
��ͨ��ͼ:�׳ƻҶ�ͼ��ÿ�����ص�ֻ����һ��ֵ��ʾ��ɫ����������ֵ��0-255֮�䣬0�Ǻ�ɫ��255�ǰ�ɫ,
�м�ֵ��һЩ��ͬ�ȼ��Ļ�ɫ;
(Ҳ��3ͨ���ĻҶ�ͼ��3ͨ���Ҷ�ͼֻ��һ��ͨ����ֵ����������ͨ����ֵ����0)
��ͨ��ͼ:ÿ�����ص㶼��3��ֵ��ʾ�����Ծ�����ͨ����Ҳ��4ͨ����ͼ;����BGRͼƬ��Ϊ��ͨ��ͼƬ��BGRɫ��ģʽ��
��ҵ���һ����ɫ��׼����ͨ����BGR(���̺�)������ɫͨ���ı任�Լ������໥֮��ĵ������õ���ʽ��������ɫ�ģ�
BGR�Ǵ������̺�����ͨ������ɫ�������׼���������������������ܸ�֪��������ɫ����Ŀǰ����������ɫϵͳ֮һ;
ÿһ������������ɫ��ʾ

*/
/*
1.��ɫ�ռ����������ұ�
����һ�ּ򵥵�C\C++���͵��޷����ַ��;���Ĵ洢�ṹ��
���ڵ�ͨ��ͼ����ԣ�ͼ��������������256������ֵ��
���ͼ������ͨ��ͼ����ôͼ�����ش洢����ɫ���Դﵽ���˵�1600w
������˶����ɫ���Ͷ����㷨��������һ�ֳ��صĸ�����
��ʱ�����ǿ����ҵ�һЩ���ܹ�������ɫ�������ǲ�����Ӱ���䴦�����ķ�����
ͨ������������ɫ�ռ䡣�����ζ�����������������ֵ�͸��ٵ���ɫ�����ֵ�ǰ����ɫ�ռ䡣
*/
/*
�������ǿ��Խ�ֵ��0-9��Χ�ڵ�����ֵ����0����ֵλ��10-19��Χ�ڵ�����ֵ����10�ȵ�;
��������int���͵���ֵ����uchar(unsigned char ��ֵλ��0-255֮��)���͵õ��Ľ����Ϊ
char����,��Щ��ֵֻ��char���͵�ֵ�������������С������ȡ��;
��ʽ�����ܽ�Ϊ:I(new)=(I(old)/10)*10
��������ͼ�����ز�Ӧ��������ʽ����һ���򵥵���ɫ�ռ������㷨;
���ڽϴ��ͼ����Ҫ��ִ�в���������ǰ�����������ֵ�洢�����ұ�
���ұ���һ�ּ򵥵�����(������һά���߶�ά),���ڸ�������������������յ����ֵ;
�ڽ���ͼ����ʱ������ȡֵ��Χ��0-255֮����ʵ����һ����256�����,���Խ���Щ��������ǰ
�洢�ڲ��ұ��У�����ͼ����ʱ������Ҫ���¼�������ֵ,����ֱ�ӴӲ��ұ���ã�
����������ֻ���ж�ȡ�������������м���;
*/

//�����������Ͳ��ұ�����:
//<sstream> �ⶨ���������ࣺistringstream��ostringstream��stringstream
void search_table()
{
	int dividewith = 0;
	stringstream s;
	//s << argv[2];
	s >> dividewith;
	if (!s || !dividewith)
	{
		printf("����Ļ��ּ����Ч\n");
		return ;
	}
	uchar table[256];
	for (int i = 0; i < 256; i++)
	{
		table[i] = (uchar)(dividewith*(i*dividewith));
	}
	//������table[i]��ŵ���ֵΪi�����������Ľ��;
	//����i=25.��table[i]=20,����������ɫ�ռ������㷨��Ϊ������:
/*
(1),����ͼ���������
(2),��������ʽӦ����ÿ������
ֵ��ע�����,�˹�ʽ�õ��˳˷��ͳ������������ּ��㷽ʽ��������ȽϷѾ���
������������������㷨ʱ,Ӧ����ʹ�üӼ��͸�ֵ����������;
	
*/
/*
2.opencv��ʱ����
������������ᵽ�ó˳�����Ӵ����ĺ�ʱ,��ô��ô������������еĺ�ʱ,
opencv���ṩ���������ļ�ʱ����,
getTickCount()��getTickFrequency();
getTickCount()������ȡcpuʱ������,
getTickFrequency()������ȡcpuʱ��Ƶ�ʡ�
������������Ϊ��λ�Գ�����к�ʱ����;
double t=(double)getTickCount();
//
//program
//
t=((double)getTickCount()-t)/getTickFrequency();
*/
}
Mat &ScanImageAndReduce(Mat &I, const uchar*const table)
{
	int channels = 0;
	int nrows = 0;
	int ncols = 0;
	int i, j;
	uchar *p;
	//CV_Assert(I.depth == CV_8U);
	//���������ԭͼ�񱣳�һ��
	channels = I.channels();
	nrows = I.rows;
	ncols = I.cols*channels;
	//�жϾ����Ƿ�����������
	if (I.isContinuous())
	{
		ncols *= nrows;
		nrows = 1;
	}
	for ( i = 0; i < nrows; i++)
	{
		p = I.ptr<uchar>(i);//��ȡ����ĵ�i�е��׵�ַ
		for (j = 0; j < ncols; j++)//��ѭ�����д���
		{
			p[j] = table[p[j]];//����---
		}
	}
	imshow("reduce-100", I);
	return I;

}
int main()
{
	int dividewith = 1000;
	int i = 0;
	uchar table[256];
	Mat img, resimg;//mat��opencv���������ݽṹ������һ��ͼ���������
	string imgpath0 = "E:\\Visual Studio 2010\\Projects\\opencv_2018_12_21\\opencv_2018_12_21\\1.jpg";
	img = imread(imgpath0, 1);//����ͼƬ����
	if (img.empty())
	{
		cout << "can not open or find the img" << endl;
		system("pause");
		return -1;
	}
	cout << " open or find the img" << endl;
	namedWindow("IMG", WINDOW_AUTOSIZE);//����һ������
	imshow("IMG", img);
	if (!dividewith)
	{
		printf("%d\n", dividewith);
		system("pause");
		exit(-1);
	}
	for ( i = 0; i < 256; i++)
	{
		table[i] = (uchar)(dividewith*(i*dividewith));
	}
	ScanImageAndReduce(img,table);
	waitKey(0);

	system("pause");
	return 0;
}