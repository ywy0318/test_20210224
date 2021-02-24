#include "opencv2/opencv.hpp"
using namespace cv;
//using namespace std;
void main()
{
	//{//均衡化的主要代码}
		Mat srcImg = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg", 0);  //以灰度方式打开，需要输入单通道图像
		imshow("src", srcImg);
		Mat dstImg;  //均衡化后的图像
		equalizeHist(srcImg, dstImg);
		imshow("dst", dstImg);
	//	{//均衡化的主要代码}

	//绘制src直方图
	MatND dstHist;  //定义存储直方图变量
	int dims = 1;  //需要统计的特征数目(只统计灰度值)
	float hranges[] = { 0, 256 };  //范围[0,256)注意是最大值加1
	const float* ranges[] = { hranges };
	int bins = 256;
	int channels = 0;
	calcHist(&srcImg, 1, &channels, Mat(), dstHist, dims, &bins, ranges);
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
	imshow("src_hist", HistImg);

	//绘制dst直方图
	calcHist(&dstImg, 1, &channels, Mat(), dstHist, dims, &bins, ranges);
	Mat HistImg2(bins * scale, bins * 1, CV_8UC3, Scalar(0));  //定义直方图输出图像
	for (int i = 0; i<256; i++)
	{
		float binValue = dstHist.at<float>(i);
		int realValue = saturate_cast<int>(binValue*hpt / maxValue);  //归一化数据
		line(HistImg2, Point(i*scale, bins - 1), Point(i*scale, bins - realValue), Scalar(0, 255, 0), 1, 8);
	}
	imshow("dst_hist", HistImg2);

	waitKey(0);
}