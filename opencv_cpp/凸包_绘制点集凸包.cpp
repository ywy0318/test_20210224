#include<opencv2/opencv.hpp>
using namespace cv;

void main()
{
	//---绘制点集的凸包
	Mat img(400, 400, CV_8UC3, Scalar::all(0));  //定义绘制图像
	RNG rng;  //定义随机数对象
	while (1)
	{
		char key;
		int count = (unsigned int)rng % 100;  //定义点的个数  
		vector<Point> points;  //定义点集
		for (int i = 0; i<count; i++)
		{
			Point pt;
			pt.x = rng.uniform(img.cols / 4, img.cols * 3 / 4);  //设定点的x范围
			pt.y = rng.uniform(img.rows / 4, img.rows * 3 / 4);  //设定点的y范围
			points.push_back(pt);
		}

		//检测凸包
		vector<int> hull;
		convexHull(Mat(points), hull, true);

		img = Scalar::all(0);
		for (int i = 0; i < count; i++)
			circle(img, points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), CV_FILLED, CV_AA);

		//准备参数
		int hullcount = (int)hull.size(); //凸包的边数
		Point point0 = points[hull[hullcount - 1]]; //连接凸包边的坐标点

													//绘制凸包的边
		for (int i = 0; i < hullcount; i++)
		{
			Point point = points[hull[i]];
			circle(img, point, 8, Scalar(0, 255, 0), 2, 8);
			line(img, point0, point, Scalar(255, 255, 255), 2, CV_AA);
			point0 = point;
		}

		//显示效果图
		imshow("img", img);

		//按下ESC,Q,或者q，程序退出
		key = (char)waitKey();
		if (key == 27 || key == 'q' || key == 'Q')
			break;
	}
	
}