#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;


Mat dst;
int value = 20;

void onChange(int, void* param) {
	Mat src = *(Mat*)param;
	threshold(src, dst, value, 255, THRESH_BINARY);//二值化
												   //Canny(src,dst,value,255);//canny边缘检测
	imshow("TrackBar", dst);
}

void main() {
	Mat src = imread("1.jpg", 0);//读入灰度图
	namedWindow("TrackBar", CV_WINDOW_AUTOSIZE);
	createTrackbar("Threshold", "TrackBar", &value, 255, onChange, &src);

	threshold(src, dst, value, 255, THRESH_BINARY);
	//Canny(src,dst,value,255);
	imshow("TrackBar", dst);//　　21/22/23这三行代码如果去掉的话，在未调整滑动条的情况下，不会有画面显示

	waitKey(0);
}