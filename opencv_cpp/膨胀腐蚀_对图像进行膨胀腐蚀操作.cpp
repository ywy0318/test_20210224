#include<opencv2/opencv.hpp>
using namespace cv;

void main() {
	Mat src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	Mat dst;
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	dilate(src, dst, element, Point(-1, -1), 1);//膨胀一次，（-1，-1）表示取中心位置
	//erode(src,dst,element,Point(-1,-1),2);//腐蚀两次

	imshow("src", src);
	imshow("dst", dst);
	waitKey(0);
}