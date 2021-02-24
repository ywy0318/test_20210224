#include "opencv2/opencv.hpp"
using namespace cv;

void main()
{
	Mat srcImg = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	Mat dstImg;
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));

	morphologyEx(srcImg, dstImg, MORPH_OPEN, element);  //开运算
//	morphologyEx(srcImg, dstImg, MORPH_CLOSE, element);  //闭运算
//	morphologyEx(srcImg, dstImg, MORPH_GRADIENT, element);  //形态学梯度运算
//	morphologyEx(srcImg, dstImg, MORPH_TOPHAT, element);  //顶帽运算
//	morphologyEx(srcImg, dstImg, MORPH_BLACKHAT, element);  //黒帽运算

	imshow("src", srcImg);
	imshow("dst", dstImg);
	waitKey(0);
}