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

	MatND dstHist;  //定义存储直方图变量
	int dims = 1;  //需要统计的特征数目(只统计灰度值)
	float hranges[] = { 0, 256 };  //范围[0,256)注意是最大值加1
	const float* ranges[] = { hranges };
	int bins = 256;
	int channels = 0;
	calcHist(&src1, 1, &channels, Mat(), dstHist, dims, &bins, ranges);
	int scale = 1;
	Mat HistImg(bins * scale, bins * 1, CV_8UC3, Scalar(0));  //定义直方图输出图像
	double minValue = 0;
	double maxValue = 0;
	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);
	int hpt = saturate_cast<int>(0.9*bins);  //设置最大值并防止溢出
	int j = 0;
	for (int i = 0; i<256; i++)
	{
		float binValue = dstHist.at<float>(i);
		int realValue = saturate_cast<int>(binValue*hpt / maxValue);  //归一化数据
		line(HistImg, Point(i*scale, bins - 1), Point(i*scale, bins - realValue), Scalar(0, 255, 0), 1, 8);
	}
	imshow("src1_hist", HistImg);

	MatND dstHist2;  //定义存储直方图变量
	calcHist(&src2, 1, &channels, Mat(), dstHist2, dims, &bins, ranges);
	Mat HistImg2(bins * scale, bins * 1, CV_8UC3, Scalar(0));  //定义直方图输出图像
	minMaxLoc(dstHist2, &minValue, &maxValue, 0, 0);
	for (int i = 0; i<256; i++)
	{
		float binValue = dstHist2.at<float>(i);
		int realValue = saturate_cast<int>(binValue*hpt / maxValue);  //归一化数据
		line(HistImg2, Point(i*scale, bins - 1), Point(i*scale, bins - realValue), Scalar(0, 255, 0), 1, 8);
	}
	imshow("src2_hist", HistImg2);

	double matchValue0 = compareHist(dstHist, dstHist2, CV_COMP_CORREL);  //值越大相似度越高
	double matchValue1 = compareHist(dstHist, dstHist2, CV_COMP_CHISQR);  //值越小相似度越高
	double matchValue2 = compareHist(dstHist, dstHist2, CV_COMP_INTERSECT); //值越大相似度越高
	double matchValue3 = compareHist(dstHist, dstHist2, CV_COMP_BHATTACHARYYA); //值越小相似度越高

	cout << "matchValue0(max_best)=" << matchValue0 << endl;
	cout << "matchValue1(min_best)=" << matchValue1 << endl;
	cout << "matchValue2(max_best)=" << matchValue2 << endl;
	cout << "matchValue3(min_best)=" << matchValue3 << endl;

	waitKey(0);
}