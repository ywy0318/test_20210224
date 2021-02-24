#include "opencv2/opencv.hpp"
using namespace cv;

void main()
{
	//Canny边缘检测
	Mat srcImg = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\7.jpg", 0); //0表示以灰度图读入,彩色图和灰度图进行边缘检测时略有不同,建议使用灰度图
	medianBlur(srcImg, srcImg,5);//中值滤波
	imshow("src", srcImg);

	Mat dstImg;
	Canny(srcImg, dstImg, 30, 80);
	imshow("Canny", dstImg);
	waitKey(0);
}