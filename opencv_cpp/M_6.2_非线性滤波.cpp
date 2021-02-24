/*
6.2非线性滤波:中值滤波,双边滤波

线性滤波即两个信号之和的响应和他们各自响应之和相等;
每个像素的输出值是一些输入像素的加权和;

邻域像素的非线性滤波会得到更好的效果;比如:
在噪声是散粒噪声而不是高斯噪声，即图像偶尔会出现
很大的值的时候,用高斯滤波器对图像进行模糊的话，
噪声像素不会被去除，只是转换为更柔和但是仍然可见
的散粒,中值滤波效果更好;

中值滤波:
中值滤波(Median filter)是一种典型的非线性滤波技术,用像素邻域灰度值
的中值来代替该像素点的灰度值,该方法在去除脉冲噪声，椒盐噪声的同时
又能保留图像的边缘细节;

中值滤波是基于排序统计理论的一种能有效抑制噪声的非线性信号处理技术,
其基本原理是把数字图像或者数字序列中一点的值用该点的一个邻域中各点值
的中值代替,让周围的像素接近真实值，从而消除孤立的噪声点;
对于斑点噪声(speckle noise)和椒盐噪声(salt-and-pepper noise),
因为它不依赖于邻域那些鱼典型值差别很大的值，中值滤波器在处理连续图像
窗函数事与线性滤波器的工作方式类似,但是中值滤波却不再是加权运算;

中值滤波在一定条件下可以克服线性滤波器,如最小均方滤波，方框滤波，均值滤波
等带来的图像细节模糊，而且对滤除脉冲干扰及图像扫描噪声非常有效,也常用于
保护边缘信息,保存边缘的特性使它在不希望边缘模糊的场合很有用;
是非常经典的平滑噪声处理方法;

中值滤波与均值滤波器比较
优势:在均值滤波器中,由于噪声成分被放入平均计算中,所以输出收到了噪声的影响,
但是在中值滤波中，由于噪声成分很难选上，所以机会不会影响到输出,因此
对同样大小的区域进行处理,中值滤波无论是在消除噪声还是保存边缘方面都是不错的选择;

劣势:中值滤波花费的时间是均值滤波的5倍以上;
中值滤波选择每个像素的邻域像素中的中值作为输出，或者说中值滤波将
每一个像素点的灰度设置为该点某邻域窗口内的所有像素点灰度值的中值;
1.>排序
2.>取中间值
中值滤波在一定条件下,克服了线性滤波器(均值滤波)所带来的图像细节模糊,
对滤波脉冲干扰即图像扫描噪声最为有效,不需要图像的统计特性,对细节多的
图像不太适合;

*/

/*
双边滤波,是一种非线性的滤波方法,是结合图像的空间林进度和像素值相似度的
一种折中处理,同时考虑空域信息和灰度相似性，达到报边去噪的目的,
具有简单，非迭代，局部的特点;

双边滤波的好处是可以做边缘保存(edge preserving );以往常用维纳滤波或高斯滤波去降噪,
但二者都会较明显的忽略模糊边缘,对应高斯细节的保护效果不明显;
双边滤波器顾名思义,比高斯滤波多了一个高斯方差sigma-d,它是基于空间分布的高斯滤波函数，
所以在边缘附近，离得较远的像素不会对边缘上的像素值影响太多,这样就保证了边缘附近像素值的保存;
但是，由于保存了过多高频的信息，对彩色图像里的高频噪声，双边滤波器能够干净的滤掉,
只能对于低频信息进行较好的滤波;
*/
/*
API
中值滤波:medianBlur函数
C++:void medianBlur(InputArray src,OutputArray dst,int ksize)

目标图像和源图像有一样的尺寸和类型,
第三个参数:int类型的ksize,孔径的线性尺寸，这个参数必须是大于1的
奇数,比如3，5，7，9;

双边滤波:bilateralFilter函数

void bilateralFilter(InputArray src,OutputArray dst,int d,double sigmaColor,double sigmaSpace,
int borderType=BORDER_DEAFAULT)

第三个参数:int类型的d,表示在过滤过程中每个像素邻域的直径;如果这个值被设置为非正数,
opencv会从第五个参数sigmaSpace来计算出来
第四个参数:double类型的sigmaColor, 颜色空间滤波器的sigma值,这个参数的值越大,
就表明该像素邻域内有越宽广的颜色会被混合到一起,产生较大的半相等颜色区域;
第五个参数:double类型的sigmaSpace,坐标空间中滤波器的sigma值,坐标空间的标注方差,
它的数值越大，意味着越远的像素会相互影响,从而使更大的区域中足够相似的颜色获取相同的
颜色,当d>0,d指定了邻域大小且与sigmaSpace无关,否则,d正比于sigmaspace

*/
#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat src_img, dst_img, gray_img, edge;
	int g_nBilateralFilter_Value = 80;
	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}

	namedWindow("src");
	namedWindow("dst_img");
	imshow("src",src_img);
	//中值滤波,
	//medianBlur(src_img,dst_img,7);
	//双边滤波操作
	bilateralFilter(src_img,dst_img, g_nBilateralFilter_Value, g_nBilateralFilter_Value *2, g_nBilateralFilter_Value /2);

	imshow("dst_img", dst_img);

	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}