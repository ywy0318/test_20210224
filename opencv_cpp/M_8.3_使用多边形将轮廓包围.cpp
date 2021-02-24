/*
8.3使用多边形将轮廓包围

返回外部举行边界:boundingRect()函数 
此函数计算并返回指定点集最外面(up-right)的矩形边界
C++:Rect boundingRect(InputArray points);
其唯一的一个参数为输入的二维点集,可以是std:vector或Mat类型

寻找最小包围矩形:minAreaRect()函数
此函数用于对给定的2D点集,寻找可旋转的最小面积的包围矩形
C++:RotatedRect minAreaRect(Inputarray points)
其唯一的一个参数为输入的二维点集,可以是std::vector<>或Mat类型

寻找最小包围圆形:minEnclosingCircle()函数
minEnclosingCircle函数的功能是利用一种迭代算法,其给定的2D点集,
去寻找面积最小的可包围他们的圆形;
C++:void minEnclosingCircle(InputArray points,Point2f& center,float& redius)
第二个参数:Point2f&类型的center,圆的输出圆心
第三个参数:float&类型的radius,圆的输出半径;

用椭圆拟合二维点集:fitEllipse()函数
用椭圆拟合二维点集
C++:RotatedRect fitEllipse(InputArray points)


逼近多边形曲线:approxPolyDP()函数
approxPolyDP()函数的作用是用指定精度逼近多边形曲线;
C++:void approxPolyDp(InputArray curve,OutputArray approxCurve,double epsilon,
bool closed)

第一个参数:输入二维点集
第二个参数:多边形逼近的结果
第三个参数:double类型的epsilon,逼近的精度,为原始曲线和即近似曲线
间的最大值;
第四个参数:bool类型的closed,如果为真,则近似的曲线为封闭曲线,
(第一个顶点和最后一个顶点相连),否则,近似的曲线曲线不封闭;

*/


#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;
int g_nThresh = 50;
int g_nThresh_max = 255;
RNG g_rng(12345);//随机数生成器

void on_minAreaRect()
{
	Mat image(1000, 1000, CV_8UC3);
	RNG &rng = theRNG();
	while (true)
	{
		int count = rng.uniform(3,106);
		//int count = 3;
		vector<Point> points;
		for (size_t i = 0; i < count; i++)
		{
			Point point_1;
			point_1.x = rng.uniform(image.cols / 4, image.cols * 3 / 4);
			point_1.y = rng.uniform(image.rows / 4, image.rows * 3 / 4);
			points.push_back(point_1);
		}
		//给定的2D点集,寻找最小面积的包围矩形
		RotatedRect box = minAreaRect(Mat(points));
		Point2f vertex[4];
		box.points(vertex);
		//绘制出随机颜色的点
		image = Scalar::all(0);
		for (size_t i = 0; i < count; i++)
		{
			circle(image,points[i],3,Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255)),FILLED,LINE_AA);
		}
		//绘制出最小面积的包围矩形
		for (size_t i = 0; i < count; i++)
		{
			line(image,vertex[i],vertex[(i+1)%4],Scalar(100,200,211),2,LINE_AA);
		}
		imshow("minAreaRect",image);
		char key = (char)waitKey();
		if ((key == 27) || (key == 'q') || (key == 'Q'))
		{
			break;
		}
	}
	//return 0;
}

void on_minEnclosingCircle()
{
	Mat image(1000, 1000, CV_8UC3);
	RNG &rng = theRNG();
	while (true)
	{
		//int count = rng.uniform(3, 1036);
		int count = 5;
		vector<Point> points;
		for (size_t i = 0; i < count; i++)
		{
			Point point_1;
			point_1.x = rng.uniform(image.cols / 4, image.cols * 3 / 4);
			point_1.y = rng.uniform(image.rows / 4, image.rows * 3 / 4);
			points.push_back(point_1);
		}
		////给定的2D点集,寻找最小面积的包围矩形
		//RotatedRect box = minAreaRect(Mat(points));
		//Point2f vertex[4];
		//box.points(vertex);
		//对于给定的2D点集,寻找最小面积的包围图
		Point2f center;
		float radius = 0;
		minEnclosingCircle(Mat(points),center,radius);
		//绘制出随机颜色的点
		image = Scalar::all(0);
		for (size_t i = 0; i < count; i++)
		{
			circle(image, points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), FILLED, LINE_AA);
		}
		//绘制出最小面积的包围矩形
	/*	for (size_t i = 0; i < count; i++)
		{
			line(image, vertex[i], vertex[(i + 1) % 4], Scalar(100, 200, 211), 2, LINE_AA);
		}*/

		circle(image,center,cvRound(radius),Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255)), 2, LINE_AA);

		imshow("minAreaRect", image);
		char key = (char)waitKey();
		if ((key == 27) || (key == 'q') || (key == 'Q'))
		{
			break;
		}
	}
}

void on_ContoursChange(int, void*)
{
	Mat threshold_output;
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	//使用Threshold检测边缘
	threshold(gray_img, threshold_output, g_nThresh, 255, THRESH_BINARY);
	findContours(threshold_output,contours,hierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point(0,0));

	//多边形逼近轮廓,获取矩形和圆形边界框
	vector<vector<Point>> contourse_poly(contours.size());
	vector<Rect> boundRect(contours.size());
	vector<Point2f>center(contours.size());
	vector<float>radius(contours.size());


	//一个循环，遍历所有部分,
	for (size_t i = 0; i < contours.size(); i++)
	{
		//用指定精度逼近多边形曲线
		approxPolyDP(Mat(contours[i]), contourse_poly[i],3,true);
		//计算点集的最外面(up-right)矩形边界
		boundRect[i] = boundingRect(Mat(contourse_poly[i]));
		//对给定的2D点集,寻找最小面积的包围圆形
		minEnclosingCircle(contourse_poly[i],center[i],radius[i]);
	}
	//绘制多边形轮廓+包围的矩形框+圆形框
	Mat draw_img = Mat::zeros(threshold_output.size(),CV_8UC3);
	for (size_t i = 0; i < contours.size(); i++)
	{
		//随机设置颜色
		Scalar color = Scalar(g_rng.uniform(0,255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		//绘制轮廓
		drawContours(draw_img,contourse_poly,i,color,1,8,vector<Vec4i>(),0,Point());
		//绘制矩形
		rectangle(draw_img,boundRect[i].tl(), boundRect[i].br(),color,2,8,0);
		//绘制圆形
		circle(draw_img,center[i],(int)radius[i],color,2,8,0);
	}
	namedWindow("draw_img",CV_WINDOW_AUTOSIZE);
	imshow("draw_img", draw_img);
}
int on_contoursChange_test()
{
	system("color 1A");
	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	cvtColor(src_img,gray_img,COLOR_BGR2GRAY);
	blur(gray_img,gray_img,Size(3,3));
	namedWindow("src_img",CV_WINDOW_AUTOSIZE);
	imshow("src_img", src_img);

	createTrackbar("阈值:","src_img",&g_nThresh,g_nThresh_max,on_ContoursChange);
	on_ContoursChange(0,0);
	waitKey(0);
	return 0;
}

int main()
{
	int flag = 0;
	if (flag)
	{
		//on_minAreaRect();
		//on_minEnclosingCircle();
	}
	else
	{
		on_contoursChange_test();
	}
	
	system("pause");
	return 0;
}
