#include "opencv2/opencv.hpp"
using namespace cv;

void main()
{
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y, dst;

	Mat src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\7.jpg", 0);
	imshow("src", src);

	Sobel(src, grad_x, CV_16S, 1, 0, 3);//16λ�з��ţ���ʱ����������x�����������Ϊ1,0
	convertScaleAbs(grad_x, abs_grad_x);//תΪ�޷���
	imshow("X����", abs_grad_x);

	Sobel(src, grad_y, CV_16S, 0, 1, 3);//y�����������Ϊ0,1
	convertScaleAbs(grad_y, abs_grad_y);
	imshow("Y����", abs_grad_y);

	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
	imshow("�ϲ�Ч��", dst);

	waitKey(0);
	destroyAllWindows();
}