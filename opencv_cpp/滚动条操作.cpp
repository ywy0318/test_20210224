#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;


Mat dst;
int value = 20;

void onChange(int, void* param) {
	Mat src = *(Mat*)param;
	threshold(src, dst, value, 255, THRESH_BINARY);//��ֵ��
												   //Canny(src,dst,value,255);//canny��Ե���
	imshow("TrackBar", dst);
}

void main() {
	Mat src = imread("1.jpg", 0);//����Ҷ�ͼ
	namedWindow("TrackBar", CV_WINDOW_AUTOSIZE);
	createTrackbar("Threshold", "TrackBar", &value, 255, onChange, &src);

	threshold(src, dst, value, 255, THRESH_BINARY);
	//Canny(src,dst,value,255);
	imshow("TrackBar", dst);//����21/22/23�����д������ȥ���Ļ�����δ����������������£������л�����ʾ

	waitKey(0);
}