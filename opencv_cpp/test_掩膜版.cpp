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
可以通过掩模矩阵(通常来讲叫核)对图像的每个图像像素值重新计算;
这个掩膜板能够调整临近像素包括当前像素对新像素的影响程度;
从数学角度来讲，我们有特殊的值对当前的值做了一个加权平均的操作,
举个例子,设想一个图像对比度增强的方法，基本上我们要将下面的公式
应用到每个像素上;
第一个公式是用数学公式，第二个是用一个掩膜版;将掩膜版中心放到你想
想计算像素上，将像素值累加并乘以与叠加矩阵值相乘，对于较大的
矩阵来看，后一种表达方式更容易理解;
*/
//有问题
void sharpen(const Mat&myimage, Mat &result)
{
	CV_Assert(myimage.depth()==CV_8U);
	const uchar* precious = NULL;
	const uchar* current = NULL;
	const uchar* next = NULL;
	uchar* output = NULL;
	const int nchannels = myimage.channels();
	for (int i = 0; i < myimage.rows; i++)
	{
		precious = myimage.ptr<uchar>(i - 1);//当前像素上一行指针;
		current = myimage.ptr<uchar>(i);//当前像素行指针
		next = myimage.ptr<uchar>(i + 1);//当前像素下一行指针
		output = result.ptr<uchar>(i);
	}
	//利用公式和上下左右四个像素对当前像素值进行处理
	for (int j = nchannels; j < nchannels*(myimage.cols-1); ++j)
	{
		*output++ = saturate_cast<uchar>(5 * current[j] - current[j - nchannels]
			- current[j + nchannels] - precious[j] - next[j]);
	}
	result.row(0).setTo(Scalar(0));//设置第一行所有元素值为0;
	result.row(result.rows-1).setTo(Scalar(0));//设置最后一行所有元素值为0;
	result.col(0).setTo(Scalar(0));//设置第一列所有元素值为0;
	result.col(result.cols-1).setTo(Scalar(0));//设置第一列一列所有元素值为0;
}
int main()
{
	Mat img,des;
	string imgpath0 = "E:\\Visual Studio 2010\\Projects\\opencv_2018_12_21\\opencv_2018_12_21\\1.jpg";
	img = imread(imgpath0, 1);//读入图片数据
	if (img.empty())
	{
		cout << "can not open or find the img" << endl;
		system("pause");
		return -1;
	}
	cout << "图片读取成功" << endl;

	namedWindow("srcimgae",WINDOW_AUTOSIZE);
	imshow("srcimage",img);

	des.create(img.size(),img.type());
	sharpen(img,des);
	namedWindow("desimage",WINDOW_AUTOSIZE);
	imshow("desimage",des);
	waitKey(0);
	

	system("pause");
	return 0;
}