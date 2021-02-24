#include "opencv2/opencv.hpp"
#include<iostream>
using namespace cv;
using namespace std;

void main()
{
	Mat img = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg", 0);  //以灰度方式打开，灰度图和彩色图直方图结果不同
	imshow("src", img);

	Mat dstHist;  //定义存储直方图变量
	int dims = 1;  //需要统计的特征数目(只统计灰度值)
	float hranges[] = { 0, 256 };  //范围[0,256),注意是最大值加1
	const float* ranges[] = { hranges };
	int bins = 256;//组距：简单理解为直方图分为几个柱子
	int channels = 0;
	//计算直方图
	calcHist(&img, 1, &channels, Mat(), dstHist, dims, &bins, ranges);

	int scale = 1;
	Mat dstImg(bins * scale, bins * 1, CV_8UC3, Scalar(0));  //定义直方图输出图像,长×宽
	double minValue = 0;
	double maxValue = 0;
	minMaxLoc(dstHist, &minValue, &maxValue);//统计直方图dstHist的最小最大值,并返回该值位置
	int hpt = saturate_cast<int>(0.9*bins);  //设置最大值并防止溢出
	int j = 0;
	//绘制直方图
	for (int i = 0; i<256; i++)
	{
		float binValue = dstHist.at<float>(i);
		//if(i>250)
		cout << "i=" << i << "---Value=" << binValue << endl;
		int realValue = saturate_cast<int>(binValue*hpt / maxValue);  //归一化数据
																	  //cout<<"i="<<i<<"---Value="<<realValue<<endl;
		line(dstImg, Point(i*scale, bins - 1), Point(i*scale, bins - realValue), Scalar(0, 255, 0), 1, 8);
		//第二个参数及line()修改直方图密度调整宽度

		//左上角和右下角坐标，坐标系如下图所示
		//rectangle(dstImg, Point(i*scale, bins-1), Point(i*scale+1, bins-realValue), Scalar(0, 255, 0), 1);
		//rectangle(dstImg, Point(j*scale, bins-1), Point(j*scale+1, bins-realValue), Scalar(rand()%255, rand()%255, rand()%255), -1);
		//rectangle(dstImg, Point(j*scale, bins-1), Point(j*scale+1, bins-realValue), Scalar(rand()%255, rand()%255, rand()%255), -1);
		//j=j+3;


	}
	imshow("Histogram", dstImg);
	waitKey(0);
	destroyAllWindows();
}