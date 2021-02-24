#include "opencv2/opencv.hpp"
#include<iostream>
using namespace std;
using namespace cv;

void main()
{
	Mat srcImg = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\24.jpg");
	imshow("src", srcImg);
	Mat dstImg = srcImg.clone();
	GaussianBlur(srcImg, srcImg, Size(3, 3), 0, 0);
	cvtColor(srcImg, srcImg, CV_BGR2GRAY);
	Canny(srcImg, srcImg, 100, 200);//因为原图比较复杂，所以需要将canny的值调大，去除不想要的成分
									//threshold(srcImg, srcImg, 100, 255, CV_THRESH_BINARY_INV); //二值化也可以实现canny效果,不过在本例中杂絮较多
	imshow("canny", srcImg);
	Mat element = getStructuringElement(MORPH_RECT, Size(11, 11), Point(-1, -1)); //定义结构元素
	dilate(srcImg, srcImg, element); //膨胀
	imshow("dilate", srcImg);
	erode(srcImg, srcImg, element);
	imshow("erode", srcImg);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarcy;
	findContours(srcImg, contours, hierarcy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);
	vector<Rect> boundRect(contours.size());
	vector<RotatedRect> box(contours.size());
	Point2f rect[4];
	for (int i = 0; i<contours.size(); i++)
	{
		box[i] = minAreaRect(Mat(contours[i]));
		boundRect[i] = boundingRect(Mat(contours[i]));

		if (box[i].size.width < 100 || box[i].size.height<100)//筛选
			continue;
		rectangle(dstImg, Point(boundRect[i].x, boundRect[i].y), Point(boundRect[i].x + boundRect[i].width, boundRect[i].y + boundRect[i].height), Scalar(0, 255, 0), 2, 8);
		circle(dstImg, Point(box[i].center.x, box[i].center.y), 5, Scalar(0, 255, 0), -1, 8);
		box[i].points(rect);
		for (int j = 0; j<4; j++)
		{
			line(dstImg, rect[j], rect[(j + 1) % 4], Scalar(0, 0, 255), 2, 8);
		}

		float angle;
		cout << "angle=" << box[i].angle << endl;
		angle = box[i].angle;
		char width[20], height[20];
		sprintf(width, "width=%0.2f", box[i].size.width);
		sprintf(height, "height=%0.2f", box[i].size.height);
		putText(dstImg, width, Point(195, 260), CV_FONT_HERSHEY_COMPLEX_SMALL, 0.85, Scalar(0, 255, 0));
		putText(dstImg, height, Point(190, 285), CV_FONT_HERSHEY_COMPLEX_SMALL, 0.85, Scalar(0, 255, 0));
		imshow("temp", dstImg);

		//利用仿射变换进行旋转        另一种方法，透视变换
		if (0< abs(angle) && abs(angle) <= 45)
			angle = angle;//负数，顺时针旋转
		else if (45< abs(angle) && abs(angle)<90)
			angle = 90 - abs(angle);//正数，逆时针旋转
		Point2f center = box[i].center;  //定义旋转中心坐标
		double angle0 = angle;
		double scale = 1;
		Mat roateM = getRotationMatrix2D(center, angle0, scale);  //获得旋转矩阵,顺时针为负，逆时针为正
		warpAffine(dstImg, dstImg, roateM, dstImg.size()); //仿射变换

														   //保存二维码
		int x0 = 0, y0 = 0, w0 = 0, h0 = 0;
		x0 = boundRect[i].x;
		y0 = boundRect[i].y;
		w0 = boundRect[i].width;
		h0 = boundRect[i].height;
		Mat ROI = dstImg(Rect(x0, y0, w0, h0));
		imwrite("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\998.jpg", ROI);
	}
	imshow("dst", dstImg);
	waitKey(0);
}