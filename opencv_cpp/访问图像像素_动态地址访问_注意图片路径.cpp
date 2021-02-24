#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

//访问内存异常 注意图片路径
void main() {
	//动态地址访问
	Mat img = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.png");
	imshow("src", img);
	Mat dst = img.clone();
	int rowNumber = img.rows;//获取行数
	int colNumber = img.cols;//获取列数
	for (int i = 0; i<rowNumber; i++) {
		for (int j = 0; j <colNumber; j++)
		{
			dst.at<Vec3b>(i, j)[0] = 255;//蓝色通道
			dst.at<Vec3b>(i, j)[1] = 0;//绿色通道
			dst.at<Vec3b>(i, j)[2] = 0;//红色通道
									   //dst.at<uchar>(i,j)=255;//灰度图像
		}
	}
	imshow("dst", dst);
	waitKey(0);
}