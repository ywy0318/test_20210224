#include<iostream>
#include<opencv2\opencv.hpp>
#include "highgui.h"
#include"cvaux.h"
#include"cxcore.h"
#include"opencv2/imgproc.hpp"
#include<string>
using namespace std;
using namespace cv;
//ѧϰMat���÷����Ͷ�Matͼ�񸳳�ʼֵ�ķ�����ѧϰMat���캯�����÷���
int main()
{
	//��ʼ��ͼ�����
	Mat red_img(Size(240,240),CV_8UC3,Scalar(0,0,255));
	Mat white_img(Size(240, 240), CV_8UC3, Scalar::all(255));
	Mat black_img=Mat::zeros(Size(240, 240), CV_8UC3);

	//���¶�ͼ���ͨ����ֵ
	Mat green_img = red_img.clone();
	green_img = Scalar(255,255,255);//blue--green--redȫ������255�Ļ����ǰ�ɫ�ģ�ȫ������0�Ļ����Ǻ�ɫ��
	/*
	�������ڵĺ�����Ϊ
	cv::namedWindow(const string & windowName, int flag)
	CV_WINDOW_NORMAL or CV_WINDOW_AUTOSIZE:  normal ģʽ�¿����ֶ��������ڴ�С�� �� auto ģʽ��Ĭ�ϣ��´��ڽ��Զ���Ӧͼ���С���޷��ֶ�������(gtk3, qt �¿���)
	CV_WINDOW_FREERATIO or CV_WINDOW_KEEPRATIO:  free_ratio ģʽ�µ���ͼ��ʱ����������ʣ� �� keep_ratio ģʽ������ͼ������ű��� ��qt�¿��ã�
	CV_GUI_NORMAL or CV_GUI_EXPANDED: expanded ģʽ�½���ʾ����Ĺ������Ͱ�ť��NOTE����qt�¿��ã�	
	*/
	namedWindow("red_img", CV_WINDOW_AUTOSIZE| CV_WINDOW_FREERATIO);
	namedWindow("white_img", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
	namedWindow("black_img", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
	namedWindow("green_img", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);

	imshow("red_img",red_img);
	imshow("white_img", white_img);
	imshow("black_img", black_img);
	imshow("green_img", green_img);
	waitKey(0);
	system("pause");
	return 0;
}