#include "opencv2/opencv.hpp"
using namespace cv;

void main()
{
	//HoughLinesP()用法
	Mat src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\8.jpg");
	Mat dstImg = src.clone();
	imshow("src", src);

	cvtColor(src, src, CV_BGR2GRAY);
	Canny(src, src, 50, 200);
	vector<Vec4i> lines;  //定义矢量结构lines用于存放得到的线段矢量集合
	HoughLinesP(src, lines, 1, CV_PI / 180, 150, 50, 10);
	//依次在图中绘制出每条线段
	for (size_t i = 0; i<lines.size(); i++)
	{
		Vec4i p = lines[i];
		line(dstImg, Point(p[0], p[1]), Point(p[2], p[3]), Scalar(0, 255, 0), 2, 8); //20
	}
	imshow("dst", dstImg);
	waitKey(0);
	destroyAllWindows();
}