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
图像的深度和通道
图像中像素点占的bit位数，就是图像的深度;
比如:
二值图像：图像的像素点不是0就是1(图像不是黑色就是白色),图像像素点占的位数就是1位，图像的深度就是1，也称作位图;
灰度图像:图像的像素点位于0-255之间，(0:全黑，255代表：全白，在0-255之间插入了256个等级的灰度，),
2^8=256，图像的深度就是8
以此轮推，我们把计算机中存储单个像素点所用的bit位称为图像的深度;
图像的通道
有了图像深度的概念，我们知道如果是24位的图像，则这个像素点的颜色取值范围是:0-2^24,这个范围特别大，
如果我们知道了某点的像素值怎么判断像素点的颜色呢，
BGR是基本的三原色，如果我们用8位代表一种颜色，每种颜色最大是255，这样每个像素点的颜色值的范围就是
(0-255,0-255,0-255)这样图像的通道就是3;
灰度图的图像存储模型
灰度图像像素点的存储就是对应的原图从左到右，从上到下，依次排列,每个点的值就是像素点的值，
每个点的地址就是像素像素点的地址；
RGB图的图像存储模型
RGB彩色图像和灰色图相比，每个像素点都有3个通道，每个通道占的内存空间8位，在内存中RGB图像的存储是以二维数组的形式;

图像中像素点的遍历
注意:我们对图像像素的遍历其实对每个像素点中通道的遍历，以后我们队像素中以及通道相关操作

什么是颜色空间的颜色
对于3通道的深度是8的RGB图像，一共可以有255^3中颜色，如此庞大的颜色对我们的处理很不方便，可以对图像的像素进行量化；
减小图像的颜色种类，同样也可以达到同样的效果，比如我们把图像的像素减少8倍，则每个通道中只能有256/8=32种颜色；
这样的话，圆的图像0-7像素点对应量化后的0，这样就能实现对图像的压缩;
利用C/C++中int变量的"/"运算，这样的话(0-7)/8=0,同理依次可以得到压缩后像素值;

(1)利用基本的行和列概念实现像素遍历;
图像的存储是以二维数组的形式，取二维数组中的元素，先确定行，后确定列，这样就能把元素提取出来，
opencv中Mat类中定义的指针，可以获取某一行的地址，然后确定列数就可以获取所需要的地址;
Mat类中有:Mat.ptr<uchar>(int i=0)获取像素矩阵的指针，i是从第0行开始的，这块有点像二维数据的存储那样，
二维数组可以当做是若干个一维指针，如果知道了每个行的第一个元素就能遍历所有数据


*/
//(1)利用基本的行和列概念实现像素遍历;
//srcImage:输入图像,desImage:输出图像,n减少倍数
void colorReduce(Mat&srcImage, Mat&desImage, int n)
{
	desImage = srcImage.clone();
	int channels = desImage.channels();
	int rows = desImage.rows;
	int cols = desImage.cols;//真正的列数是像素的列数乘以通道数,具体见RGB图像的存储
	//双重循环的外循环，遍历图片的行数
	for (int i = 0; i < rows; i++)
	{
		uchar *pt = desImage.ptr<uchar>(i);//获取第i行的图像矩阵指针;
		for (int j = 0; j < cols; j++)//双重循环的内循环,遍历图像的列数(包括每个通道数)
		{
			pt[j] = (pt[j] / n)*n + n / 2;//通常我们会在后面加上n/2;
			//内层循环可以用指针实现移动到下一列
			//*pt++ = (*pt / n)*n + n / 2;
		}
	}
}
//(2)利用动态地址遍历像素点
/*
Mat类中的成员函数at(int x,int y)可以用来储存图像元素,但是在编译期间，知道图像的数据类型，
我们一定保确保指定的数据类型和矩阵中数据类型符合,因为at方法不会对任何数据类型进行转换;
对于彩色图像，每个像素由三部分组成，通道(RGB),因此，对于每一个包含彩色图像的Mat,会返回一个由
8位数字组成的向量,opencv将此类型向量定义为:Vec3b;存储彩色图像像素代码可以写成:
image.at<Vec3b>(i,j)[channal]=value;
其中,(i,j)代表像素点位置，channel代表通道;

*/
void colorReduce2(Mat&src, Mat&des, int n = 8)
{
	des = src.clone();
	int cols = src.cols;
	int rows = src.rows;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			des.at<Vec3b>(i, j)[0] = (src.at<Vec3b>(i, j)[0] / n)*n + n / 2;
			des.at<Vec3b>(i, j)[1] = (src.at<Vec3b>(i, j)[1] / n)*n + n / 2;
			des.at<Vec3b>(i, j)[2] = (src.at<Vec3b>(i, j)[2] / n)*n + n / 2;
		}
	}
}
//(3)迭代器操作像素
//迭代器是C++中STL的概念
void colorReduce3(Mat&src, Mat&des, int n = 8)
{
	des = src.clone();
	Mat_<Vec3b>::iterator it = des.begin<Vec3b>();//初始位置迭代器
	Mat_<Vec3b>::iterator itend = des.end<Vec3b>();//初始位置迭代器
	for (;it!=itend; it++)
	{
		(*it)[0] = ((*it)[0] / n)*n + n / 2;
		(*it)[1] = ((*it)[1] / n)*n + n / 2;
		(*it)[2] = ((*it)[2] / n)*n + n / 2;
	}
}
//单通道遍历
void fore_each_signal(Mat &src)
{
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			uchar *data = src.ptr<uchar>(i);
			int pixel = data[j];
			printf("gray_pixel=%d\n",pixel);
		}
	}
}
//RGB图像
void fore_each_RGB(Mat&src)
{
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			uchar *data = src.ptr<uchar>(i);
			int b = data[3 * j];
			int g = data[3 * j + 1];
			int r = data[3 * j + 2];
			printf("blue_pixel=%d-green_pixel=%d-red_pixel=%d\n",b,g,r);
		}
	}
}

