#include "opencv2/opencv.hpp"
using namespace cv;

void main()
{
	Mat src, dst, abs_dst;
	src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\7.jpg", 0);
	imshow("src", src);

	Laplacian(src, dst, CV_16S, 3);
	convertScaleAbs(dst, abs_dst);
	imshow("Laplacian", abs_dst);

	waitKey(0);
	destroyAllWindows();
}