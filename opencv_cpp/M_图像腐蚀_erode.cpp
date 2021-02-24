#include<iostream>
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;
int main(int argc, char* argv[])
{
	Mat src_img, des_img;//mat是opencv基本的数据结构，定义一个图像矩阵类型
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

	src_img = imread(imgpath4, 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	imshow("srcimg",src_img);
	//getStructuringElement的返回值是指定形状，指定尺寸的内和矩阵
	Mat element = getStructuringElement(MORPH_RECT,Size(15,15));
	erode(src_img, des_img,element);

	imshow("after erode", des_img);

	waitKey(0);
	system("pause");
	return 0;
}