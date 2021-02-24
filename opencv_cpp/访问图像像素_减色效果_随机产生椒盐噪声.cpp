//Mat img = imread("E://1.jpg");
//imshow("src", img);
//Mat dst = img.clone();
//int rowNumber = img.rows;
//int colNumber = img.cols*img.channels();//获取每一行的元素
//for (int i = 0; i<rowNumber; i++) {
//	uchar* data = dst.ptr<uchar>(i);//获取每一行首地址
//	for (int j = 0; j <colNumber; j++)
//	{
//		switch (j % 3)
//		{
//		case 0://蓝色通道
//			data[j] = data[j] / 64 * 64 + 64 / 2;
//			break;
//		case 1://绿色通道
//			data[j] = data[j] / 64 * 64 + 64 / 2;
//			break;
//		case 2://红色通道
//			data[j] = data[j] / 64 * 64 + 64 / 2;
//			break;
//		}
//	}
//}
//imshow("dst", dst);
//waitKey(0);


#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

void main() {
	Mat img = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\cat2.jpg");
	imshow("src", img);
	Mat dst = img.clone();
	int rowNumber = img.rows;
	int colNumber = img.cols;
	int i, j;
	for (int k = 0; k < 400; k++)//产生噪声的个数（此时为400）
	{
		i = rand() % rowNumber;//任意数对行数取余
		j = rand() % colNumber;//任意数对列数取余
		dst.at<Vec3b>(i, j)[0] = 255;
		dst.at<Vec3b>(i, j)[1] = 255;
		dst.at<Vec3b>(i, j)[2] = 255;//将这三行的“255”设置为“0”即产生椒噪声
	}
	imshow("dst", dst);
	waitKey(0);
}







