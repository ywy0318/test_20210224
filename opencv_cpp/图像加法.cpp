#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

void main() {
	Mat img1 = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	Mat img2 = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	Mat dst;//存储结果
	imshow("img1", img1);
	imshow("img2", img2);
	cout << "img1  " << int(img1.at<Vec3b>(100, 100)[0]) << endl;//img1在坐标（100,100）的蓝色通道的值，强制转成int
	cout << "img2  " << int(img2.at<Vec3b>(100, 100)[0]) << endl;

	dst = img1 + img2;//这两个加法效果相同
					  //add(img1,img2,dst);//注意：这两个加法要求被加的图片尺寸必须一致
					  //addWeighted(img1,0.5,img2,0.5,0,dst);//按权重相加，下一行dst输出参数为正常参数的一半
	cout << "dst  " << int(dst.at<Vec3b>(100, 100)[0]) << endl;
	imshow("dst", dst);
	waitKey(0);
}