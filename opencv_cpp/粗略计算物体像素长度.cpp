#include "opencv2/opencv.hpp"
#include<iostream>
using namespace std;
using namespace cv;

void main()
{
	Mat srcImg = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\22.jpg");
	imshow("src", srcImg);
	Mat dstImg = srcImg.clone();
	medianBlur(srcImg, srcImg, 5);
	GaussianBlur(srcImg, srcImg, Size(3, 3), 0, 0);
	cvtColor(srcImg, srcImg, CV_BGR2GRAY);
	threshold(srcImg, srcImg, 100, 255, CV_THRESH_BINARY_INV); //INV是因为背景白色，物体黑色，需要反转一下
	imshow("threshold", srcImg);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarcy;

	findContours(srcImg, contours, hierarcy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	cout << "num=" << contours.size() << endl;
	vector<Rect> boundRect(contours.size());
	vector<RotatedRect> box(contours.size());
	Point2f rect[4];
	for (int i = 0; i<contours.size(); i++)
	{
		box[i] = minAreaRect(Mat(contours[i]));
		boundRect[i] = boundingRect(Mat(contours[i]));
		cout << box[i].angle << endl;
		cout << box[i].center << endl;
		cout << box[i].size.width << endl;
		cout << box[i].size.height << endl;
		circle(dstImg, Point(box[i].center.x, box[i].center.y), 5, Scalar(0, 255, 0), -1, 8);

		//绘制外接矩形和    最小外接矩形（for循环）
		rectangle(dstImg, Point(boundRect[i].x, boundRect[i].y), Point(boundRect[i].x + boundRect[i].width, boundRect[i].y + boundRect[i].height), Scalar(0, 255, 0), 2, 8);
		box[i].points(rect);//把最小外接矩形四个端点复制给rect数组
		for (int j = 0; j<4; j++)
		{
			line(dstImg, rect[j], rect[(j + 1) % 4], Scalar(0, 0, 255), 2, 8);
		}

		char width[20], height[20];
		sprintf(width, "width=%0.2f", box[i].size.width);
		sprintf(height, "height=%0.2f", box[i].size.height);
		putText(dstImg, width, Point(235, 260), CV_FONT_HERSHEY_COMPLEX_SMALL, 0.85, Scalar(0, 255, 0));
		putText(dstImg, height, Point(235, 285), CV_FONT_HERSHEY_COMPLEX_SMALL, 0.85, Scalar(0, 255, 0));

	}
	imshow("dst", dstImg);
	waitKey(0);
}