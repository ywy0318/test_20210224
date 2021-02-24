#include "opencv2/opencv.hpp"
#include<iostream>
using namespace cv;
using namespace std;
void main()
{
	//分割硬币轮廓
	Mat srcImg = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\18.jpg");
	imshow("src", srcImg);
	Mat dstImg = srcImg.clone();  //原图备份
	cvtColor(srcImg, srcImg, CV_BGR2GRAY); //转为灰度图
	threshold(srcImg, srcImg, 100, 255, CV_THRESH_BINARY); //二值化
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1)); //获得结构元素
	dilate(srcImg, srcImg, element); //膨胀操作
	imshow("dilate", srcImg);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarcy;
	findContours(srcImg, contours, hierarcy, CV_RETR_EXTERNAL, CHAIN_APPROX_NONE); //查找轮廓
	vector<Rect> boundRect(contours.size()); //定义外接矩形集合
	int x0 = 0, y0 = 0, w0 = 0, h0 = 0, num = 0;
	for (int i = 0; i<contours.size(); i++)
	{
		boundRect[i] = boundingRect((Mat)contours[i]); //查找每个轮廓的外接矩形
		drawContours(dstImg, contours, i, Scalar(0, 0, 255), 2, 8);  //绘制轮廓
		x0 = boundRect[i].x;
		y0 = boundRect[i].y;
		w0 = boundRect[i].width;
		h0 = boundRect[i].height;
		if (w0>30 && h0>30)//筛选
		{
			rectangle(dstImg, Point(x0, y0), Point(x0 + w0, y0 + h0), Scalar(0, 255, 0), 2, 8); //绘制第i个外接矩形
			num++;
		}
	}
	cout << "硬币数量：" << num;
	imshow("boundRect", dstImg);
	waitKey(0);
}