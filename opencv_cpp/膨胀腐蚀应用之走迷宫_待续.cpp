#include "opencv2/opencv.hpp"
#include<iostream>
using namespace cv;
using namespace std;

//�Թ���ͼƬ
void main() {
	Mat img = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\7.jpg");
	int thres_min = 220;  //��ֵ����С��ֵ
	if (!img.empty()) {
		//��ֵ��
		threshold(img, img, thres_min, 255, THRESH_BINARY);
		imshow("img_thres", img);
		//img����
		Mat copy = img.clone();//����ԭͼ���Ҳ�������ԭͼ�ı�
		cvtColor(copy, copy, CV_BGR2GRAY);//��ɫͼת�Ҷ�ͼ
		threshold(copy, copy, thres_min, 255, THRESH_BINARY_INV);//��ת����ɫ���ɫ����ɫ���ɫ
		imshow("copy", copy);
		//����copy������
		vector<vector<Point>>contours;
		findContours(copy, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
		//����������ȫ��ͼ����
		Mat draw;
		draw = Mat::zeros(img.size(), CV_32FC1);//����һ��img��С��ȫ��ͼ��
		drawContours(draw, contours, 0, Scalar(255), -2);
		imshow("img2", draw);
		//�������͸�ʴ����
		Mat dilated, eroded;
		Mat kernel = getStructuringElement(MORPH_RECT, Size(19, 19));//����ṹԪ��
		dilate(draw, dilated, kernel, Point(-1, -1), 2);//��������
		imshow("dilate", dilated);
		erode(dilated, eroded, kernel, Point(-1, -1), 2);
		imshow("erode", eroded);
		//���͸�ʴ���
		Mat diff;
		absdiff(dilated, eroded, diff);
		diff.convertTo(diff, CV_8UC1);//ת��Ϊ��ͨ��ͼ�����Ҷ�ͼ��
		imshow("diff", diff);
		//�ڲ���ͼdiff�в�������,Ȼ����ԭͼ�л�������
		vector<vector<Point>>contours2;
		findContours(diff, contours2, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
		drawContours(img, contours2, 0, Scalar(0, 255, 0), -1);//-1��ʾ���������ڲ���������ʾ����������ϸ
		imshow("result", img);
	}
	waitKey(0);
	destroyAllWindows();
}