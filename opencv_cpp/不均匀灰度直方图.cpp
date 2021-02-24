#include "opencv2/opencv.hpp"
#include<iostream>
using namespace cv;
using namespace std;

void main()
{
	Mat img = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg", 0);
	imshow("src", img);

	Mat dstHist;
	int channels = 0;
	int histSize[1] = { 5 };
	float hranges[6] = { 0,50,100,150,200,256 };
	const float* ranges[1] = { hranges };
	int size = 256;
	//计算直方图
	calcHist(&img, 1, &channels, Mat(), dstHist, 1, histSize, ranges, false);

	int scale = 1;
	Mat dstImg(size*scale, size, CV_8UC3, Scalar(0));
	double minValue = 0;
	double maxValue = 0;
	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);
	int hpt = saturate_cast<int>(0.9*size);//设置最大值并防止溢出
	int j = 0;
	for (int i = 0; i < 5; i++)
	{
		float binValue = dstHist.at<float>(i);
		cout << "i=" << i << "---Value=" << binValue << endl;
		int realValue = saturate_cast<int>(binValue*hpt / maxValue);
		rectangle(dstImg, Point(j*scale, size - 1), Point((j + 20)*scale - 1, size - realValue), Scalar(0, 255, 0), -1);
		j += 35;
	}

	imshow("Histogram", dstImg);
	waitKey(0);
	destroyAllWindows();

}