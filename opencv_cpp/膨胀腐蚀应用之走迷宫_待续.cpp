#include "opencv2/opencv.hpp"
#include<iostream>
using namespace cv;
using namespace std;

//迷宫的图片
void main() {
	Mat img = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\7.jpg");
	int thres_min = 220;  //二值化最小阈值
	if (!img.empty()) {
		//二值化
		threshold(img, img, thres_min, 255, THRESH_BINARY);
		imshow("img_thres", img);
		//img备份
		Mat copy = img.clone();//拷贝原图，且不会随着原图改变
		cvtColor(copy, copy, CV_BGR2GRAY);//彩色图转灰度图
		threshold(copy, copy, thres_min, 255, THRESH_BINARY_INV);//反转：白色变黑色，黑色变白色
		imshow("copy", copy);
		//查找copy的轮廓
		vector<vector<Point>>contours;
		findContours(copy, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
		//将轮廓画在全黑图像上
		Mat draw;
		draw = Mat::zeros(img.size(), CV_32FC1);//定义一个img大小的全黑图像
		drawContours(draw, contours, 0, Scalar(255), -2);
		imshow("img2", draw);
		//进行膨胀腐蚀操作
		Mat dilated, eroded;
		Mat kernel = getStructuringElement(MORPH_RECT, Size(19, 19));//定义结构元素
		dilate(draw, dilated, kernel, Point(-1, -1), 2);//膨胀两次
		imshow("dilate", dilated);
		erode(dilated, eroded, kernel, Point(-1, -1), 2);
		imshow("erode", eroded);
		//膨胀腐蚀相减
		Mat diff;
		absdiff(dilated, eroded, diff);
		diff.convertTo(diff, CV_8UC1);//转换为单通道图（即灰度图）
		imshow("diff", diff);
		//在差异图diff中查找轮廓,然后在原图中绘制轮廓
		vector<vector<Point>>contours2;
		findContours(diff, contours2, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
		drawContours(img, contours2, 0, Scalar(0, 255, 0), -1);//-1表示绘制轮廓内部，正数表示轮廓线条粗细
		imshow("result", img);
	}
	waitKey(0);
	destroyAllWindows();
}