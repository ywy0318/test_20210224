/*
综合实例:边缘检测
分别演示了canny边缘检测，sobel边缘检测，scharr滤波器

*/
#include<iostream>
#include<opencv2\opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;

Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;
//Canny边缘检测相关变量
Mat g_cannyDetectededges;
int g_cannyLowThreshold = 1;//TrackBar位置参数

//Sobel边缘检测相关变量
Mat g_sobelGradient_x, g_sobelGradient_y;
Mat g_sobelAbsGradient_x, g_sobelAbsGradient_y;
int g_sobelKernelSize = 1;//TrackBar位置参数

//Scharr滤波器相关变量
Mat g_scharrGradient_x, g_scharrGradient_y;
Mat g_scharrAbsGradient_x, g_scharrAbsGradient_y;

static void on_Canny(int ,void*);//Canny边缘检测窗口滚动条的回调函数
static void on_Sobel(int, void*);//Sobel边缘检测窗口滚动条的回调函数
void on_Scharr();//封装了边缘检测相关代码的函数


int main()
{
	//改变console字体颜色
	system("color 2F");
	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	namedWindow("src_img",WINDOW_AUTOSIZE);
	imshow("src_img", src_img);

	//创建与src同类型和大小的矩阵(dst)
	dst_img.create(src_img.size(),src_img.type());
	//将源图像转换为灰度图像
	cvtColor(src_img,gray_img,COLOR_BGR2GRAY);

	namedWindow("Canny",WINDOW_AUTOSIZE);
	namedWindow("Sobel", WINDOW_AUTOSIZE);
	namedWindow("Scharr", WINDOW_AUTOSIZE);

	createTrackbar("参数值:","Canny",&g_cannyLowThreshold,120,on_Canny);
	createTrackbar("参数值","Sobel",&g_sobelKernelSize,3,on_Sobel);

	//调用回调函数
	on_Canny(0,0);
	on_Sobel(0,0);
	//调用封装了Scharr边缘检测代码的函数 
	on_Scharr();
	waitKey(0);
	while (true)
	{

	}

	
	cout << CV_MAJOR_VERSION << endl;
	system("pause");
	return 0;
}
void on_Canny(int ,void*)
{
	//先使用3*3内核来降噪
	blur(gray_img,g_cannyDetectededges,Size(3,3));
	//运行我们的Canny算子
	Canny(g_cannyDetectededges,g_cannyDetectededges,g_cannyLowThreshold,g_cannyLowThreshold*3,3);
	
	//先将dst_img内的所有元素设置为0
	dst_img = Scalar::all(0);
	//使用Canny算子输出的边缘图g_cannyDetechedEgdes作为掩码,来将原图g_src_img,拷到
	//目标图g_dstimg中
	src_img.copyTo(dst_img,g_cannyDetectededges);
	imshow("Canny",dst_img);
	waitKey(0);
}
void on_Sobel(int, void*)
{
	//求x方向梯度
	Sobel(src_img, g_sobelGradient_x,CV_16S,1,0,(2*g_sobelKernelSize+1),1,1,BORDER_DEFAULT);
	convertScaleAbs(g_sobelGradient_x,g_sobelAbsGradient_x);

	//求Y方向梯度
	Sobel(src_img, g_sobelGradient_y, CV_16S, 0, 1, (2 * g_sobelKernelSize + 1), 1, BORDER_DEFAULT);
	convertScaleAbs(g_sobelGradient_y,g_sobelAbsGradient_y);

	//合并梯度
	addWeighted(g_sobelAbsGradient_x,0.5, g_sobelAbsGradient_y,0.5,0,dst_img);
	imshow("Sobel",dst_img);
	waitKey(0);
}

void on_Scharr( )
{
	//求x方向梯度
	Sobel(src_img, g_scharrGradient_x, CV_16S, 1, 0, (2 * g_sobelKernelSize + 1), 1, 1, BORDER_DEFAULT);
	convertScaleAbs(g_scharrGradient_x, g_scharrAbsGradient_x);

	//求Y方向梯度
	Sobel(src_img, g_scharrGradient_y, CV_16S, 0, 1, (2 * g_sobelKernelSize + 1), 1, BORDER_DEFAULT);
	convertScaleAbs(g_scharrGradient_y, g_scharrAbsGradient_y);

	//合并梯度
	addWeighted(g_scharrAbsGradient_x, 0.5, g_scharrAbsGradient_y, 0.5, 0, dst_img);
	imshow("Scharr", dst_img);
	waitKey(0);
}
