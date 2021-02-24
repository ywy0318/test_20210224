//Mat img;//创建无初始化矩阵
//Mat img1(200, 100, CV_8UC1);//200行，100列（长200，宽100）
//Mat img2(Size(200, 100), CV_8UC3, Scalar(0, 255, 0));//长100，宽200
//Mat img3(200, 100, CV_8UC3, Scalar(0, 255, 0));//创建200行，100列的8位三通道矩阵
//Mat img4(200, 100, CV_8UC1, Scalar(255));//创建单通道矩阵

#include <opencv2/opencv.hpp>
using namespace cv;

void main() {
	Mat img1 = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	//Mat img1 = imread("E://1.jpg");
	//"E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.mp4"
	Mat img2(img1);
	Mat img3 = img1;
	Mat img4 = img1.clone();
	Mat img5;
	img1.copyTo(img5);

	cvtColor(img1, img1, CV_BGR2HSV);//BGR图转为HSV图
	imshow("img1", img1);
	imshow("img2", img2);
	imshow("img3", img3);//image1/2/3跟随原图变化
	imshow("img4", img4);
	imshow("img5", img5);//image4/5不会跟随原图变化
	waitKey(0);
}