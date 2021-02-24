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
单通道图:俗称灰度图，每个像素点只能有一个值表示颜色，它的像素值在0-255之间，0是黑色，255是白色,
中间值是一些不同等级的灰色;
(也有3通道的灰度图，3通道灰度图只有一个通道有值，其他两个通道的值都是0)
三通道图:每个像素点都是3个值表示，所以就是三通道，也有4通道的图;例如BGR图片即为三通道图片，BGR色彩模式是
工业界的一种颜色标准，是通过对BGR(蓝绿红)三个颜色通道的变换以及他们相互之间的叠加来得到各式各样的颜色的，
BGR是代表蓝绿红三个通道的颜色，这个标准几乎包括了人类视力所能感知的所有颜色，是目前运用最广的颜色系统之一;
每一个点由三个颜色表示

*/
/*
1.颜色空间缩减及查找表
设想一种简单的C\C++类型的无符号字符型矩阵的存储结构，
对于单通道图像而言，图像像素最多可以由256个像素值。
如果图像是三通道图像，那么图像像素存储的颜色可以达到惊人的1600w
处理如此多的颜色类型对于算法的运算是一种沉重的负担。
有时候我们可以找到一些既能够降低颜色数量但是并不会影响其处理结果的方法。
通常我们缩减颜色空间。这就意味着我们用新输入的数值和更少的颜色来划分当前的颜色空间。
*/
/*
例如我们可以将值在0-9范围内的像素值看做0，将值位于10-19范围内的像素值看做10等等;
当我们用int类型的数值代替uchar(unsigned char 的值位于0-255之间)类型得到的结果扔为
char类型,这些数值只是char类型的值，所以求出来的小数向下取整;
公式可以总结为:I(new)=(I(old)/10)*10
遍历整幅图像像素并应用上述公式就是一个简单的颜色空间缩减算法;
对于较大的图像需要在执行操作可以以前计算好其像素值存储到查找表；
查找表是一种简单的数组(可能是一维或者多维),对于给定的输入变量给出最终的输出值;
在进行图像处理时，像素取值范围在0-255之间其实就是一共有256中情况,所以讲这些计算结果提前
存储于查找表中，进行图像处理时，不需要重新计算像素值,可以直接从查找表调用，
其优势在于只进行读取操作，而不进行计算;
*/

//综上所述公和查找表如下:
//<sstream> 库定义了三种类：istringstream、ostringstream和stringstream
void search_table()
{
	int dividewith = 0;
	stringstream s;
	//s << argv[2];
	s >> dividewith;
	if (!s || !dividewith)
	{
		printf("输入的划分间隔无效\n");
		return ;
	}
	uchar table[256];
	for (int i = 0; i < 256; i++)
	{
		table[i] = (uchar)(dividewith*(i*dividewith));
	}
	//程序中table[i]存放的是值为i的像素缩减的结果;
	//例如i=25.则table[i]=20,这样看来颜色空间缩减算法分为两部分:
/*
(1),遍历图像矩阵像素
(2),将上述公式应用于每个像素
值得注意的是,此公式用到了乘法和除法，而这两种计算方式相对来将比较费劲，
所以在设计像素缩减算法时,应尽量使用加减和赋值运算来代替;
	
*/
/*
2.opencv计时函数
在上面分析中提到用乘除法会加大程序的耗时,那么怎么计算程序运行中的耗时,
opencv中提供了两个简便的计时函数,
getTickCount()和getTickFrequency();
getTickCount()用来获取cpu时钟周期,
getTickFrequency()用来获取cpu时钟频率。
这样就能以秒为单位对程序进行耗时分析;
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
	//定义变量与原图像保持一致
	channels = I.channels();
	nrows = I.rows;
	ncols = I.cols*channels;
	//判断矩阵是否是连续矩阵
	if (I.isContinuous())
	{
		ncols *= nrows;
		nrows = 1;
	}
	for ( i = 0; i < nrows; i++)
	{
		p = I.ptr<uchar>(i);//获取矩阵的第i行的首地址
		for (j = 0; j < ncols; j++)//列循环进行处理
		{
			p[j] = table[p[j]];//待续---
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
	Mat img, resimg;//mat是opencv基本的数据结构，定义一个图像矩阵类型
	string imgpath0 = "E:\\Visual Studio 2010\\Projects\\opencv_2018_12_21\\opencv_2018_12_21\\1.jpg";
	img = imread(imgpath0, 1);//读入图片数据
	if (img.empty())
	{
		cout << "can not open or find the img" << endl;
		system("pause");
		return -1;
	}
	cout << " open or find the img" << endl;
	namedWindow("IMG", WINDOW_AUTOSIZE);//创建一个窗口
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