#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

void main() {
	Mat img = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.png");
	imshow("src", img);
	Mat dst = img.clone();
	int rowNumber = img.rows;//��ȡ����
	int colNumber = img.cols*img.channels();//������ͨ����=ÿһ�е�Ԫ�ظ���
	for (int i = 0; i<rowNumber; i++) {
		uchar* data = dst.ptr<uchar>(i);//��ȡÿһ���׵�ַ��ptr�������Եõ�ͼ�������е��׵�ַ
		for (int j = 0; j <colNumber; j++)
		{
			//data[j]=255;//�Ҷ�ͼ
			switch (j % 3)
			{
			case 0://��ɫͨ��
				data[j] = 255;
				break;
			case 1://��ɫͨ��
				data[j] = 0;
				break;
			case 2://��ɫͨ��
				data[j] = 255;
				break;
			}
		}
	}
	imshow("dst", dst);
	waitKey(0);
}