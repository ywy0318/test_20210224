#include<opencv2/opencv.hpp>
using namespace cv;
Mat dst;
int value = 21;

void onChange(int, void* param) {
	Mat src = *(Mat *)param;
	if (value % 2 == 0) {
		medianBlur(src, dst, value - 1);//中值滤波的第三个参数为奇数
	}
	else
	{
		medianBlur(src, dst, value);
	}
	imshow("windows", dst);
}

void main() {
	Mat src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	namedWindow("windows", CV_WINDOW_AUTOSIZE);
	createTrackbar("滑动条", "windows", &value, 99, onChange, &src);//最后一个参数若设置为0，移动滑动条时会报错
	medianBlur(src, dst, 21);
	imshow("windows", dst);
	waitKey(0);
}