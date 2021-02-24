#include "opencv2/opencv.hpp"
using namespace cv;

void main()
{
	//轮廓最小外接矩形的绘制
	Mat srcImg = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\20.jpg");
	Mat dstImg = srcImg.clone();
	cvtColor(srcImg, srcImg, CV_BGR2GRAY);
	threshold(srcImg, srcImg, 100, 255, CV_THRESH_BINARY); //二值化
	imshow("threshold", srcImg);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarcy;
	findContours(srcImg, contours, hierarcy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	vector<Rect> boundRect(contours.size());  //定义外接矩形集合
	vector<RotatedRect> box(contours.size()); //定义最小外接矩形集合
	Point2f rect[4];
	for (int i = 0; i<contours.size(); i++)
	{
		box[i] = minAreaRect(Mat(contours[i]));  //计算每个轮廓最小外接矩形
		boundRect[i] = boundingRect(Mat(contours[i]));
		circle(dstImg, Point(box[i].center.x, box[i].center.y), 5, Scalar(0, 255, 0), -1, 8);  //绘制最小外接矩形的中心点
		box[i].points(rect);  //把最小外接矩形四个端点复制给rect数组
		rectangle(dstImg, Point(boundRect[i].x, boundRect[i].y), Point(boundRect[i].x + boundRect[i].width, boundRect[i].y + boundRect[i].height), Scalar(0, 255, 0), 2, 8);
		for (int j = 0; j<4; j++)
		{
			line(dstImg, rect[j], rect[(j + 1) % 4], Scalar(0, 0, 255), 2, 8);  //绘制最小外接矩形每条边
		}
	}
	imshow("dst", dstImg);
	waitKey(0);
}