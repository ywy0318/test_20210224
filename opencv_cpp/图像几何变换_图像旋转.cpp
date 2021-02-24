#include<opencv2/opencv.hpp>
using namespace cv;

void main() {
	Mat src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	Point2f center = Point2f(src.cols / 2, src.rows / 2);//��ת����
	double angle = 15;//��ת�Ƕ�
	double scale = 0.5;//���ų߶�
	Mat rotate = getRotationMatrix2D(center, angle, scale);//��ת����
	Mat dst;
	warpAffine(src, dst, rotate, Size(600, 400));//����任

	imshow("src", src);
	imshow("dst", dst);
	waitKey(0);
}