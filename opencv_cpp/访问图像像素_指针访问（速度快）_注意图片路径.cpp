#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

void main() {
	Mat img = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.png");
	imshow("src", img);
	Mat dst = img.clone();
	int rowNumber = img.rows;//获取行数
	int colNumber = img.cols*img.channels();//列数×通道数=每一行的元素个数
	for (int i = 0; i<rowNumber; i++) {
		uchar* data = dst.ptr<uchar>(i);//获取每一行首地址，ptr函数可以得到图像任意行的首地址
		for (int j = 0; j <colNumber; j++)
		{
			//data[j]=255;//灰度图
			switch (j % 3)
			{
			case 0://蓝色通道
				data[j] = 255;
				break;
			case 1://绿色通道
				data[j] = 0;
				break;
			case 2://红色通道
				data[j] = 255;
				break;
			}
		}
	}
	imshow("dst", dst);
	waitKey(0);
}