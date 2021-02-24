#include <opencv2/opencv.hpp>
using namespace cv;
//画线、画圆、画矩形
void main() {
	Mat img(500, 400, CV_8UC3, Scalar(255, 255, 255));//创建一个500行400列，3通道（即彩色图）的白色图
	line(img, Point(10, 10), Point(100, 250), Scalar(0, 255, 255), 20, 8);//在img图中画一条黄线，线宽为20，线型为8联通（一般都设置为8）
	circle(img, Point(200, 100), 50, Scalar(0, 255, 255), 15, 8);   //以（200,100）为圆心，半径为50，线宽为15画空心圆
	circle(img, Point(200, 250), 50, Scalar(0, 255, 255), -1, 8);   //设置为-1时，画实心圆
	rectangle(img, Point(10, 100), Point(200, 200), Scalar(0, 0, 255), 1, 8);   //传入坐上、右下角坐标，画空心矩形
	rectangle(img, Rect(200, 300, 100, 50), Scalar(0, 255, 0), -1, 8); //传矩形数据（左上角坐标（200,300）和宽100，高50），画实心绿色矩形

	imshow("drawing", img);
	waitKey(0);
}