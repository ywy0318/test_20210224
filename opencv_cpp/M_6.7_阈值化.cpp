/*
在对各种图像进行处理操作的过程中,需要对图像中的像素做出取舍与决策,
直接剔除一些低于或者高于一定值的像素;
阈值可以被视作最简单的图像分割的方法;
这种分割方法基于图像中物体与背景之间的灰度差异,此分割属于像素级的分割;

一幅图像中提取出我们需要的部分,用图像中的每一个像素点的灰度值与选取的阈值
进行比较，做出相应的判断;
阈值:的选取依赖于具体的问题;即物体在不同的图像中可能会有不能同的灰度值;
一旦找到了需要分割的物体的像素点,可以对这些像素点设定一些特定的值来表示;
比如:可以将该物体的像素点的灰度值设置为"0"(黑色);
其他的像素点设置为灰度值"255"(白色);
固定阈值操作:
Threshold()函数
Threshold()函数对单通道数组应用固定阈值操作;该函数的典型应用是
对灰色图像进行阈值操作得到二值图像;(compare()函数可以达到此目的),
或者去掉噪声,例如过滤很小或很大的像素值的图像点;
C++:double threshold(InputArray src,OutputArray dst,double thresh,
double maxval,int type)
第三个参数:double thresh,阈值的具体值;
第四个参数:double 类型的maxval,第五个参数阈值类型type取
CV_THRESH_BINARY或CV_THRESH_INV时阈值类型时的最大值;

第五个参数:int 类型的type，阈值类型,threshold()支持对图像取阈值
的方法由其确定;


adaptiveThreshold()函数的作用是对矩阵采用自适应阈值操作,支持就地操作;
C++:void adaptiveThreshold(InputArray src,OutputArray dst,double maxValue,
int adaptiveMethod,int thresholdType,int blockSize,double C)

第三个参数:double类型的maxValue,给像素赋的满足条件的非零值;
第四个参数,int类型的adaptiveMethod,用于指定要使用的自适应阈值算法,
可取值为ADAPTIVE_THRESH_MEAN_C或者ADAPTIVE_THRESH_GAUSSIAN_C;
第五个参数:int类型的thresholdType,阈值类型,取值必须为
THRESH_BINARY,THRESH_BINARY_INV;

第六个参数:int类型的blockSize,用于计算阈值大小的一个像素的邻域尺寸;
通常取值3,5,7;
第七个参数:double类型的C,减去平均或者加权平均值后的常数值,通常
为整数,但是少数情况下可以为0或者负数;

*/
#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img;
int g_nThresholdValue = 100;
int g_nThresholdType = 3;

void on_Threshold(int, void*);//回调函数
int main()
{

	

	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	imshow("src_img", src_img);
	cvtColor(src_img,gray_img,COLOR_RGB2GRAY);
	namedWindow("dst_img",WINDOW_AUTOSIZE);

	createTrackbar("模式","dst_img",&g_nThresholdType,4,on_Threshold);
	createTrackbar("参数值", "dst_img",&g_nThresholdValue,255,on_Threshold);

	on_Threshold(0,0);

	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
void on_Threshold(int, void*)
{
	threshold(gray_img,dst_img,g_nThresholdValue,255,g_nThresholdType);
	imshow("dst_img",dst_img);
}
