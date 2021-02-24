/*
8.2寻找物体的凸包
凸包(Convex Hull)是一个计算几何(图形学)概念,给定二维平面
上的点集,凸包就是将最外层的点连接起来构成的凸多边形,它是
能包含点集中所有点的;理解物体形状或轮廓的一种比较有用的方法
是计算一个物体的凸包,然后计算其凸缺陷(convexity defeects);
很多复杂物体的特性能够很好的被这种缺陷表现出来;

寻找凸包:convexHull()函数用于寻找图像点击中的凸包,
C++:void convexHull(InputArray points,OutputArray hull,
bool clockwise=false,bool returnPoints=true)
第一个参数:InputArray类型的points,输入的二维点集,
可以填Mat类型或者std:vector
第二个参数:OutputArray类型的hull,输出参数,函数调用后
找到的凸包;
第三个参数:bool类型的clockwise,操作方向标识符,当此标识符
为真时,输出的凸包为顺时针方向,否则就为逆时针方向,并且
假定坐标系的x轴指定右,y轴指向上方;
第四个参数:bool类型的returnPoints,操作标识符,默认为true;
当标识符为真时,函数返回各凸包的各个点;否则,它返回凸包
各点的指数,当输出数组是std::vector时,此标志被忽略;
*/

#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;

int main()
{
	//初始化变量和随机值
	Mat image(1000,1000, CV_8UC3);
	RNG& rng = theRNG();

	while (true)
	{
		//
		char key;
		//int count = (unsigned)rng % 100 + 3;//随机生成点的数量
		int count = 500;
		vector<Point> points;
		for (size_t i = 0; i < count; i++)
		{
			Point point_1;
			point_1.x = rng.uniform(image.cols/4,image.cols*3/4);
			point_1.y = rng.uniform(image.rows/4,image.rows*3/4);
			points.push_back(point_1);
		}
		//检测凸包
		vector<int> hull;
		convexHull(Mat(points), hull, true);
		//绘制出随机颜色的点
		image = Scalar::all(0);
		for (size_t i = 0; i < count; i++)
		{
			circle(image, points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), FILLED, LINE_AA);

		}
		//准备参数
		int hullcount = (int)hull.size();//凸包的边数
		Point point_0 = points[hull[hullcount - 1]];//连接凸包边的坐标点

		//绘制凸包的边
		for (size_t i = 0; i < hullcount; i++)
		{
			Point point_2 = points[hull[i]];
			line(image,point_0, point_2,Scalar(255,255,255),2,LINE_AA);
			point_0 = point_2;

		}
		imshow("凸包检测示例",image);
		key = (char)waitKey();
		if ((key == 27) || (key == 'q') || (key == 'Q'))
		{
			break;
		}
		return 0;
	}

}