/*
常用像素存储结构

*/
/*
opencv中有类模板Vec,可以表示一个向量;opencv中使用Vec类预定义了
一些小向量,可以用于矩阵元素的表达;

typedef Vec<uchar, 2> Vec2b;
typedef Vec<uchar, 3> Vec3b;
typedef Vec<uchar, 4> Vec4b;

typedef Vec<short, 2> Vec2s;
typedef Vec<short, 3> Vec3s;
typedef Vec<short, 4> Vec4s;

typedef Vec<int, 2> Vec2i;
typedef Vec<int, 3> Vec3i;
typedef Vec<int, 4> Vec4i;

typedef Vec<float, 2> Vec2f;
typedef Vec<float, 3> Vec3f;
typedef Vec<float, 4> Vec4f;
typedef Vec<float, 6> Vec6f;

typedef Vec<double, 2> Vec2d;
typedef Vec<double, 3> Vec3d;
typedef Vec<double, 4> Vec4d;
typedef Vec<double, 6> Vec6d;

例如8U类型的RGB彩色图像也可以使用Vec3B,
3通道float类型的矩阵可以使用Vec3f,
对于Vec对象可以使用[]符号如数组一样对其元素
进行读写操作
如:
Vec3b color;//用color变量描述一种RGB颜色
color[0]=255;//B分量
color[1]=0;//G分量
color[2]=0;//R分量
*/
/*
3，像素值的读写
在对图像进行处理时，需要读取某个像素值或者设置某个像素值;
在更多的时候需要对图像中所有像素进行遍历

*/

void test_01()
{
	//2D Point
	Point2f p(5, 1);
	cout << endl << "Point(2D)=" << p << endl << endl;
	//3D Point
	Point3f p3f(2, 5, 7);
	cout << endl << "Point(3f)=" << p3f << endl << endl;
	//std::vector via cv::Mat
	vector<float> v;
	v.push_back((float)CV_PI);//将pi的值以float类型存入v,push_back是c++中容器的一种操作
	v.push_back(2);
	v.push_back(3.01f);
	cout << "vector of floats via Mat=" << endl << Mat(v) << endl << endl;

	//std::vector of points 
	vector<Point2f> vPoints(20);
	for (size_t i = 0; i < vPoints.size(); ++i)
	{
		vPoints[i] = Point2f((float)i * 5, (float)(i % 7));
	}
	cout << "vector of 2D points=" << endl << vPoints << endl << endl;
}
//3.1 at()函数
/*
可以用函数at()来实现对矩阵中某个像素值进行读取或进行赋值操作,
但是前提要知道该像素行列位置,
用法如下:
uchar value =img.at<uchar>(i,j);//读取第i行第j列像素值
img.at<uchar>(i,j)=128;//将第i行第j列像素值设置为128
*/
//如果需要对图像像素进行遍历，不推荐使用at()函数，因为使用这个函数其效率不高，但是其可读性较好。
void fore_each_at()
{
	double timeConsume = static_cast<double>(getTickCount());
	Mat grayImage(400,600,CV_8UC1);//创建一个大小为600*800的单通道灰度图
	Mat colorImage(400,600,CV_8UC3);//创建一个大小为400*600的三通道彩色图
	//遍历所有像素并设置像素值
	for (int i = 0; i < grayImage.rows; i++)//遍历行
	{
		for (int j = 0; j < grayImage.cols; j++)//遍历列
		{
			grayImage.at<uchar>(i, j) = (i + j) % 255;
		}
	}
	//遍历所有像素并设置像素值
	for (int i = 0; i < colorImage.rows; i++)//遍历行
	{
		for (int j = 0; j < colorImage.cols; j++)//遍历列
		{
			Vec3b pixel;//定义三通道像素值变量
			pixel[0] = i % 255;//blue
			pixel[1] = j % 255;//green
			pixel[2] = 0;//red
			colorImage.at<Vec3b>(i, j) = pixel;
		}
	}
	//显示遍历图像的结果
	namedWindow("grayimage",WINDOW_AUTOSIZE);
	imshow("grayimage",grayImage);

	namedWindow("colorimage", WINDOW_AUTOSIZE);
	imshow("colorimage", colorImage);

	timeConsume = ((double)getTickCount() - timeConsume) / getTickFrequency();
	cout << "程序耗时:" << timeConsume << endl;


}

