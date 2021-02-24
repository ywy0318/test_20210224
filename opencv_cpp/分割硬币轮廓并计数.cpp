#include "opencv2/opencv.hpp"
#include<iostream>
using namespace cv;
using namespace std;
void main()
{
	//�ָ�Ӳ������
	Mat srcImg = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\18.jpg");
	imshow("src", srcImg);
	Mat dstImg = srcImg.clone();  //ԭͼ����
	cvtColor(srcImg, srcImg, CV_BGR2GRAY); //תΪ�Ҷ�ͼ
	threshold(srcImg, srcImg, 100, 255, CV_THRESH_BINARY); //��ֵ��
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1)); //��ýṹԪ��
	dilate(srcImg, srcImg, element); //���Ͳ���
	imshow("dilate", srcImg);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarcy;
	findContours(srcImg, contours, hierarcy, CV_RETR_EXTERNAL, CHAIN_APPROX_NONE); //��������
	vector<Rect> boundRect(contours.size()); //������Ӿ��μ���
	int x0 = 0, y0 = 0, w0 = 0, h0 = 0, num = 0;
	for (int i = 0; i<contours.size(); i++)
	{
		boundRect[i] = boundingRect((Mat)contours[i]); //����ÿ����������Ӿ���
		drawContours(dstImg, contours, i, Scalar(0, 0, 255), 2, 8);  //��������
		x0 = boundRect[i].x;
		y0 = boundRect[i].y;
		w0 = boundRect[i].width;
		h0 = boundRect[i].height;
		if (w0>30 && h0>30)//ɸѡ
		{
			rectangle(dstImg, Point(x0, y0), Point(x0 + w0, y0 + h0), Scalar(0, 255, 0), 2, 8); //���Ƶ�i����Ӿ���
			num++;
		}
	}
	cout << "Ӳ��������" << num;
	imshow("boundRect", dstImg);
	waitKey(0);
}