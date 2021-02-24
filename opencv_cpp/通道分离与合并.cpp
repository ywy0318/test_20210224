#include<opencv2/opencv.hpp>
using namespace cv;

void main() {
	Mat img = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\6.jpg");
	Mat dst;
	vector<Mat>channels;//定义Mat类型的向量

	split(img, channels);//通道分离
	Mat blue = channels.at(0);
	Mat green = channels.at(1);
	Mat red = channels.at(2);

	threshold(blue, blue, 200, 255, THRESH_BINARY);//二值化：大于200的赋值255，小于200的赋值0
	threshold(green, green, 200, 255, THRESH_BINARY);
	threshold(red, red, 200, 255, THRESH_BINARY);

	merge(channels, dst);//通道合并

	imshow("原图", img);
	imshow("blue", blue);
	imshow("green", green);
	imshow("red", red);
	imshow("dst", dst);
	waitKey(0);
}