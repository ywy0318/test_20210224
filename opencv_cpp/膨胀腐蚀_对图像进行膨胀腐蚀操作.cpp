#include<opencv2/opencv.hpp>
using namespace cv;

void main() {
	Mat src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	Mat dst;
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	dilate(src, dst, element, Point(-1, -1), 1);//����һ�Σ���-1��-1����ʾȡ����λ��
	//erode(src,dst,element,Point(-1,-1),2);//��ʴ����

	imshow("src", src);
	imshow("dst", dst);
	waitKey(0);
}