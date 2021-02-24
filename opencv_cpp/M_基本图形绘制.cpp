#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#define WINDOW_NAME_1 "����ͼ1"
#define WINDOW_NAME_2 "����ͼ2"
#define WINDOW_WIDTH 600//���崰�ڴ�С�ĺ�
using namespace std;
using namespace cv;

//�Զ���Ļ��ƺ���,ʵ���˻��Ʋ�ͬ�Ƕ�,��ͬ�ߴ����Բ
void DrawEllipse(Mat img, double angle)
{
	int thickness = 2;
	int lineType = 8;
	//DrawEllipse������OpenCV�е� ellipse����,
	//��Բ����ͼ��img��,��Բ���ĵ�Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2)
	//��СSize(WINDOW_WIDTH / 4, WINDOW_WIDTH / 16)
	//angle��Բ��ת�Ƕ�Ϊangle
	//��չ�Ļ��ȴ�0��360
	//ͼ����ɫΪScalar(255, 129, 0)������ɫ
	//thickness �߿�
	//lineType����(8��ͨ����)
	ellipse(img, Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2), Size(WINDOW_WIDTH / 4, WINDOW_WIDTH / 16)
		, angle, 0, 360, Scalar(255, 129, 0), thickness, lineType);

}
//����Բ��
void DrawFilledCircle(Mat img, Point center)
{
	int thickness = -1;
	int lineType = 8;
	//Scalar(0,0,255);//Բ����ɫ����BGR
	//thickness=-1���Ƶ�Բʵ�ĵ�
	circle(img,center,WINDOW_WIDTH/32,Scalar(0,0,255),thickness,lineType);
}
//fillPoly�������ڽ�����λ���ͼ��img��,����εĶ��㼯Ϊppt,Ҫ���ƵĶ���ζ�����ĿΪnpt
//Ҫ���ƵĶ����������Ϊ1,����ε���ɫ����Ϊ��ɫScalar(255,255,255);
void DrawPolygon(Mat img)
{
	int lineType = 8;
	//����һЩ��
	Point rookPoints[1][20];
	rookPoints[0][0] = Point(WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8);
	rookPoints[0][1] = Point(3*WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8);
	rookPoints[0][2] = Point(3 * WINDOW_WIDTH / 4, 13 * WINDOW_WIDTH / 16);
	rookPoints[0][3] = Point(11 * WINDOW_WIDTH / 16, 13 * WINDOW_WIDTH / 16);
	rookPoints[0][4] = Point(19 * WINDOW_WIDTH / 32, 3 * WINDOW_WIDTH / 8);
	rookPoints[0][5] = Point(WINDOW_WIDTH / 4, 3 * WINDOW_WIDTH / 8);
	rookPoints[0][6] = Point(3*WINDOW_WIDTH / 4,  WINDOW_WIDTH / 8);
	rookPoints[0][7] = Point(26 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rookPoints[0][8] = Point(26 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
	rookPoints[0][9] = Point(22 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
	rookPoints[0][10] = Point(22 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rookPoints[0][11] = Point(18 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rookPoints[0][12] = Point(18 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);

	rookPoints[0][13] = Point(14 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
	rookPoints[0][14] = Point(14 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rookPoints[0][15] = Point(WINDOW_WIDTH / 4, WINDOW_WIDTH / 8);

	rookPoints[0][16] = Point(WINDOW_WIDTH / 4, 3*WINDOW_WIDTH / 8);
	rookPoints[0][17] = Point(13*WINDOW_WIDTH / 32, 3 * WINDOW_WIDTH / 8);
	rookPoints[0][18] = Point(5 * WINDOW_WIDTH / 16, 13 * WINDOW_WIDTH / 16);
	rookPoints[0][19] = Point(WINDOW_WIDTH / 4, 13 * WINDOW_WIDTH / 16);

	const Point*ppt[1] = { rookPoints[0] };
	int npt[] = { 20 };

	fillPoly(img,ppt,npt,1,Scalar(255,255,255),lineType);
}

void DrawLine(Mat img,Point start,Point end)
{
	int thickness = 2;
	int lineType = 8;
	line(img, start, end, Scalar(0, 0, 0), thickness, lineType);
}



int main()
{
	//�����հ׵�Matͼ��
	Mat atomImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH,CV_8UC3);
	Mat rookImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);

	//���ƻ�ѧ�е�ԭ��ʾ��ͼ
	DrawEllipse(atomImage,90);
	DrawEllipse(atomImage, 0);
	DrawEllipse(atomImage, 45);
	DrawEllipse(atomImage, -45);
	//����Բ��
	DrawFilledCircle(atomImage,Point(WINDOW_WIDTH/2, WINDOW_WIDTH/2));

	//�������ͼ
	//�Ȼ�����Բ
	DrawPolygon(rookImage);
	//���ƾ���
	rectangle(rookImage, Point(0, 7 * WINDOW_WIDTH / 8), Point(WINDOW_WIDTH, WINDOW_WIDTH), Scalar(0, 255, 255), -1,8);

	//����һЩ�߶�
	DrawLine(rookImage,Point(0,15* WINDOW_WIDTH/16),Point(WINDOW_WIDTH,15* WINDOW_WIDTH/16));
	DrawLine(rookImage, Point(WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8), Point(WINDOW_WIDTH/4, 16 * WINDOW_WIDTH / 16));
	DrawLine(rookImage, Point(WINDOW_WIDTH / 2, 7 * WINDOW_WIDTH /8), Point(WINDOW_WIDTH/2, 16 * WINDOW_WIDTH / 16));
	DrawLine(rookImage, Point(3 * WINDOW_WIDTH /4, 14 * WINDOW_WIDTH / 16), Point(3*WINDOW_WIDTH/4, 16 * WINDOW_WIDTH / 16));

	imshow(WINDOW_NAME_1, atomImage);
	cvMoveWindow(WINDOW_NAME_1,0,200);

	imshow(WINDOW_NAME_2, rookImage);
	cvMoveWindow(WINDOW_NAME_2, WINDOW_WIDTH, 200);

	cout << CV_MAJOR_VERSION << endl;
	waitKey(0);
	system("pause");
	return 0;
}
