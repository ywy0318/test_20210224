#include "opencv2/opencv.hpp"
using namespace cv;

void main() {
	Mat srcImg = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\25.jpg");
	imshow("src", srcImg);
	Mat dstImg = srcImg.clone();  //原图备份
	Mat tempImg = srcImg.clone();  //原图备份
	Mat tempImg2(srcImg.size(), CV_8UC3, Scalar::all(0));  //定义全黑的和原图一样大小的图像
	Mat draw(srcImg.size(), CV_8UC3, Scalar::all(0));
	Mat tempImg3(srcImg.size(), CV_8UC3, Scalar::all(0));

	GaussianBlur(srcImg, srcImg, Size(3, 3), 0, 0);
	cvtColor(srcImg, srcImg, CV_BGR2GRAY);
	threshold(srcImg, srcImg, 100, 255, CV_THRESH_BINARY); //二值化
	imshow("threshold", srcImg);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarcy;
	findContours(srcImg, contours, hierarcy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);
	while (1)
	{
		for (int i = 0; i<contours.size(); i++)
		{
			tempImg2.copyTo(draw);  //每次进入将draw清空为全黑
			tempImg2.copyTo(tempImg3);
			//drawContours(dstImg, contours, i, Scalar(0, 255, 0), 5, 8);    
			drawContours(draw, contours, i, Scalar(255, 255, 255), -1, 8);
			Mat mask;  //定义掩码
			cvtColor(draw, mask, CV_BGR2GRAY);
			tempImg.copyTo(tempImg3, mask);  //将tempImg 复制到tempImg3(只有mask部分被复制)
			imshow("draw", draw);
			imshow("result", tempImg3);
			char key = waitKey();
			if (key == 27)  //按下Esc键跳出for循环
				break;
		}
		break;
	}
}