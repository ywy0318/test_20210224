#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

//根据鼠标左键按下抬起确定矩形两个对角的坐标

Point pt;
void OnMouse(int event, int x, int y, int flags, void* param) {
	Mat img = *(Mat*)param;//将param强制转换为Mat指针，*(Mat*)=Mat，就如*（int*）=int一样
	switch (event) {
	case CV_EVENT_LBUTTONDOWN://鼠标左键按下时
		pt.x = x;
		pt.y = y;
		break;
	case CV_EVENT_LBUTTONUP://鼠标左键抬起时
		rectangle(img, pt, Point(x, y), Scalar(0, 255, 0), 2, 8);
		break;
	default:
		break;
	}
}

void main() {
	Mat img(500, 500, CV_8UC3, Scalar(255, 255, 255));
	namedWindow("mouse", CV_WINDOW_AUTOSIZE);
	setMouseCallback("mouse", OnMouse, &img);//传入img的地址，这样就不必将img设置成全局变量了

	while (1) {
		imshow("mouse", img);
		if (27 == waitKey(10))//每隔10毫秒检测是否按下esc键
			break;
	}
}