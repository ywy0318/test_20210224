//Mat img = imread("E://1.jpg");
//imshow("src", img);
//Mat dst = img.clone();
//int rowNumber = img.rows;
//int colNumber = img.cols*img.channels();//��ȡÿһ�е�Ԫ��
//for (int i = 0; i<rowNumber; i++) {
//	uchar* data = dst.ptr<uchar>(i);//��ȡÿһ���׵�ַ
//	for (int j = 0; j <colNumber; j++)
//	{
//		switch (j % 3)
//		{
//		case 0://��ɫͨ��
//			data[j] = data[j] / 64 * 64 + 64 / 2;
//			break;
//		case 1://��ɫͨ��
//			data[j] = data[j] / 64 * 64 + 64 / 2;
//			break;
//		case 2://��ɫͨ��
//			data[j] = data[j] / 64 * 64 + 64 / 2;
//			break;
//		}
//	}
//}
//imshow("dst", dst);
//waitKey(0);


#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

void main() {
	Mat img = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\cat2.jpg");
	imshow("src", img);
	Mat dst = img.clone();
	int rowNumber = img.rows;
	int colNumber = img.cols;
	int i, j;
	for (int k = 0; k < 400; k++)//���������ĸ�������ʱΪ400��
	{
		i = rand() % rowNumber;//������������ȡ��
		j = rand() % colNumber;//������������ȡ��
		dst.at<Vec3b>(i, j)[0] = 255;
		dst.at<Vec3b>(i, j)[1] = 255;
		dst.at<Vec3b>(i, j)[2] = 255;//�������еġ�255������Ϊ��0��������������
	}
	imshow("dst", dst);
	waitKey(0);
}







