/*
图像一维直方图的计算和绘制过程
*/
#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
Mat src_img, dst_img, gray_img, mask_img, edge_img, temp_img;

void HIST_1D()
{
	//定义变量
	MatND dst_Hist;//CV中CVHistogram *hist=cvCreateHist
	int dims = 1;
	float hrange[] = { 0,255 };
	const float *ranges[] = { hrange };//const类型
	int size = 256;
	int channels = 0;
	//计算图像的直方图,cv中是cvCalcHist
	calcHist(&src_img, 1, &channels, Mat(), dst_Hist, dims, &size, ranges);
	int scale = 1;
	Mat dstimage(size*scale, size, CV_8U, Scalar(0));
	//获取最大值和最小值
	double minValue = 0;
	double maxValue = 0;
	minMaxLoc(dst_Hist, &minValue, &maxValue, 0, 0);
	//绘制出直方图
	int hpt = saturate_cast<int>(0.9*size);
	for (size_t i = 0; i < 256; i++)
	{
		float binValue = dst_Hist.at<float>(i);//hist中是float类型
		int realValue = saturate_cast<int>(binValue*hpt / maxValue);
		rectangle(dstimage, Point(i*scale, size - 1), Point((i + 1)*scale - 1, size - realValue), Scalar(255));
	}
	imshow("一维直方图", dstimage);
	waitKey();
}

void HIST_RGB()
{
	//参数准备
	int bins_rgb = 256;
	int hist_size_rgb[] = { bins_rgb };
	float range_rgb[] = {0,256};
	const float* ranges_rgb[] = { range_rgb };
	MatND redHist, grayHist, blueHist;
	int channels_r[] = { 0 };
	int channels_g[] = { 1 };
	int channels_b[] = { 2 };
	//进行直方图的计算(红色分量部分)//不使用掩码
	calcHist(&src_img,1,channels_r,Mat(),redHist,1,hist_size_rgb,ranges_rgb,true,false);
	//进行直方图的计算(绿色分量部分)//不使用掩码
	calcHist(&src_img, 1, channels_g, Mat(), grayHist, 1, hist_size_rgb, ranges_rgb, true, false);
	//进行直方图的计算(蓝色分量部分)//不使用掩码
	calcHist(&src_img, 1, channels_b, Mat(), blueHist, 1, hist_size_rgb, ranges_rgb, true, false);

	//绘制出三色直方图
	double maxValue_red, maxValue_green, maxValue_blue;
	minMaxLoc(redHist,0,&maxValue_red,0,0);
	minMaxLoc(grayHist, 0, &maxValue_green, 0, 0);
	minMaxLoc(blueHist, 0, &maxValue_blue, 0, 0);
	int scale = 1;
	int hist_Height = 256;
	Mat histImage = Mat::zeros(hist_Height, bins_rgb*3,CV_8UC3);

	//正式开始绘制
	for (size_t i = 0; i < bins_rgb; i++)
	{
		//参数准备
		float binValue_red = redHist.at<float>(i);
		float binValue_green = grayHist.at<float>(i);
		float binValue_blue = blueHist.at<float>(i);

		int intensity_red = cvRound(binValue_red*hist_Height/maxValue_red);//要绘制的高度
		int intensity_green = cvRound(binValue_green*hist_Height / maxValue_green);//要绘制的高度
		int intensity_blue = cvRound(binValue_blue*hist_Height / maxValue_blue);//要绘制的高度

		rectangle(histImage,Point(i*scale,hist_Height-1),Point((i+1)*scale-1,hist_Height-intensity_red),Scalar(255,0,0));
		rectangle(histImage, Point((i+bins_rgb)*scale, hist_Height - 1), Point((i + 1 + bins_rgb)*scale - 1, hist_Height - intensity_green), Scalar(0, 255, 0));
		rectangle(histImage, Point((i + bins_rgb*2)*scale, hist_Height - 1), Point((i + 1 + bins_rgb*2)*scale - 1, hist_Height - intensity_blue), Scalar(0, 0, 255));
	}	
	imshow("RGB_HIST", histImage);
	waitKey();
	return;
}
int main()
{

	src_img = imread("lena.jpg", 1);//读入图片数据
	if (src_img.empty())
	{
		cout << "can not open or find the img" << endl;
		return -1;
	}
	HIST_RGB();
	return 0;
}