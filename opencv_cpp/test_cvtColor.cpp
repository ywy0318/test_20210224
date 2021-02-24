#include<iostream>
#include<opencv2\opencv.hpp>
#include "highgui.h"
#include"cvaux.h"
#include"cxcore.h"
#include"opencv2/imgproc.hpp"
#include<string>
using namespace std;
using namespace cv;
int main()
{
	//--1--双右斜线法
	string imgpath0 = "E:\\Visual Studio 2010\\Projects\\opencv_2018_12_21\\opencv_2018_12_21\\1.jpg";
	Mat img1, img2;//
	img1 = imread(imgpath0,IMREAD_COLOR);
	if (img1.empty())//读取图片失败
	{
		cout << "open filed" << endl;
		return -1;
	}
	namedWindow("原图",WINDOW_AUTOSIZE);//创建一个窗口
	imshow("原图",img1);
	cvtColor(img1,img2,CV_RGB2GRAY);//把图片转化为灰度图
	//把图片写入到图片中
	imwrite("E:\\Visual Studio 2010\\Projects\\opencv_2018_12_21\\opencv_2018_12_21\\1.bmp",img2);
	namedWindow("灰度图",WINDOW_AUTOSIZE);
	imshow("灰度图",img2);
	waitKey(0);//等待一次按键，程序结束
	
	system("pause");
	return 0;
}