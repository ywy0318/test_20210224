#include "opencv2/opencv.hpp"
using namespace cv;

void main()
{
	Mat img1 = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	Mat img2 = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	Mat diff;
	absdiff(img1, img2, diff);//��������������Ա�����ָ�ֵ=0�����
	imshow("img1", img1);
	imshow("img2", img2);
	imshow("diff", diff);

	Mat gray;
	cvtColor(diff, gray, COLOR_BGR2GRAY);//תΪ�Ҷ�ͼ
										 //adaptiveThreshold(gray,gray,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY_INV,15,3);//����Ӧ��ֵ�е㲻��
	threshold(gray, gray, 5, 255, THRESH_BINARY);
	imshow("threshold", gray);

	//������̬ѧ����
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));//����ṹԪ��
	morphologyEx(gray, gray, MORPH_OPEN, element);//������
	medianBlur(gray, gray, 9);//��ֵ�˲�
	dilate(gray, gray, element);
	imshow("dst", gray);

	waitKey(0);
}