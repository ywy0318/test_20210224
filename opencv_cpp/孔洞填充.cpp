#include "opencv2/opencv.hpp"
using namespace cv;

void main()
{
	Mat src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	Mat temp = src.clone();
	//ת�Ҷ�ͼ����ֵ��
	cvtColor(src, src, CV_BGR2GRAY);
	threshold(src, src, 100, 255, THRESH_BINARY);
	imshow("thres", src);
	//���Ҳ���������
	vector<vector<Point>>contours;
	vector<Vec4i>hierarcy;
	findContours(src, contours, hierarcy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	//��Ч��
	/////�׶����
	//findContours(src, contours, hierarcy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE); //��������
	//drawContours(temp, contours, -1, Scalar(0, 255, 0), -1, 8); //��������

	//�����ͨ��
	for (int i = 0; i < contours.size(); i++)
	{
		drawContours(temp, contours,i,Scalar(rand()%255, rand() % 255, rand() % 255),-1,8);
	}

	imshow("contours", temp);
	waitKey(0);
}