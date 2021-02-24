#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;

//定义一个矢量结构g_lines用于存放得到的线段矢量集合
vector<Vec4i> g_lines;

//回调函数
static void on_HoughLines(int, void*);

//变量接收的Trackhold位置参数
int g_nthreshold = 100;

int main()
{
	system("color 3F");
	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	namedWindow("src_img",CV_WINDOW_AUTOSIZE);
	imshow("src_img", src_img);

	namedWindow("dst_img",CV_WINDOW_AUTOSIZE);
	createTrackbar("value","dst_img",&g_nthreshold,200,on_HoughLines);

	//进行边缘检测和转换为灰度图
	Canny(src_img, temp_img, 50, 200, 3);//进行一次canny边缘检测
	cvtColor(temp_img,dst_img,COLOR_GRAY2BGR);
	//调用一次回调函数,调用一次HoughLinesP函数
	on_HoughLines(g_nthreshold,0);
	HoughLinesP(temp_img,g_lines,1,CV_PI/180,80,50,10);
	imshow("dst_img", dst_img);
	waitKey(0);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
//顶帽运算/黑帽运算
static void on_HoughLines(int, void*)
{
	Mat dst_img_temp = dst_img.clone();
	Mat temp_img_temp = temp_img.clone();
	//调用HoughLinesP函数
	vector<Vec4i> mylines;
	HoughLinesP(dst_img_temp, mylines, 1, CV_PI / 180, g_nthreshold + 1, 50, 10);

	//循环遍历绘制每一条线段
	for (size_t i = 0; i < mylines.size(); i++)
	{
		Vec4i l = mylines[i];
		line(dst_img_temp, Point(l[0], l[1]), Point(l[2], l[3]),
			Scalar(23, 180, 55), 1, LINE_AA);

	}
	imshow("dst_img",dst_img_temp);
}