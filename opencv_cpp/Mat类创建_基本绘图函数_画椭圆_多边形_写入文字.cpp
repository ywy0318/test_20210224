#include <opencv2/opencv.hpp>
using namespace cv;

void main() {
	Mat img(600, 650, CV_8UC3, Scalar(255, 255, 255));
	ellipse(img, Point(200, 200), Size(180, 80), 15, 0, 360, Scalar(0, 255, 255), 10, 8);   //����Բ����200,200��Ϊ�е㣬15��ת�Ƕȣ�0~360�ȣ�����180������80
	ellipse(img, RotatedRect(Point(350, 350), Size(150, 100), 40), Scalar(0, 255, 0), -1, 8);   //����Բ��40��ת�Ƕ�

	Point ppt[] = { Point(120,50),Point(180,50),Point(210,100),Point(180,150),Point(120,150),Point(90,100) };
	Point ppt2[] = { Point(80,400),Point(80,550),Point(250,500),Point(300,550) };//����㼯
	const Point* pts[] = { ppt };
	const Point* pts2[] = { ppt2 };
	int npt[] = { 6 };
	int npt2[] = { 4 };
	fillPoly(img, pts, npt, 1, Scalar(255, 255, 0), 8);   //���������
	polylines(img, pts2, npt2, 1, false, Scalar(0, 100, 200), 2, 8);   //������Σ�falseΪ���պϣ�trueΪ�պ�

	putText(img, "China", Point(400, 400), CV_FONT_BLACK, 2, Scalar(100, 100, 100), 5, 8);//д������

	imshow("drawing", img);
	waitKey(0);
}