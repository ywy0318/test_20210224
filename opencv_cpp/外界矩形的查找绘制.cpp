#include "opencv2/opencv.hpp"
using namespace cv;
void main()
{
	//外接矩形的查找绘制
	Mat srcImg = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\13.jpg");
	imshow("src", srcImg);
	Mat dstImg = srcImg.clone();  //原图备份
	cvtColor(srcImg, srcImg, CV_BGR2GRAY); //转为灰度图
	threshold(srcImg, srcImg, 100, 255, CV_THRESH_BINARY); //二值化

	vector<vector<Point>> contours;
	vector<Vec4i> hierarcy;
	findContours(srcImg, contours, hierarcy, CV_RETR_EXTERNAL, CHAIN_APPROX_NONE); //查找轮廓
	vector<Rect> boundRect(contours.size()); //定义外接矩形集合
											 //drawContours(dstImg, contours, -1, Scalar(0, 0, 255), 2, 8);  //绘制轮廓
	int x0 = 0, y0 = 0, w0 = 0, h0 = 0;
	for (int i = 0; i<contours.size(); i++)
	{
		boundRect[i] = boundingRect((Mat)contours[i]); //查找每个轮廓的外接矩形
		drawContours(dstImg, contours, i, Scalar(0, 0, 255), 2, 8);  //绘制轮廓
		x0 = boundRect[i].x;  //获得第i个外接矩形的左上角的x坐标
		y0 = boundRect[i].y; //获得第i个外接矩形的左上角的y坐标
		w0 = boundRect[i].width; //获得第i个外接矩形的宽度
		h0 = boundRect[i].height; //获得第i个外接矩形的高度
		rectangle(dstImg, Point(x0, y0), Point(x0 + w0, y0 + h0), Scalar(0, 255, 0), 2, 8); //绘制第i个外接矩形
	}
	imshow("boundRect", dstImg);
	waitKey(0);
}