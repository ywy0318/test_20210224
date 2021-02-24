#include<iostream>
#include<opencv2\opencv.hpp>
#include "highgui.h"
#include"cvaux.h"
#include"cxcore.h"
#include"opencv2/imgproc.hpp"
#include<string>
using namespace std;
using namespace cv;
/*
使用resize函数改变图像的尺寸

函数原型：

void resize(InputArray src, OutputArray dst, Size dsize, double fx=0, double fy=0, int interpolation=INTER_LINEAR )

src源图像 dst目标图像 dsize目标图像的大小 各个参数的意义比较直观，
但是需要注意的是dsize与fx和fy必须不能同时为零，
也就是说要么dsize不为零而fx与fy同时可以为0，要么dsize为0而fx与fy不同时为0；
resize函数的目标大小可以是任意的大小，可以不保持长宽比率，
删除的像素或者新增的像素值通过interpolation（内插）控制； 
fx，fy分别指水平和垂直方向的比率；
如果dsize 为零，则目标图像的大小是通过这两个参数来计算的：
目标图像的宽度为原图像的宽度*fx,同理目标图像的高度为原图像的高度*fy; 
如果dsize不为零,fx,fy会自动计算： fx=dsize.width/src.cols; fy=dsize.height/src.rows; 
因此dsize和（fx,fy）只需设置其中一个，另外一个置为零就可以了。
interpolation取值： INTER_NN - 最近邻插值。 INTER_LINEAR - 双线性插值 (缺省使用)。 
INTER_AREA - 使用象素关系重采样。
当图像缩小时候，该方法可以避免波纹出现。
当图像放大时，类似于 INTER_NN 方法。 INTER_CUBIC - 立方插值。
*/
int main()
{
	Mat src_img, des_img0;
	
	string path = "E:\\Visual Studio 2010\\Projects\\opencv_2018_12_21\\opencv_2018_12_21\\1.jpg";
	src_img = imread(path, IMREAD_COLOR);
	if (src_img.empty())
	{
		cout << "imread file failed" << endl;
	}
	cout <<"src_img.type():"<< src_img.type() << endl;
	Mat des_img1(src_img.rows*0.5, src_img.cols*0.5, src_img.type());
	namedWindow("src_img", WINDOW_AUTOSIZE);
	imshow("src_img", src_img);
	namedWindow("des_img1", WINDOW_AUTOSIZE);
	imshow("des_img1",des_img1);

	//
	
	//双线性插值
	resize(src_img,des_img0,Size(),0.5,0.5);
	//立方插值
	resize(src_img, des_img1, des_img1.size(), INTER_CUBIC);
	namedWindow("resize des_img0", WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
	namedWindow("resize des_img1", WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
	imshow("resize des_img0", des_img0);
	imshow("resize des_img1",des_img1);

	waitKey(0);
	system("pause");
	return 0;
}