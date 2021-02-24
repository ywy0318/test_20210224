#include "opencv2/opencv.hpp"
using namespace cv;
void main()
{
	//��Ӿ��εĲ��һ���
	Mat srcImg = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\13.jpg");
	imshow("src", srcImg);
	Mat dstImg = srcImg.clone();  //ԭͼ����
	cvtColor(srcImg, srcImg, CV_BGR2GRAY); //תΪ�Ҷ�ͼ
	threshold(srcImg, srcImg, 100, 255, CV_THRESH_BINARY); //��ֵ��

	vector<vector<Point>> contours;
	vector<Vec4i> hierarcy;
	findContours(srcImg, contours, hierarcy, CV_RETR_EXTERNAL, CHAIN_APPROX_NONE); //��������
	vector<Rect> boundRect(contours.size()); //������Ӿ��μ���
											 //drawContours(dstImg, contours, -1, Scalar(0, 0, 255), 2, 8);  //��������
	int x0 = 0, y0 = 0, w0 = 0, h0 = 0;
	for (int i = 0; i<contours.size(); i++)
	{
		boundRect[i] = boundingRect((Mat)contours[i]); //����ÿ����������Ӿ���
		drawContours(dstImg, contours, i, Scalar(0, 0, 255), 2, 8);  //��������
		x0 = boundRect[i].x;  //��õ�i����Ӿ��ε����Ͻǵ�x����
		y0 = boundRect[i].y; //��õ�i����Ӿ��ε����Ͻǵ�y����
		w0 = boundRect[i].width; //��õ�i����Ӿ��εĿ��
		h0 = boundRect[i].height; //��õ�i����Ӿ��εĸ߶�
		rectangle(dstImg, Point(x0, y0), Point(x0 + w0, y0 + h0), Scalar(0, 255, 0), 2, 8); //���Ƶ�i����Ӿ���
	}
	imshow("boundRect", dstImg);
	waitKey(0);
}