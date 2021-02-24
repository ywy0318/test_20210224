#include "opencv2/opencv.hpp"
using namespace cv;

void main()
{
	Mat src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\12.jpg");
	//
	//Mat temp = src.clone();

	/***/
	//��Ч��1
	Mat temp(src.rows,src.cols,CV_8UC3,Scalar(255,255,255));
	/***/

	//ת�Ҷ�ͼ����ֵ��
	cvtColor(src, src, CV_BGR2GRAY);
	threshold(src, src, 100, 255, THRESH_BINARY);
	imshow("thres", src);
	//���Ҳ���������
	vector<vector<Point>>contours;
	vector<Vec4i>hierarcy;
	/***/
	//��Ч��1
	findContours(src, contours, hierarcy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);
	/***/

	//findContours(src, contours, hierarcy, CV_RETR_TREE, CV_LINK_RUNS);
	/*drawContours(temp,contours,-1,Scalar(0,255,0),2,8);    ���Ʋ���ʾ��������
	imshow("contours",temp);*/
	/************************/
	//����������ÿһ����
	//for (int i = 0; i<contours.size(); i++) {
	//	for (int j = 0; j<contours[i].size(); j++) {
	//		circle(temp, Point(contours[i][j].x, contours[i][j].y), 3, Scalar(0, 255, 0), 2, 8);
	//	}
	//}
	/************************/
	//����̫�ܼ��ˣ���С�ܼ���
	//for (int i = 0; i<contours.size(); i++) {
	////	for (int j = 0; j<contours[i].size(); j++) {
	////		circle(temp, Point(contours[i][j].x, contours[i][j].y), 3, Scalar(0, 255, 0), 2, 8);
	////	}
	//	for (int j = 0; j<contours[i].size(); j += 15) {
	//		circle(temp, Point(contours[i][j].x, contours[i][j].y), 3, Scalar(0, 255, 0), 2, 8);
	//	}
	//}
	/************************************/
	//����һ��Ч������̬���ߣ�
	//for (int i = 0; i<contours.size(); i++) {
	//	for (int j = 0; j<contours[i].size(); j += 15) {
	//		circle(temp, Point(contours[i][j].x, contours[i][j].y), 3, Scalar(0, 255, 0), 2, 8);
	//		line(temp, Point(10, 10), Point(contours[i][j].x, contours[i][j].y), Scalar(0, 0, 255), 1, 8);
	//		waitKey(100);
	//		imshow("contours", temp);
	//	}
	//}
	/***********************************/
	
	/***/
	//��Ч��1
	for (int i = 0; i<contours.size(); i++) {
		for (int j = 0; j<contours[i].size(); j += 15) {
			circle(temp, Point(contours[i][j].x, contours[i][j].y), 3, Scalar(0, 0, 0), 2, 8);
			//line(temp, Point(10, 10), Point(contours[i][j].x, contours[i][j].y), Scalar(0, 0, 255), 1, 8);
			waitKey(100);
			imshow("contours", temp);
		}
	}
	/***/


	/***/
	//��Ч��1
	//imshow("contours", temp);
	/***/
	waitKey(0);
}