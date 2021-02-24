#include "opencv2/opencv.hpp"
using namespace cv;

#define WINDOW_NAME "��ԭʼͼ��" 
Mat g_hueImage;
int g_bins = 30;//ֱ��ͼ���

void on_BinChange(int, void*)
{
	MatND hist;
	int histSize = MAX(g_bins, 2);
	float hue_range[] = { 0, 180 };
	const float* ranges = { hue_range };
	calcHist(&g_hueImage, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false);
	normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());

	MatND backproj;
	calcBackProject(&g_hueImage, 1, 0, hist, backproj, &ranges, 1, true);
	imshow("����ͶӰͼ", backproj);

	int w = 400; int h = 400;
	int bin_w = cvRound((double)w / histSize);
	Mat histImg = Mat::zeros(w, h, CV_8UC3);
	for (int i = 0; i < g_bins; i++)
	{
		rectangle(histImg, Point(i*bin_w, h), Point((i + 1)*bin_w, h - cvRound(hist.at<float>(i)*h / 255.0)), Scalar(100, 123, 255), -1);
	}
	imshow("ֱ��ͼ", histImg);
}

void main()
{
	Mat g_srcImage = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\11.jpg");
	Mat g_hsvImage;
	resize(g_srcImage, g_srcImage, Size(g_srcImage.cols / 4, g_srcImage.rows / 4));//ԭͼ̫�󣬽�������
	cvtColor(g_srcImage, g_hsvImage, CV_BGR2HSV);

	g_hueImage.create(g_hsvImage.size(), g_hsvImage.depth());
	int ch[] = { 0, 0 };
	mixChannels(&g_hsvImage, 1, &g_hueImage, 1, ch, 1);//�������п���ĳͨ����������ض���ͨ��

	namedWindow(WINDOW_NAME, CV_WINDOW_AUTOSIZE);
	createTrackbar("ɫ����� ", WINDOW_NAME, &g_bins, 180, on_BinChange);
	on_BinChange(0, 0);

	imshow(WINDOW_NAME, g_srcImage);
	waitKey(0);
}