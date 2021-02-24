#include "opencv2/opencv.hpp"
#include<iostream>
using namespace std;
using namespace cv;

void main() {
	Mat srcImg = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\25.jpg");
	imshow("src", srcImg);
	Mat dstImg = srcImg.clone();
	Mat dstImg2(srcImg.size(), CV_8UC3, Scalar::all(0));

	GaussianBlur(srcImg, srcImg, Size(3, 3), 0, 0);
	cvtColor(srcImg, srcImg, CV_BGR2GRAY);
	//Canny(srcImg, srcImg, 100, 200);
	threshold(srcImg, srcImg, 200, 255, CV_THRESH_BINARY);
	imshow("threshold", srcImg);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarcy;
	findContours(srcImg, contours, hierarcy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);
	cout << "num=" << contours.size() << endl;

	for (int i = 0; i<contours.size(); i++)
	{
		double area = contourArea(contours[i]);//计算第i个轮廓的面积
		cout << "area--" << i << "---" << area << endl;

		double length = arcLength(contours[i], true);
		cout << "length--" << i << "---" << length << endl;
		//if(area>10000)  //面积大约1W
		//if(area> 100 && area<300)

		if (length<300 && area>300)
			drawContours(dstImg, contours, i, Scalar(0, 0, 255), 2, 8);
	}
	imshow("dst", dstImg);
	waitKey(0);
}