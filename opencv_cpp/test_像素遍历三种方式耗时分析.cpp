#include<iostream>
#include<opencv2\opencv.hpp>
#include "highgui.h"
#include"cvaux.h"
#include"cxcore.h"
#include"opencv2/imgproc.hpp"
#include<string>
using namespace std;
using namespace cv;
/*
���ص���ɫ�ռ����������ұ��������ص����ַ�ʽ�������ʱ;
����һ���ۺϳ�����жԱȣ�
��ʽ�������ַ�ʽ��lenaͼ��(220*220)���д���,
ʹ����ɫ�����256�ֱ��64��;
����ɫ�ռ�������ʹ�ù����ַ�ʽ��
��ÿ������ֵ����4����ȡ����Ȼ���ٳ���4,���ɽ�����ɫ����������64��;

*/
void colorReduceIterator(Mat& src, Mat& des1, int div)
{
	MatIterator_<Vec3b> imageit = des1.begin<Vec3b>();
	MatIterator_<Vec3b> imageend = des1.end<Vec3b>();
	for (; imageit!=imageend;imageit++)
	{
		(*imageit)[0] = (*imageit)[0] / div*div;
		(*imageit)[1] = (*imageit)[1] / div*div;
		(*imageit)[2] = (*imageit)[2] / div*div;
	}
}
void colorReducePtr(Mat& src, Mat& des2, int div)
{
	for (int i = 0; i < des2.rows; i++)
	{
		uchar *p = des2.ptr<uchar>(i);
		for (int j = 0; j < des2.cols; j++)
		{
			p[j] = p[j] / div*div;
		}
	}
}
//ʹ��at��̬��ַ���㷽ʽ
void colorReduceAt(Mat& src, Mat& des ,int div)
{
	for (int  i = 0; i < des.rows; i++)
	{
		for (int j = 0; j < des.cols; j++)
		{
			des.at<Vec3b>(i, j)[0] = des.at<Vec3b>(i, j)[0] / div*div;
			des.at<Vec3b>(i, j)[1] = des.at<Vec3b>(i, j)[1] / div*div;
			des.at<Vec3b>(i, j)[2] = des.at<Vec3b>(i, j)[2] / div*div;
		}
	}
}
/*
�ӽ��ۺ�ʱ����������ʹ��ָ�뷽ʽ�����Ĵ���ʽ,
���������ķ�ʽ�������������ʹ�õ������ǽ�Ϊ��ȫ�ķ��ʷ�ʽ;
�������������ϸ����ָ��ʽ���ʺ�at()��̬��ַ���ʷ�ʽ�Ĳ�ͬ;
�����ҵ������ͼ����������ر�����ʽ���з�������ʱ�������Բ��;

�ٷ��ĵ��ᵽ��ʹ��LUT()����,�ڽ���ͼ����ʱ������������ͼ��֮�滻��������ֵ,
opencv���ṩ��LUT()������������ʵ�����ֹ���;
�÷�����:
Mat lookUpTable(1,2556,CV_8U);
uchar *p=lookUpTable.data;
for(int i=0;i<256;i++)
{
	p[i]=table[i];
}
//Ȼ����ú���,(I������ͼ��,J�����ͼ��)
LUT(I,lookUpTable,J);

�ٷ��ĵ���ͨ��һ��(2560*1600)ͼ������ϰٴεĴ���ó����½���:
1,������ܵĻ�������ʹ��opencv���ṩ�Ĳ���
2,���ķ�ʽ��LUT()����,��Ϊopencv��ͨ��Intel Threaded Building Blocks
	ʵ������߳�;
3,���дһ����ͼ��ı��������Ƽ�ʹ��ָ�뷽ʽ
4,����������������Ƚϰ�ȫ�ķ��ʷ�ʽ�������ٶ�Ҳ��Խ���
5,��Debugģʽ�£���̬��ַ���㷽���������ķ��ʷ�ʽ��������releaseģʽ�����п���
	��iterator���ʷ�ʽ��;


*/

int main()
{
	Mat img, des_at_image,des_ptr_image,des_iterator_image;
	string imgpath1 = "E://Visual Studio 2010//Projects//opencv_2018_12_21//lena.jpg";
	img = imread(imgpath1, 1);//����ͼƬ����
	if (img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	int num = 4;
	double time_at, time_iterator, time_ptr;
	des_at_image = img.clone();
	des_iterator_image = img.clone();
	des_ptr_image = img.clone();
	imshow("img", img);

	time_at = static_cast<double>(getTickCount());
	colorReduceAt(img, des_at_image, num);
	time_at = ((double)getTickCount() - time_at) / getTickFrequency();
	cout <<"time_att::  "<<time_at << endl;
	imshow("colorReduceAt", des_at_image);

	time_ptr = static_cast<double>(getTickCount());
	colorReducePtr(img, des_ptr_image, num);
	time_ptr = ((double)getTickCount() - time_ptr) / getTickFrequency();
	cout << "time_ptr::  " << time_ptr << endl;
	imshow("colorReducePtr", des_ptr_image);

	time_iterator = static_cast<double>(getTickCount());
	colorReduceIterator(img, des_iterator_image, num);
	time_iterator = ((double)getTickCount() - time_iterator) / getTickFrequency();
	cout << "time_ite::  " << time_iterator << endl;
	imshow("colorReduceIterator", des_iterator_image);

	waitKey(0);
	system("pause");
	return 0;
}