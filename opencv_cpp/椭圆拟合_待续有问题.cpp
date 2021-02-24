#include "opencv2/opencv.hpp"
using namespace cv;

void main() {
	Mat srcImg = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\23.jpg");
	imshow("src", srcImg);
	Mat dstImg = srcImg.clone();
	GaussianBlur(srcImg, srcImg, Size(3, 3), 0, 0);
	cvtColor(srcImg, srcImg, CV_BGR2GRAY);
	Canny(srcImg, srcImg, 100, 200);
	imshow("Canny", srcImg);

	//≤È’“¬÷¿™
	vector<vector<Point>> contours;
	vector<Vec4i> hierarcy;
	findContours(srcImg, contours, hierarcy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);

	vector<RotatedRect> box(contours.size());
	Point2f rect[4];
	for (int i = 0; i<contours.size(); i++)
	{
		box[i] = fitEllipse(Mat(contours[i]));
		//ellipse(dstImg, box[i].center, Size(box[i].size.width/2, box[i].size.height/2), box[i].angle, 0, 360, Scalar(0, 255, 0), 2, 8);
		ellipse(dstImg, box[i], Scalar(0, 255, 0), 2, 8);
	}
	imshow("dst", dstImg);

	waitKey(0);
}