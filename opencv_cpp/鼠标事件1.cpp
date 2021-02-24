#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

//鼠标左键按下就会画圆圈,
//esc腿


Mat img(500, 500, CV_8UC3, Scalar(255, 255, 255));//定义成全局变量

void OnMouse(int event, int x, int y, int flags, void* param) {
	if (event == CV_EVENT_LBUTTONDOWN) {//如果鼠标左键按下
		cout << "mouse down" << endl;//控制台输出
		circle(img, Point(x, y), 80, Scalar(255, 255, 0), 2, 8);//在全局变量img上画圆
	}
}

void main() {
	namedWindow("mouse", CV_WINDOW_AUTOSIZE);
	setMouseCallback("mouse", OnMouse, 0);
	while (1) {
		imshow("mouse", img);
		if (27 == waitKey(10))//每隔10毫秒检测是否按下esc键
			break;
	}
}