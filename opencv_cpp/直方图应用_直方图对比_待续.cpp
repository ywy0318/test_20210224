#include "opencv2/opencv.hpp"
#include<iostream>
using namespace cv;
using namespace std;

void main()
{
	Mat src1 = imread("E://a.jpg");
	Mat src2 = imread("E://b.jpg");
	imshow("src1", src1);
	imshow("src2", src2);

	MatND dstHist;  //����洢ֱ��ͼ����
	int dims = 1;  //��Ҫͳ�Ƶ�������Ŀ(ֻͳ�ƻҶ�ֵ)
	float hranges[] = { 0, 256 };  //��Χ[0,256)ע�������ֵ��1
	const float* ranges[] = { hranges };
	int bins = 256;
	int channels = 0;
	calcHist(&src1, 1, &channels, Mat(), dstHist, dims, &bins, ranges);
	int scale = 1;
	Mat HistImg(bins * scale, bins * 1, CV_8UC3, Scalar(0));  //����ֱ��ͼ���ͼ��
	double minValue = 0;
	double maxValue = 0;
	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);
	int hpt = saturate_cast<int>(0.9*bins);  //�������ֵ����ֹ���
	int j = 0;
	for (int i = 0; i<256; i++)
	{
		float binValue = dstHist.at<float>(i);
		int realValue = saturate_cast<int>(binValue*hpt / maxValue);  //��һ������
		line(HistImg, Point(i*scale, bins - 1), Point(i*scale, bins - realValue), Scalar(0, 255, 0), 1, 8);
	}
	imshow("src1_hist", HistImg);

	MatND dstHist2;  //����洢ֱ��ͼ����
	calcHist(&src2, 1, &channels, Mat(), dstHist2, dims, &bins, ranges);
	Mat HistImg2(bins * scale, bins * 1, CV_8UC3, Scalar(0));  //����ֱ��ͼ���ͼ��
	minMaxLoc(dstHist2, &minValue, &maxValue, 0, 0);
	for (int i = 0; i<256; i++)
	{
		float binValue = dstHist2.at<float>(i);
		int realValue = saturate_cast<int>(binValue*hpt / maxValue);  //��һ������
		line(HistImg2, Point(i*scale, bins - 1), Point(i*scale, bins - realValue), Scalar(0, 255, 0), 1, 8);
	}
	imshow("src2_hist", HistImg2);

	double matchValue0 = compareHist(dstHist, dstHist2, CV_COMP_CORREL);  //ֵԽ�����ƶ�Խ��
	double matchValue1 = compareHist(dstHist, dstHist2, CV_COMP_CHISQR);  //ֵԽС���ƶ�Խ��
	double matchValue2 = compareHist(dstHist, dstHist2, CV_COMP_INTERSECT); //ֵԽ�����ƶ�Խ��
	double matchValue3 = compareHist(dstHist, dstHist2, CV_COMP_BHATTACHARYYA); //ֵԽС���ƶ�Խ��

	cout << "matchValue0(max_best)=" << matchValue0 << endl;
	cout << "matchValue1(min_best)=" << matchValue1 << endl;
	cout << "matchValue2(max_best)=" << matchValue2 << endl;
	cout << "matchValue3(min_best)=" << matchValue3 << endl;

	waitKey(0);
}