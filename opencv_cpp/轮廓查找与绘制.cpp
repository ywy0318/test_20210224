#include"opencv2/opencv.hpp"
#include<iostream>
using namespace std;
using namespace cv;

void main()
{
	Mat srcImg = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\7.jpg");
	Mat tempImg = srcImg.clone();
	//Mat draw(srcImg.rows, srcImg.cols, CV_8UC3);
	cvtColor(srcImg, srcImg, CV_BGR2GRAY); //转为灰度图
	threshold(srcImg, srcImg, 100, 255, CV_THRESH_BINARY);//图像二值化，value>threshold（即100）?255:0
	imshow("srcImg", srcImg);  //轮廓查找前

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	//findContours(srcImg, contours, hierarchy,RETR_EXTERNAL, CHAIN_APPROX_SIMPLE ); //查找外轮廓，压缩存储轮廓点
	findContours(srcImg, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE); //查找所有轮廓
																			   //findContours(srcImg, contours, hierarchy,CV_RETR_CCOMP, CHAIN_APPROX_SIMPLE ); //查找所有轮廓
																			   //findContours(srcImg, contours, hierarchy,RETR_TREE, CHAIN_APPROX_NONE ); //查找所有轮廓，存储所有轮廓点
	imshow("cont", srcImg);  //轮廓查找后 
	drawContours(tempImg, contours, -1, Scalar(0, 255, 0), 2);  //绘制轮廓：-1代表绘制所有轮廓
	cout << "num=" << contours.size() << endl; //输出轮廓个数
	imshow("contours", tempImg);

	waitKey(0);
}