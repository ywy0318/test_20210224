#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

//���������¾ͻửԲȦ,
//esc��


Mat img(500, 500, CV_8UC3, Scalar(255, 255, 255));//�����ȫ�ֱ���

void OnMouse(int event, int x, int y, int flags, void* param) {
	if (event == CV_EVENT_LBUTTONDOWN) {//�������������
		cout << "mouse down" << endl;//����̨���
		circle(img, Point(x, y), 80, Scalar(255, 255, 0), 2, 8);//��ȫ�ֱ���img�ϻ�Բ
	}
}

void main() {
	namedWindow("mouse", CV_WINDOW_AUTOSIZE);
	setMouseCallback("mouse", OnMouse, 0);
	while (1) {
		imshow("mouse", img);
		if (27 == waitKey(10))//ÿ��10�������Ƿ���esc��
			break;
	}
}