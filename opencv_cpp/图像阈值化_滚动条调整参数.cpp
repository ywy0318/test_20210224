#include<opencv2/opencv.hpp>
using namespace cv;

Mat src, dst, dst2;
int thres_value = 21, block_size = 5, c = 5;

void onThreshold(int, void*) {
	threshold(src, dst, thres_value, 255, CV_THRESH_BINARY);
	imshow("固定阈值", dst);
}
void onAdaptiveThreshold(int, void *) {
	if (block_size % 2 == 0)    block_size++;//如果block_size是偶数
	adaptiveThreshold(src, dst2, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, block_size, c);
	imshow("自适应阈值", dst2);
}

void main() {
	src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg", 0);//以灰度模式读入    
	namedWindow("固定阈值", CV_WINDOW_AUTOSIZE);
	namedWindow("自适应阈值", CV_WINDOW_AUTOSIZE);
	createTrackbar("Threshold", "固定阈值", &thres_value, 255, onThreshold, 0);
	createTrackbar("Block_size", "自适应阈值", &block_size, 255, onAdaptiveThreshold, 0);
	createTrackbar("C", "自适应阈值", &c, 255, onAdaptiveThreshold, 0);

	onThreshold(thres_value, 0); //回调函数初始化
	onAdaptiveThreshold(block_size, 0);
	onAdaptiveThreshold(c, 0);

	imshow("src", src);
	waitKey(0);
}