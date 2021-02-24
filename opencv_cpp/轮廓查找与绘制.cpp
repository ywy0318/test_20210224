#include"opencv2/opencv.hpp"
#include<iostream>
using namespace std;
using namespace cv;

void main()
{
	Mat srcImg = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\7.jpg");
	Mat tempImg = srcImg.clone();
	//Mat draw(srcImg.rows, srcImg.cols, CV_8UC3);
	cvtColor(srcImg, srcImg, CV_BGR2GRAY); //תΪ�Ҷ�ͼ
	threshold(srcImg, srcImg, 100, 255, CV_THRESH_BINARY);//ͼ���ֵ����value>threshold����100��?255:0
	imshow("srcImg", srcImg);  //��������ǰ

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	//findContours(srcImg, contours, hierarchy,RETR_EXTERNAL, CHAIN_APPROX_SIMPLE ); //������������ѹ���洢������
	findContours(srcImg, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE); //������������
																			   //findContours(srcImg, contours, hierarchy,CV_RETR_CCOMP, CHAIN_APPROX_SIMPLE ); //������������
																			   //findContours(srcImg, contours, hierarchy,RETR_TREE, CHAIN_APPROX_NONE ); //���������������洢����������
	imshow("cont", srcImg);  //�������Һ� 
	drawContours(tempImg, contours, -1, Scalar(0, 255, 0), 2);  //����������-1���������������
	cout << "num=" << contours.size() << endl; //�����������
	imshow("contours", tempImg);

	waitKey(0);
}