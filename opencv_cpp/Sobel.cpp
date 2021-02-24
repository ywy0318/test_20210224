#include "opencv2/opencv.hpp"
using namespace cv;

void main()
{
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y, dst;

	Mat src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\7.jpg", 0);
	imshow("src", src);

	Sobel(src, grad_x, CV_16S, 1, 0, 3);//16位有符号（求导时有正负），x方向参数设置为1,0
	convertScaleAbs(grad_x, abs_grad_x);//转为无符号
	imshow("X方向", abs_grad_x);

	Sobel(src, grad_y, CV_16S, 0, 1, 3);//y方向参数设置为0,1
	convertScaleAbs(grad_y, abs_grad_y);
	imshow("Y方向", abs_grad_y);

	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
	imshow("合并效果", dst);

	waitKey(0);
	destroyAllWindows();
}