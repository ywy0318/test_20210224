#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

//�����ڴ��쳣 ע��ͼƬ·��
void main() {
	//��̬��ַ����
	Mat img = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.png");
	imshow("src", img);
	Mat dst = img.clone();
	int rowNumber = img.rows;//��ȡ����
	int colNumber = img.cols;//��ȡ����
	for (int i = 0; i<rowNumber; i++) {
		for (int j = 0; j <colNumber; j++)
		{
			dst.at<Vec3b>(i, j)[0] = 255;//��ɫͨ��
			dst.at<Vec3b>(i, j)[1] = 0;//��ɫͨ��
			dst.at<Vec3b>(i, j)[2] = 0;//��ɫͨ��
									   //dst.at<uchar>(i,j)=255;//�Ҷ�ͼ��
		}
	}
	imshow("dst", dst);
	waitKey(0);
}