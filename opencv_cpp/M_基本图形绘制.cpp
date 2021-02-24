#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#define WINDOW_NAME_1 "绘制图1"
#define WINDOW_NAME_2 "绘制图2"
#define WINDOW_WIDTH 600//定义窗口大小的宏
using namespace std;
using namespace cv;

//自定义的绘制函数,实现了绘制不同角度,相同尺寸的椭圆
void DrawEllipse(Mat img, double angle)
{
	int thickness = 2;
	int lineType = 8;
	//DrawEllipse调用了OpenCV中的 ellipse函数,
	//椭圆画到图像img上,椭圆中心点Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2)
	//大小Size(WINDOW_WIDTH / 4, WINDOW_WIDTH / 16)
	//angle椭圆旋转角度为angle
	//拓展的弧度从0到360
	//图形颜色为Scalar(255, 129, 0)代表蓝色
	//thickness 线宽
	//lineType线型(8联通线型)
	ellipse(img, Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2), Size(WINDOW_WIDTH / 4, WINDOW_WIDTH / 16)
		, angle, 0, 360, Scalar(255, 129, 0), thickness, lineType);

}
//绘制圆形
void DrawFilledCircle(Mat img, Point center)
{
	int thickness = -1;
	int lineType = 8;
	//Scalar(0,0,255);//圆的颜色按照BGR
	//thickness=-1绘制的圆实心的
	circle(img,center,WINDOW_WIDTH/32,Scalar(0,0,255),thickness,lineType);
}
//fillPoly函数用于将多边形画到图像img上,多边形的顶点集为ppt,要绘制的多边形顶点数目为npt
//要绘制的多边形数量仅为1,多边形的颜色定义为白色Scalar(255,255,255);
void DrawPolygon(Mat img)
{
	int lineType = 8;
	//创建一些点
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
	//创建空白的Mat图像
	Mat atomImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH,CV_8UC3);
	Mat rookImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);

	//绘制化学中的原子示例图
	DrawEllipse(atomImage,90);
	DrawEllipse(atomImage, 0);
	DrawEllipse(atomImage, 45);
	DrawEllipse(atomImage, -45);
	//绘制圆心
	DrawFilledCircle(atomImage,Point(WINDOW_WIDTH/2, WINDOW_WIDTH/2));

	//绘制组合图
	//先绘制椭圆
	DrawPolygon(rookImage);
	//绘制矩形
	rectangle(rookImage, Point(0, 7 * WINDOW_WIDTH / 8), Point(WINDOW_WIDTH, WINDOW_WIDTH), Scalar(0, 255, 255), -1,8);

	//绘制一些线段
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
