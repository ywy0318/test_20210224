/*
设定感兴趣区域ROI和使用addweighted函数进行图像线性混合的基础上,
将二者结合起来,先指定ROI,再使用addWeighted函数对指定的ROI区域的图像
进行混合操作,将其封装在ROI_LiearBlending

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

	//定义一个Mat类型并给其设定ROI区域
	Mat image_ROI;
	//方法一:
	//image_ROI = src_img(Rect(200,250,src_img_1.cols/2,src_img_1.rows/2));

	//方法二:
	image_ROI = src_img(Range(250, 250 + src_img_1.rows/2), Range(200, 200 + src_img_1.cols/2));

	//0.0=gamma
	addWeighted(src_img, alpha_value, src_img_1, beta_value, 0.0, image_ROI);

	namedWindow("src_img", 1);
	imshow("src_img", src_img);

	//namedWindow("des_img--LinearBlending",1);
	imshow("image_ROI", image_ROI);
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
