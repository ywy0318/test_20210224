#include<iostream>
#include<opencv2\opencv.hpp>
#include "highgui.h"
#include"cvaux.h"
#include"cxcore.h"
#include"opencv2/imgproc.hpp"
#include<string>
using namespace std;
using namespace cv;
int main()
{
	//--1--˫��б�߷�
	string imgpath0 = "E:\\Visual Studio 2010\\Projects\\opencv_2018_12_21\\opencv_2018_12_21\\1.jpg";
	Mat img1, img2;//
	img1 = imread(imgpath0,IMREAD_COLOR);
	if (img1.empty())//��ȡͼƬʧ��
	{
		cout << "open filed" << endl;
		return -1;
	}
	namedWindow("ԭͼ",WINDOW_AUTOSIZE);//����һ������
	imshow("ԭͼ",img1);
	cvtColor(img1,img2,CV_RGB2GRAY);//��ͼƬת��Ϊ�Ҷ�ͼ
	//��ͼƬд�뵽ͼƬ��
	imwrite("E:\\Visual Studio 2010\\Projects\\opencv_2018_12_21\\opencv_2018_12_21\\1.bmp",img2);
	namedWindow("�Ҷ�ͼ",WINDOW_AUTOSIZE);
	imshow("�Ҷ�ͼ",img2);
	waitKey(0);//�ȴ�һ�ΰ������������
	
	system("pause");
	return 0;
}