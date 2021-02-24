#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

//��������������̧��ȷ�����������Խǵ�����

Point pt;
void OnMouse(int event, int x, int y, int flags, void* param) {
	Mat img = *(Mat*)param;//��paramǿ��ת��ΪMatָ�룬*(Mat*)=Mat������*��int*��=intһ��
	switch (event) {
	case CV_EVENT_LBUTTONDOWN://����������ʱ
		pt.x = x;
		pt.y = y;
		break;
	case CV_EVENT_LBUTTONUP://������̧��ʱ
		rectangle(img, pt, Point(x, y), Scalar(0, 255, 0), 2, 8);
		break;
	default:
		break;
	}
}

void main() {
	Mat img(500, 500, CV_8UC3, Scalar(255, 255, 255));
	namedWindow("mouse", CV_WINDOW_AUTOSIZE);
	setMouseCallback("mouse", OnMouse, &img);//����img�ĵ�ַ�������Ͳ��ؽ�img���ó�ȫ�ֱ�����

	while (1) {
		imshow("mouse", img);
		if (27 == waitKey(10))//ÿ��10�������Ƿ���esc��
			break;
	}
}