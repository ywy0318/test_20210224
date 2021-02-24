#include "opencv2/opencv.hpp"
using namespace cv;

void main()
{
	Mat src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	imshow("src", src);

	//分割通道
	vector<Mat>channels;
	split(src, channels);
	Mat blue, green, red, dst;
	blue = channels.at(0);
	green = channels.at(1);
	red = channels.at(2);
	//分别对BGR通道做直方图均衡化
	equalizeHist(blue, blue);
	equalizeHist(green, green);
	equalizeHist(red, red);
	//合并通道
	merge(channels, dst);
	imshow("dst", dst);

	waitKey(0);
}