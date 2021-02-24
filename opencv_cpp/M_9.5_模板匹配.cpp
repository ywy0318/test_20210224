/*
9.5模板匹配的概念与原理
模板匹配是一项在一幅图像中寻找与另外一幅模板图像最匹配(相似)部分的技术;
在opencv2和opencv3中,模板匹配由MatchTemplate()函数完成;
模板匹配不是基于直方图的,而是通过在输入图像上滑动图像块;
对实际的图像块和输入图像进行匹配的一种匹配方法;

实现模板匹配:matchTemplate()函数
matchTemplate()函数用于匹配出和模板重叠的图像区域
C++:void matchTemplate(InputArray image,InputArray temp1,OutputArray result,int method);
第一个参数:InputArray类型的image,待搜索的图像,需要为8位或者32位浮点型图像;
第二个参数:InputArray类型的temp1,搜索模板,需要和源图片有一样的数据类型,且尺寸不能大于源图像;
第三个参数:OutputArray类型的result,比较结果的映射图像;其必须为单通道,32位浮点型图像,如果
图像尺寸时W*H,而temp1尺寸时W*h,则此参数result一定是(W-w+1)*(H-h+1);
第四个参数:int类型的method,指定的匹配方法;

1.平方差匹配法 method=TM_SQDIFF
这类方法利用平方差进行匹配,最好匹配为0;若匹配越差,匹配值越大;
2.归一化平方差匹配法 method=TM_SQDIFF_NORMED
3.相关匹配法 method=TM_CCORR
这类方法采用模板和图像键的乘法操作,所以较大的数表示匹配程度较高,0表示最坏的匹配效果;
4.归一化相关匹配法 method=TM_CCORR_NORMED
5.系数匹配法 method=TM_CCOEFF
这类方法将模板对其均值的相对值与图像对其均值的相关值进行匹配,
1表示完美匹配,-1表示糟糕的匹配,而0表示没有任何相关性(随机序列)
6.归一化相关系数匹配法method=TM_CCOEFF_NORMED

通常,随着从简单的测量(平方差)到更复杂的测量(相关系数),可以获得越来越准确的匹配;
同时也会以越来越大的计算量为代价;
比较科学的办法是对所有这些办法多次测试实验,以便为自己的应用选择同时兼顾速度和精度
的最佳方案;
*/

#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
int g_nMatch_Method;
int g_nMaxTrackbarNum = 5;
void on_Matching(int ,void* );
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;
int main()
{
	src_img = imread("111temp.png", 1);//读入图片数据
	//src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	//图片需要修改
	dst_img = imread("111.png", 1);
	//dst_img = imread("lena.jpg",1);
	if (dst_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	namedWindow("src_img",WINDOW_AUTOSIZE);
	namedWindow("dst_img", WINDOW_AUTOSIZE);
	//创建滑动条并进行一次初始化
	createTrackbar("方法","src_img",&g_nMatch_Method,g_nMaxTrackbarNum,on_Matching);
	on_Matching(0,0);
	waitKey(0);
	return 0;
}
void on_Matching(int, void*)
{
	//给局部变量初始化
	src_img.copyTo(temp_img);
	//初始化用于结果输出的矩阵
	int resultImage_cols = src_img.cols - dst_img.cols + 1;
	int resultImage_rows = src_img.rows - dst_img.rows + 1;
	edge_img.create(resultImage_cols, resultImage_rows, CV_32FC1);
	//进行匹配和标准化
	matchTemplate(src_img,dst_img,edge_img,g_nMatch_Method);
	normalize(edge_img, edge_img,0,1,NORM_MINMAX,-1,Mat());

	//通过函数minMaxLoc定位最匹配的位置
	double minValue;
	double MaxValue;
	Point minLocation;
	Point maxLoaction;
	Point matchLocation;
	minMaxLoc(edge_img,&minValue,&MaxValue,&minLocation,&maxLoaction,Mat());

	//对于方法SQDIFF和SQDIFF_NORMED,越小的数值有着更高的匹配结果,而其余的方法,
	//数值越大匹配效果越好;
	if (g_nMatch_Method == TM_SQDIFF || g_nMatch_Method == TM_SQDIFF_NORMED)
	{
		matchLocation = minLocation;
	}
	else
	{
		matchLocation = maxLoaction;
	}

	//绘制出矩形,并显示最终结果
	rectangle(temp_img, matchLocation,Point(matchLocation.x+dst_img.cols,matchLocation.y+
	dst_img.rows),Scalar(0,0,255),2,8,0);

	rectangle(edge_img, matchLocation, Point(matchLocation.x + dst_img.cols, matchLocation.y +
		dst_img.rows), Scalar(0, 0, 255), 2, 8, 0);
	imshow("src_img",src_img);
	imshow("dst_img",dst_img);

}