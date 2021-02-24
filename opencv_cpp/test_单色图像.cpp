#include<iostream>
#include<opencv2\opencv.hpp>
#include "highgui.h"
#include"cvaux.h"
#include"cxcore.h"
#include"opencv2/imgproc.hpp"
#include<string>
using namespace std;
using namespace cv;
//学习Mat的用法，和对Mat图像赋初始值的方法，学习Mat构造函数的用法。
int main()
{
	//初始化图像矩阵
	Mat red_img(Size(240,240),CV_8UC3,Scalar(0,0,255));
	Mat white_img(Size(240, 240), CV_8UC3, Scalar::all(255));
	Mat black_img=Mat::zeros(Size(240, 240), CV_8UC3);

	//重新对图像的通道赋值
	Mat green_img = red_img.clone();
	green_img = Scalar(255,255,255);//blue--green--red全部都是255的话就是白色的，全部都是0的话就是黑色的
	/*
	创建窗口的函数改为
	cv::namedWindow(const string & windowName, int flag)
	CV_WINDOW_NORMAL or CV_WINDOW_AUTOSIZE:  normal 模式下可以手动调整窗口大小， 而 auto 模式（默认）下窗口将自动适应图像大小，无法手动调整。(gtk3, qt 下可用)
	CV_WINDOW_FREERATIO or CV_WINDOW_KEEPRATIO:  free_ratio 模式下调整图像时不考虑其比率， 而 keep_ratio 模式将保持图像的缩放比率 （qt下可用）
	CV_GUI_NORMAL or CV_GUI_EXPANDED: expanded 模式下将显示额外的工具栏和按钮（NOTE：仅qt下可用）	
	*/
	namedWindow("red_img", CV_WINDOW_AUTOSIZE| CV_WINDOW_FREERATIO);
	namedWindow("white_img", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
	namedWindow("black_img", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
	namedWindow("green_img", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);

	imshow("red_img",red_img);
	imshow("white_img", white_img);
	imshow("black_img", black_img);
	imshow("green_img", green_img);
	waitKey(0);
	system("pause");
	return 0;
}