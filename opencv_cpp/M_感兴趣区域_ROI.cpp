/*
ROI,region of interest
定义ROI区域有两种方法:
第一种是使用表示矩形区域的Rect;它指定矩形的左上角坐标(构造函数的前两个参数)和矩形的长宽(构造函数的后两个区域)

Mat imageROI=image(Rect(500,250,logo.cols,logo.rows));

另一种定义ROI的方式是指定感兴趣行或者列的范围(Range);
Range是指从起始索引到终止索引(不包括终止索引)的一连段连续序列;
cRange可以用来定义Range;
如果使用Range来定义ROI
//方法2

Mat imageROI=image(Range(250,250+logoImage.rows),Range(200,200+logoImage.cols))

*/


#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
int main()
{
	string imgpath4 = "1.jpg";
	Mat img = imread(imgpath4, 1);//读入图片数据
	if (img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	string imgpath2 = "2.jpg";
	Mat img_2 = imread(imgpath2, 1);//读入图片数据
	if (img_2.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}

	//定义一个Mat类型并给其设定ROI区域
	Mat image_ROI = img(Rect(200,250,img_2.cols,img_2.rows));
	//加载掩码(必须是灰度图)
	Mat mask = imread(imgpath2,0);
	
	//将掩码复制到ROI
	img_2.copyTo(image_ROI, mask);
	//显示结果
	namedWindow("<1>利用ROI实现图像叠加实力窗口");
	imshow("<1>利用ROI实现图像叠加实力窗口",img);
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
