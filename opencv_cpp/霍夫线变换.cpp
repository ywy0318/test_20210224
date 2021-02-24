#include "opencv2/opencv.hpp"
using namespace cv;

void main()
{
	Mat src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\8.jpg");
	Mat dst;
	imshow("src", src);

	Canny(src, src, 50, 200);
	imshow("Canny", src);
	//cvtColor(src, dst, CV_BGR2GRAY);//彩色图转灰度图：该语句不能放在canny边缘检测后（canny检测后，图像变为了灰度图）
	cvtColor(src, dst, CV_GRAY2BGR);//灰度图转彩色图

									//进行霍夫线变换
	vector<Vec2f> lines;  //定义矢量结构lines用于存放得到的线段矢量集合
	HoughLines(src, lines, 1, CV_PI / 180, 150);//超过150的线段才被检测到

												//依次在图中绘制出每条线段
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000 * (-b));//cvRound(double value) 函数：对一个double型数字四舍五入，返回一个整数
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(dst, pt1, pt2, Scalar(55, 100, 195), 2, 8);
	}

	imshow("dst", dst);
	waitKey(0);
	destroyAllWindows();
}