/*
使用迭代器iterator
使用迭代器可以很方便的遍历所有元素;Mat类支持迭代器的方式对矩阵元素进行遍历;
由于使用迭代器就不需要再使用行列数进行操作;
*/
/*
使用迭代器进行像素遍历被认为是一种更安全的方式,使用迭代器只需要求出矩阵的开头和矩阵末尾，
接下来使用for循环进行迭代，知道"it==end",
代码中"colorit=colorimage.begin(),colorend=colorimage.end()";
是求出矩阵起始位置和结束位置;
*/
void fore_each_iterator()
{
	double timeConsume = static_cast<double>(getTickCount());
	Mat grayImage(400,600,CV_8UC1);
	Mat colorImage(400, 600, CV_8UC3);
	//遍历所有像素并且设置像素值
	MatIterator_<uchar>grayit, grayend;
	for (grayit = grayImage.begin<uchar>(), grayend = grayImage.end<uchar>(); grayit != grayend; grayit++)
	{
		*grayit = rand() % 255;
	}
	//遍历所有像素并设置像素值
	MatIterator_<Vec3b> colorit, colorend;
	for (colorit = colorImage.begin<Vec3b>(), colorend = colorImage.end<Vec3b>(); colorit != colorend; colorit++)
	{
		(*colorit)[0] = rand() % 255;//blue
		(*colorit)[1] = rand() % 255;//green
		(*colorit)[2] = rand() % 255;//red
	}
	namedWindow("color",WINDOW_AUTOSIZE);
	imshow("color",colorImage);//

	namedWindow("gray",WINDOW_AUTOSIZE);
	imshow("gray",grayImage);
	timeConsume = ((double)getTickCount() - timeConsume) / getTickFrequency();
	cout <<"程序耗时:" <<timeConsume<< endl;
	waitKey(0);
}

/*
3.3使用指针进行访问
在前面已经提到用指针进行访问,虽然使用指针速度最快，但是指针操作不进行类型
以及越界检查，所有在程序写好编译没有问题，但是运行就有可能出错;
虽然速度不如指针，但是相对两者比较容易实现,可读性比较好,

*/
void fore_each_point()
{
	double timeConsume = static_cast<double>(getTickCount());
	Mat grayImage(400,600,CV_8UC1);
	Mat colorImage(400, 600, CV_8UC3);
	//遍历
	for (int i = 0; i < grayImage.rows; i++)
	{
		uchar *p = grayImage.ptr<uchar>(i);//获取第i行第一个像素的指针
		for (int j = 0; j < grayImage.cols; j++)
		{
			p[j] = (i + j) % 255;//对每个i行的所有像素进行赋值操作
		}
	}
	//遍历所有像素并且设置像素值
	for (int i = 0; i < colorImage.rows; i++)
	{
		Vec3b *p = colorImage.ptr<Vec3b>(i);
		for (int j = 0; j < colorImage.cols; j++)
		{
			p[j][0] = i % 255;
			p[j][1] = j % 255;
			p[j][2] = 0;
		}
	}
	namedWindow("grayimage",WINDOW_AUTOSIZE);
	imshow("grayimage",grayImage);
	namedWindow("color",WINDOW_AUTOSIZE);
	imshow("color",colorImage);
	timeConsume=((double)getTickCount() - timeConsume) / getTickFrequency();
	cout <<"程序耗时:"<< timeConsume<< endl;
	waitKey(0);
}

int main()
{
	//test_01();
	//fore_each_at();
	//fore_each_iterator();
	fore_each_point();
	system("pause");
	return 0;
}