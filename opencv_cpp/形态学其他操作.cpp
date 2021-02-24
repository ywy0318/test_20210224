#include "opencv2/opencv.hpp"
using namespace cv;

void main()
{
	Mat srcImg = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	Mat dstImg;
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));

	morphologyEx(srcImg, dstImg, MORPH_OPEN, element);  //������
//	morphologyEx(srcImg, dstImg, MORPH_CLOSE, element);  //������
//	morphologyEx(srcImg, dstImg, MORPH_GRADIENT, element);  //��̬ѧ�ݶ�����
//	morphologyEx(srcImg, dstImg, MORPH_TOPHAT, element);  //��ñ����
//	morphologyEx(srcImg, dstImg, MORPH_BLACKHAT, element);  //�\ñ����

	imshow("src", srcImg);
	imshow("dst", dstImg);
	waitKey(0);
}