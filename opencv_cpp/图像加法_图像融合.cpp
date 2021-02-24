#include<opencv2/opencv.hpp>
using namespace cv;

void main() {
	Mat img1 = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\2.jpg");
	Mat img2 = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\2.jpg");
	Mat mask = Mat::zeros(img1.size(), CV_8SC1);//´¿ºÚ
	circle(mask, Point(mask.cols / 2, mask.rows / 2), 100, Scalar(100), -1, 8);
	Mat dst;
	add(img1, img2, dst, mask);
	imshow("result", dst);
	waitKey(0);
}