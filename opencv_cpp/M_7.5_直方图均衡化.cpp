/*
7.5直方图均衡化
扩大图像的动态范围,直方图均衡化;
直方图均衡化是灰度变换的一个应用;
图像的像素灰度变换是随机的,直方图的图形高低不齐,
直方图均衡化就是用一定的算法使直方图大致平和;

直方图均衡化是通过拉伸像素强度分布范围来增强对比度的一种方法;
均衡化处理后的图像只能近似均衡分布;均衡化图像的动态范围扩大了, 
其本质是扩大了量化间隔,而量化级别反而减少了;
原来灰度不同的图像经处理后,可能变得相同;形成了一片相同灰度的区域;
各区域之间有明显的边界,从而出现了伪轮廓;

在原始图像对比度本来就很高的情况下,如果再均衡化则灰度调和,对比度会
降低;在泛白缓和的图像中,均衡化会合并一些像素灰度,从而增加对比度;
均衡化的图片如果再对其均衡化,则图像不会有任何变化;

实现直方图均衡化:equalizeHist()函数
C++:void equalizeHist(InputArray src ,OutputArray dst)
输入图像为8位单通道的图像,输出图像和源图像有一样的尺寸和类型;

进行直方图归一化,直方图的组距的和为255;
计算直方图积分;
以积分作为查询表进行图像变换;
equalizeHist()函数实现的灰度直方图均衡化算法,就是把直方图的
每个灰度级进行归一化处理,求每种灰度的累积分布,得到一个映射的
灰度映射表,然后根据相应的灰度值来修正原图中的每个像素;

*/
#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;
int main()
{

	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	imshow("src_img", src_img);
	//转为灰度图并且显示出来
	cvtColor(src_img,gray_img,COLOR_BGR2GRAY);
	imshow("gray_img",gray_img);
	equalizeHist(gray_img,dst_img);
	imshow("dst_img",dst_img);

	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
