/*
图像变换
将一副图像转变为图像数据的另一种表现形式;
最常见的例子就是傅里叶变换,将图像转换为源图像数据的另一种
表现形式;这类操作的结果仍然保存在Opencv图像结构的形式,
新图像的每个单独像素表示原始输出图像的频谱分量,而不是通常所考虑的空间分量;

边缘检测的一般步骤:
第一步:滤波
边缘检测的算法主要是基于图像增强的一阶及二阶倒数,但是倒数通常对
噪声很敏感,因此必须采用滤波器来改善与噪声有关的边缘检测器的性能;
常见的滤波方法主要有高斯滤波,即采用离散化的高斯函数产生一组归一化的
高斯核,然后基于高斯核函数对图像灰度矩阵的每一点进行加权求和;

第二步:增强
增强边缘的基础是确定图像各点邻域强度的变化值;增强算法可以将
回读图像点邻域强度值有显著变换的点凸显出来,在具体
编程实现时,可通过计算梯度赋值来确定;

第三部:增强
经过增强的图像,往往邻域中有很多点的梯度值比较大,而在特定的应用中,
这些点并不是要找的边缘点,所以应该采用某种方法对这些点进行取舍,
实际工程中,常用的方法是通过阈值化的方法来检测;

canny算子:
canny的目标是找到一个最优的边缘检测算法;
最优边缘检测的三个主要评价目标:
低错误率:表示出尽可能多的实际边缘,同时尽可能的减少噪声产生
的误报;
高定位性:标识出的边缘要与图像中的实际边缘尽可能接近;
最小响应:图像中的边缘只能标识一次,并且可能存在的图像噪声不应标识为
边缘;
为了满足这些要求,Canny使用了变分法,这是一种寻找满足特定功能的函数的方法;
最优检测用4个指数函数项的和表示,但是它非常接近高斯函数的一阶导数;

Canny边缘检测的步骤:
第一步:消除噪声;
一般情况下，使用高斯平滑滤波器卷积降噪;
第二步:计算梯度幅值和方向
梯度方向一般取4个可能的角度之一:0度,45度,90度,135度;
第三步:非极大值抑制
这一步排除非边缘像素,仅仅保留一些细线条(候选边缘);
第四步:
Canny使用了滞后阈值,滞后阈值需要两个阈值(高阈值与低阈值):
1.>若某一像素位置的幅值超过高阈值,该像素被保留为边缘像素,
2.>若某一像素位置的幅值小于低阈值,该像素被排除;
3.>若某一像素位置的幅值在两个阈值之间,该像素仅仅在连接到
一个高于高阈值的像素时被保留;

Canny边缘检测:Canny()函数
c++:void Canny(InputArray src,OutputArray edges,double threshold1,
double threshold2,int apertureSize=3,bool L2gradient=false)
第二个参数:输出的边缘图,和源图片有一样的尺寸和类型;
第三个参数:double类型的threshold1,第一个滞后性阈值;
第四个参数:double类型的threshold2,第二个滞后性阈值;
第五个参数:int类型的apertureSize,表示应用Sobel算子的
孔径大小,默认值为3;
第六个参数,bool类型的L2gradient,一个计算图像梯度幅值的标识,
默认值为false;
需要注意的是,这个函数阈值1和阈值2两者中较小的值用于边缘连接,
而较大的值用来控制强边缘的初始段,推荐的高低阈值的比在2:1到3:1之间;


*/
#include<iostream>
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;
//opencv进行canny边缘检测
//载入图像,转换为灰度图,blur进行图像模糊降噪，然后用canny进行边缘检测 

//高阶的canny用法,转成灰度图,降噪,用canny,最后将得到的边缘作为掩码,
//拷贝原图得到效果图上,得到彩色的边缘图;

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
	Mat src_img, dst_img, gray_img, edge_img,temp_img;

	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	temp_img = src_img.clone();
	imshow("srcimg", temp_img);
	//创建跟src_img同类型和大小的矩阵
	dst_img.create(src_img.size(), src_img.type());


	//将原始图像转换为灰度图像
	//opencv2版本
	//cvtColor(src_img, gray_img, CV_BGR2GRAY);


	//opencv3版本
	cvtColor(src_img, gray_img, COLOR_BGR2GRAY);
	//使用3x3内核来降噪
	blur(gray_img, edge_img, Size(3, 3));

	//getStructuringElement的返回值是指定形状，指定尺寸的内和矩阵
	//Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//erode(src_img, dst_img, element);

	//Canny算子
	Canny(edge_img, edge_img, 3, 9, 3);

	dst_img = Scalar::all(0);
	//使用Canny算子输出的边缘图g_cannyDetectedEdges作为掩码,
	//将原图g_srcimage拷贝到目标图dst_img
	temp_img.copyTo(dst_img,edge_img);
	imshow("edge_img",edge_img);
	imshow("dst_img", dst_img);

	waitKey(0);
	system("pause");
	return 0;
}