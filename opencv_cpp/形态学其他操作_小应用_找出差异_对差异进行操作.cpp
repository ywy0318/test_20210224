#include "opencv2/opencv.hpp"
using namespace cv;

void main()
{
	Mat img1 = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	Mat img2 = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	Mat diff;
	absdiff(img1, img2, diff);//用这个做减法可以避免出现负值=0的情况
	imshow("img1", img1);
	imshow("img2", img2);
	imshow("diff", diff);

	Mat gray;
	cvtColor(diff, gray, COLOR_BGR2GRAY);//转为灰度图
										 //adaptiveThreshold(gray,gray,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY_INV,15,3);//自适应阈值有点不懂
	threshold(gray, gray, 5, 255, THRESH_BINARY);
	imshow("threshold", gray);

	//进行形态学操作
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));//定义结构元素
	morphologyEx(gray, gray, MORPH_OPEN, element);//开运算
	medianBlur(gray, gray, 9);//中值滤波
	dilate(gray, gray, element);
	imshow("dst", gray);

	waitKey(0);
}