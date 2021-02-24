#include "opencv2/opencv.hpp"
#include<iostream>
using namespace std;
using namespace cv;

void main() {
	Mat srcImg = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\23.jpg");
	imshow("src", srcImg);
	Mat dstImg = srcImg.clone();
	GaussianBlur(srcImg, srcImg, Size(3, 3), 0, 0);
	cvtColor(srcImg, srcImg, CV_BGR2GRAY);
	Canny(srcImg, srcImg, 100, 200);
	imshow("Canny", srcImg);

	//查找轮廓
	vector<vector<Point>> contours;
	vector<Vec4i> hierarcy;
	findContours(srcImg, contours, hierarcy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);
	cout << "num=" << contours.size() << endl;

	Point2f center;  //定义圆中心坐标
	float radius;  //定义圆半径
	for (int i = 0; i<contours.size(); i++)  //依次遍历每个轮廓
	{
		minEnclosingCircle(Mat(contours[i]), center, radius);
		drawContours(dstImg, contours, i, Scalar(0, 0, 255), 2, 8);
		circle(dstImg, center, radius, Scalar(0, 255, 0), 2, 8);  //绘制第i个轮廓的最小外接圆
	}
	imshow("dst", dstImg);

	waitKey(0);
}