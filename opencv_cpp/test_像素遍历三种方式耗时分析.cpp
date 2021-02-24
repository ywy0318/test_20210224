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
像素的颜色空间缩减表，查找表，遍历像素的三种方式，程序计时;
利用一个综合程序进行对比，
方式是用三种方式对lena图像(220*220)进行处理,
使其颜色种类从256种变成64中;
在颜色空间缩减中使用过这种方式，
即每个像素值除以4想下取整，然后再乘以4,即可将其颜色种类缩减到64种;

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
//使用at动态地址计算方式
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
从结论耗时分析来看，使用指针方式是最快的处理方式,
而迭代器的方式相对最慢，但是使用迭代器是较为安全的访问方式;
从上面程序中仔细分析指针式访问和at()动态地址访问方式的不同;
可以找到更大的图像对三种像素遍历方式进行分析，耗时会有明显差别;

官方文档提到了使用LUT()函数,在进行图像处理时将所给的所有图像之替换成其他的值,
opencv中提供的LUT()函数可以批量实现这种功能;
用法如下:
Mat lookUpTable(1,2556,CV_8U);
uchar *p=lookUpTable.data;
for(int i=0;i<256;i++)
{
	p[i]=table[i];
}
//然后调用函数,(I是输入图像,J是输出图像)
LUT(I,lookUpTable,J);

官方文档中通过一副(2560*1600)图像进行上百次的处理得出如下结论:
1,如果可能的话尽可能使用opencv中提供的参数
2,最快的方式是LUT()函数,因为opencv库通过Intel Threaded Building Blocks
	实现其多线程;
3,如果写一个简单图像的遍历程序推荐使用指针方式
4,迭代器是相对来讲比较安全的访问方式，但其速度也相对较慢
5,在Debug模式下，动态地址计算方法是最慢的访问方式，但是在release模式下它有可能
	比iterator访问方式快;


*/

int main()
{
	Mat img, des_at_image,des_ptr_image,des_iterator_image;
	string imgpath1 = "E://Visual Studio 2010//Projects//opencv_2018_12_21//lena.jpg";
	img = imread(imgpath1, 1);//读入图片数据
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