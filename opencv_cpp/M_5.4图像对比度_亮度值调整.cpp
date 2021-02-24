/*
5.4图像对比度,亮度值调整
理论依据
算子的概念:一般的图像处理算子都是一个函数,它接收一个或者多个输入图像，
并伸长输出图像;下面是算子的一般形式;
g(x)=h(f(x))或者g(x)=h(f0(x)-----fn(x))
图像亮度和对比度的调整操作,其实属于图像处理变换中比较
简单的一种---点操作(pointoperators);
点操作有一个特点:仅仅根据输入像素值(有时可加上某些全局信息或者参数),
来计算相应的输出像素值,这类算子包括亮度(brightness)和对比度 (contrast)调整,
颜色校正(colorcorrection)和变换(transformations);
两种最常用的点操作(或者说点算子)是乘上一个常数(对应对比度的调节)
以及加上一个常数(对应亮度值的调节)
g(x)=a*f(x)+b
f(x)表示源图像像素
g(x)表示输出图像像素;
a(需要满足a>0)被称为增益(gain),常常被用来控制图像的对比度;
b通常被称为偏置(bias),常常被用来控制图像的亮度;
g(i,j)=a*f(i,j)+b
i,j表示像素位于第i行和第j列,这个式子是opencv
中控制图像的亮度和对比度的理论公式;


//运算结果可能会超出像素取值范围(溢出),还可能是非整数(如果是浮点数的话),
所以要用 saturate_cast 对结果进行转换,以确保它为有效值;
{
大致原理:
	if(data<0)
        data=0;
else if(data>255)
	data=255;

}
for(int y=0;y<image.rows;y++)
{
	for(int x=0;x<image.cols;x++)
	{
		for(int c=0;c<3;c++)
		{
		new_image.at<Vec3b>(y,x)[c]=saturate_cast<uchar>((g_nConstrastValue*0.01)*(iamge.at<Vec3b>(y,x)+g_nBrightValue)
		}
	}
}

*/

#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
int g_nContrastValue = 80;//对比度值
int g_nBrightValue = 80;//亮度值
Mat src_img, dst_img, gray_img, edge;

void on_ContrastAndBright(int ,void*)
{
	namedWindow("原始图窗口",1);
	for (size_t y = 0; y < src_img.cols; y++)
	{
		for (int x=0;x<src_img.rows;x++)
		{
			for (size_t c = 0; c < 3; c++)
			{
				dst_img.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(
					(g_nContrastValue)*0.01*(src_img.at<Vec3b>(y, x)[c]) + g_nBrightValue);
			}
		}
	}
	imshow("原始图窗口",src_img);
	imshow("效果图窗口",dst_img);
}
int main()
{
	
	
	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	dst_img = Mat::zeros(src_img.size(),src_img.type());


	namedWindow("效果图窗口",1);
	createTrackbar("对比度:","效果图窗口",&g_nContrastValue,300,on_ContrastAndBright);
	createTrackbar("亮 度:", "效果图窗口", &g_nBrightValue, 300,on_ContrastAndBright);

	on_ContrastAndBright(g_nContrastValue,0);
	on_ContrastAndBright(g_nBrightValue, 0);
	waitKey(0);
	while (true)
	{

	}
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
