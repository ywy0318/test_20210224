#include "opencv2/opencv.hpp"
using namespace cv;
//using namespace std;
void main()
{
	//{//���⻯����Ҫ����}
		Mat srcImg = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\1.jpg", 0);  //�ԻҶȷ�ʽ�򿪣���Ҫ���뵥ͨ��ͼ��
		imshow("src", srcImg);
		Mat dstImg;  //���⻯���ͼ��
		equalizeHist(srcImg, dstImg);
		imshow("dst", dstImg);
	//	{//���⻯����Ҫ����}

	//����srcֱ��ͼ
	MatND dstHist;  //����洢ֱ��ͼ����
	int dims = 1;  //��Ҫͳ�Ƶ�������Ŀ(ֻͳ�ƻҶ�ֵ)
	float hranges[] = { 0, 256 };  //��Χ[0,256)ע�������ֵ��1
	const float* ranges[] = { hranges };
	int bins = 256;
	int channels = 0;
	calcHist(&srcImg, 1, &channels, Mat(), dstHist, dims, &bins, ranges);
	int scale = 1;
	Mat HistImg(bins * scale, bins * 1, CV_8UC3, Scalar(0));  //����ֱ��ͼ���ͼ��
	double minValue = 0;
	double maxValue = 0;
	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);
	int hpt = saturate_cast<int>(0.9*bins);  //�������ֵ����ֹ���
	int j = 0;
	for (int i = 0; i<256; i++)
	{
		float binValue = dstHist.at<float>(i);
		int realValue = saturate_cast<int>(binValue*hpt / maxValue);  //��һ������
		line(HistImg, Point(i*scale, bins - 1), Point(i*scale, bins - realValue), Scalar(0, 255, 0), 1, 8);
	}
	imshow("src_hist", HistImg);

	//����dstֱ��ͼ
	calcHist(&dstImg, 1, &channels, Mat(), dstHist, dims, &bins, ranges);
	Mat HistImg2(bins * scale, bins * 1, CV_8UC3, Scalar(0));  //����ֱ��ͼ���ͼ��
	for (int i = 0; i<256; i++)
	{
		float binValue = dstHist.at<float>(i);
		int realValue = saturate_cast<int>(binValue*hpt / maxValue);  //��һ������
		line(HistImg2, Point(i*scale, bins - 1), Point(i*scale, bins - realValue), Scalar(0, 255, 0), 1, 8);
	}
	imshow("dst_hist", HistImg2);

	waitKey(0);
}