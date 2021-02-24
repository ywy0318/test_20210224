/*
sobel算子的基本概念
sobel算子是一个主要用于边缘检测的离散微分算子;
它结合了高斯平滑和微分求导,用来计算图像灰度函数的近似梯度;
在图像的任何一点使用此算子,都将产生对应的梯度矢量或其法矢量
1.>分别在x和y两个方向求导;
2.>在图像的每一点,结合以上两个结果求出近似梯度
Sobel函数使用扩展的Sobel,来计算一阶,二阶，三阶或混合图像差分;
C++:void sobel(InputArray src,OutputArray dst,int ddepth,int dx,int dy,
int ksize=3,double scale=1,double delta=0,int borderType=BORDER_DEFAULT);

第三个参数:int 类型的ddepth,输出图像的深度,src.depth()和ddepth的组合;
	若src.depth()=CV_8U,取ddepth=-1/CV_16S/CV_32F/CV_64F
	若src.depth()=CV_16U/CV_16S,取ddepth=-1/CV_32F/CV_64F
	若src.depth()=CV_32U,取ddepth=-1CV_32F/CV_64F
	若src.depth()=CV_64U,取ddepth=-1/CV_64F

第六个参数:ksize,默认值为3,表示Sobel核的大小,必须取1，3，5，7
第七个参数:double类型的scale,计算导数值时可选的缩放因子,默认值是1,
表示默认情况下是没有应用缩放的;
第八个参数:double类型的delta,表示在结果存入目标图(第二个参数dst)
之前可选的delta 值,有默认值0;
第九个参数:int类型的borderType,边界模式,默认值为BORDER_DEFAULT;
一般情况下,都是用ksize*ksize来计算导数的,当ksize=1时,
往往会使用3*1或者1*3,且这种情况下,没有进行高斯平滑操作;

当内核大小为3时,Sobel内核可能产生比较明显的误差,
(毕竟Sobel算子只是求取导数的近似值而已,);
Scharr函数,但该函数仅作用于大小为3的内核,该函数的运算和Sobel函数一样快;
但是结果更加精确;
因为Sobel算子结合了高斯平滑和分化,因此结果会具有更多的抗噪性;
大多数情况下,使用sobel函数时,xorder=1,yorder=0,ksize=3来计算图像X方向的导数;
xorder=0,yorder=1,ksize=3;来计算图像y方向的导数;

*/
#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y, dst;
	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	imshow("src_img",src_img);
	//求x方向梯度
	Sobel(src_img, grad_x,CV_16S,1,0,3,1,1,BORDER_DEFAULT);
	convertScaleAbs(grad_x,abs_grad_x);
	imshow("x_sobel",abs_grad_x);

	//求y方向梯度
	Sobel(src_img, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);
	imshow("y_sobel", abs_grad_y);
	//合并梯度
	addWeighted(abs_grad_x,0.5,abs_grad_y,0.5,0,dst);
	imshow("dst",dst);

	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
