#include<opencv2/opencv.hpp>
using namespace cv;

void main() {
	Mat src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	Mat dst;
	resize(src, dst, Size(300, 300));
	imshow("src", src);
	imshow("dst", dst);
	waitKey(0);
}