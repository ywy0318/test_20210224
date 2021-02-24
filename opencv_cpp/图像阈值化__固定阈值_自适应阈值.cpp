#include<opencv2/opencv.hpp>
using namespace cv;

void main() {
	Mat src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg", 0);//以灰度模式读入    
	Mat dst;
	threshold(src,dst,100,255,CV_THRESH_BINARY);
	//adaptiveThreshold(src,dst,255,CV_ADAPTIVE_THRESH_MEAN_C,CV_THRESH_BINARY,11,5);
	//adaptiveThreshold(src, dst, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 11, 5);
	imshow("src", src);
	imshow("dst", dst);
	waitKey(0);
}