#include<opencv2/opencv.hpp>
using namespace cv;

void main() {
	Mat src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	Point2f center = Point2f(src.cols / 2, src.rows / 2);//旋转中心
	double angle = 15;//旋转角度
	double scale = 0.5;//缩放尺度
	Mat rotate = getRotationMatrix2D(center, angle, scale);//旋转矩阵
	Mat dst;
	warpAffine(src, dst, rotate, Size(600, 400));//仿射变换

	imshow("src", src);
	imshow("dst", dst);
	waitKey(0);
}