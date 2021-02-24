#include "opencv2/opencv.hpp"
using namespace cv;

void main()
{
	Mat src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\10.jpg");
	Mat dst = src.clone();
	imshow("src", src);

	cvtColor(src, src, CV_BGR2GRAY);
	GaussianBlur(src, src, Size(9, 9), 2);

	vector<Vec3f> circles;
	HoughCircles(src, circles, CV_HOUGH_GRADIENT, 1.5, 10, 200, 100);
	for (size_t i = 0; i<circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		circle(dst, center, 3, Scalar(0, 0, 255), -1, 8, 0);//设置为-1时，画实心圆
		circle(dst, center, radius, Scalar(0, 255, 0), 3, 8, 0);//画空心圆
	}
	imshow("dst", dst);
	waitKey(0);
}