/*
线性混合操作
线性混合操作时一种典型的二元(两个输入)的像素操作
g(x)=(1-a)*f1(x)+a*f2(x)
通过范围0-1之间改变a值,来对两幅图像(f1(x)和f2(x))或两段视频
同样为(f0(x)和f1(x))产生时间上的画面跌叠加(cross-dissolve)
效果,就像幻灯片放映和电影制作中的那样,也就是在幻灯片翻页时设置的
前后页缓慢过渡叠加效果,以及电影情节过渡时出现的画面叠加的效果
OpenCV中运用addWeighted函数;
计算数组加权和:addWeighted()函数---计算两个数组(图像阵列)的加权和
(InputArray scr_1,double alpha,InputArray src_2,double beta,double gamma,OutputArray dst,int dtype=-1)
第一个参数:InputArray类型的src_1,表示需要加权的第一个数组,常常填一个Mat;
第二个参数:alpha,第一个数组的权重
第三个参数:InputArray--src_2,第二个数组，它需要和第一个数组拥有相同的尺寸和通道数;
第四个参数:beta,表示第一个数组的权重值;
第五个参数:gamma,一个加到权重总和上的标量值,
第六个参数,OutputArray类型的dst,输入的数组，它和输入的两个数组拥有相同的尺寸和通道数
第七个参数:int 类型的dtype,输出阵列的可选深度,有默认值-1,当两个输入数组具有相同的深度,
这个参数设置为-1,等同于src_1.depth();
图像深度是指存储每个像素所用的位数，也用于量度图像的色彩分辨率。
数学表达式:
dst=src_1[I]*alpha+src_2*beta+gamma;
I,是多维数组元素的索引值,在遇到多通道数组的时候,每个通道都需要独立进行处理;
当输出数组的深度为CV_32S的时候,这个函数不适用,
就会内存溢出或者算出来的结果不对;

*/

#include<iostream>
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;
//opencv进行canny边缘检测
//载入图像,转换为灰度图,blur进行图像模糊降噪，然后用canny进行边缘检测

int main(int argc, char* argv[])
{
	
	//--1--双右斜线法
	string imgpath0 = "E:\\Visual Studio 2010\\Projects\\opencv_2018_12_21\\opencv_2018_12_21\\1.jpg";
	//--2--双左斜线法
	string imgpath1 = "E://Visual Studio 2010//Projects//opencv_2018_12_21//opencv_2018_12_21//1.jpg";
	//--3--单左斜线法
	string imgpath2 = "E:/Visual Studio 2010/Projects/opencv_2018_12_21/opencv_2018_12_21/1.jpg";
	//--4--以上三种混合
	string imgpath3 = "E:/Visual Studio 2010//Projects\\opencv_2018_12_21//opencv_2018_12_21//1.jpg";
	//--5--相对路径法
	string imgpath4 = "1.jpg";
	//--6--命令行参数法
	//string imgpath5 = argv[1];
	//mat是opencv基本的数据结构，定义一个图像矩阵类型
	Mat src_img, src_img_1, des_img, gray_img, edge;
	double alpha_value = 0.5;
	double beta_value = (1.0 - alpha_value);
	src_img = imread(imgpath4);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	src_img_1 = imread("1_1.jpg");//读入图片数据
	if (src_img_1.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	//0.0=gamma
	addWeighted(src_img, alpha_value, src_img_1, beta_value,0.0, des_img);

	namedWindow("src_img_1", 1);
	imshow("src_img_1", src_img_1);

	//namedWindow("des_img--LinearBlending",1);
	imshow("LinearBlending", des_img);
	//imshow("srcimg", src_img);
	//创建跟src_img同类型和大小的矩阵
	//des_img.create(src_img.size(), src_img.type());


	//将原始图像转换为灰度图像
	//opencv2版本
	//cvtColor(src_img, gray_img, CV_BGR2GRAY);


	//opencv3版本
	//cvtColor(src_img, gray_img, COLOR_BGR2GRAY);
	//使用3x3内核来降噪
	//blur(gray_img, edge, Size(3, 3));

	//getStructuringElement的返回值是指定形状，指定尺寸的内和矩阵
	//Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//erode(src_img, des_img, element);

	//Canny算子
	//Canny(edge, edge, 3, 9, 3);

	

	waitKey(0);
	system("pause");
	return 0;
}