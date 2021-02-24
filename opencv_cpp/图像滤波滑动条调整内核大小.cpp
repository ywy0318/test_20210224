#include<opencv2/opencv.hpp>
using namespace cv;
Mat dst;
int value = 21;

void onChange(int, void* param) {
	Mat src = *(Mat *)param;
	if (value % 2 == 0) {
		medianBlur(src, dst, value - 1);//��ֵ�˲��ĵ���������Ϊ����
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
	createTrackbar("������", "windows", &value, 99, onChange, &src);//���һ������������Ϊ0���ƶ�������ʱ�ᱨ��
	medianBlur(src, dst, 21);
	imshow("windows", dst);
	waitKey(0);
}