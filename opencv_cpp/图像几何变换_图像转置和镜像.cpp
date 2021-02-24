#include<opencv2/opencv.hpp>
using namespace cv;

void main() {
	Mat src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	Mat dst;
//	transpose(src,dst);//先左右翻转，然后再逆时针旋转90°
//	flip(src,dst,0);//沿x轴翻转
//	flip(src,dst,1);//大于0，沿y轴翻转
	flip(src, dst, -1);//小于0，沿原点翻转

	imshow("src", src);
	imshow("dst", dst);
	waitKey(0);
}