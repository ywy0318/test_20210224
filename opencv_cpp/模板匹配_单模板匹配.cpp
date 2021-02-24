#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;
//ע�⣺result�ĳ���������ԭͼ-ģ��ͼ�ĳ���resultͼ�а����̶ȱ�ʾƥ��̶�
void main()
{
	Mat temp = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg");
	Mat src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\0.jpg");
	Mat dst = src.clone();
	imshow("temp", temp);

	int width = src.cols - temp.cols + 1;//result���
	int height = src.rows - temp.rows + 1;//result�߶�

	Mat result(height, width, CV_32FC1);//�������ӳ��ͼ��
	//matchTemplate(srcImg, templateImg, resultImg, CV_TM_SQDIFF); //ƽ����ƥ�䷨(���ƥ��0)
	//matchTemplate(srcImg, templateImg, resultImg, CV_TM_SQDIFF_NORMED); //��һ��ƽ����ƥ�䷨(���ƥ��0)
	//matchTemplate(srcImg, templateImg, resultImg, CV_TM_CCORR); //���ƥ�䷨(�ƥ��0)
	//matchTemplate(srcImg, templateImg, resultImg, CV_TM_CCORR_NORMED); //��һ�����ƥ�䷨(�ƥ��0)
	//matchTemplate(srcImg, templateImg, resultImg, CV_TM_CCOEFF); //ϵ��ƥ�䷨(���ƥ��1)
	matchTemplate(src, temp, result, CV_TM_CCOEFF_NORMED);//�����ϵ��ƥ��,���ֵ1

	imshow("result", result);
	normalize(result, result, 0, 1, NORM_MINMAX, -1);//��һ����0-1��Χ

	double minValue, maxValue;
	Point minLoc, maxLoc;
	minMaxLoc(result, &minValue, &maxValue, &minLoc, &maxLoc);
	cout << "minValue=" << minValue << endl;
	cout << "maxValue=" << maxValue << endl;

	rectangle(dst, maxLoc, Point(maxLoc.x + temp.cols, maxLoc.y + temp.rows), Scalar(0, 255, 0), 2, 8);
	imshow("dst", dst);

	waitKey(0);
}