#include "opencv2/opencv.hpp"
#include<iostream> 
#include <opencv2/core/core.hpp> 
using namespace cv;
using namespace std;
int main()
{
	Mat src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\8.jpg");

	if(src== NULL)
	{
		cout << "src is null" << endl;
		return -1;
	}

	int bins = 256;
	int hist_size[] = { bins };
	float range[] = { 0, 256 };
	const float* ranges[] = { range };
	Mat hist_r, hist_g, hist_b;

	int channels_r[] = { 2 };
	calcHist(&src, 1, channels_r, Mat(), // do not use mask
		hist_r, 1, hist_size, ranges,
		true, // the histogram is uniform
		false);

	int channels_g[] = { 1 };
	calcHist(&src, 1, channels_g, Mat(), hist_g, 1, hist_size, ranges, true, false);
	int channels_b[] = { 0 };
	calcHist(&src, 1, channels_b, Mat(), hist_b, 1, hist_size, ranges, true, false);

	double max_val_r, max_val_g, max_val_b;
	minMaxLoc(hist_r, 0, &max_val_r, 0, 0);
	minMaxLoc(hist_g, 0, &max_val_g, 0, 0);
	minMaxLoc(hist_b, 0, &max_val_b, 0, 0);
	int scale = 1;
	int hist_height = 256;
	Mat hist_img = Mat::zeros(hist_height, bins * 3 + 5, CV_8UC3);
	for (int i = 0; i<bins; i++)
	{
		float bin_val_r = hist_r.at<float>(i);
		float bin_val_g = hist_g.at<float>(i);
		float bin_val_b = hist_b.at<float>(i);
		int intensity_r = cvRound(bin_val_r*hist_height / max_val_r);  //要绘制的高度
		int intensity_g = cvRound(bin_val_g*hist_height / max_val_g);  //要绘制的高度
		int intensity_b = cvRound(bin_val_b*hist_height / max_val_b);  //要绘制的高度
		rectangle(hist_img, Point(i*scale, hist_height - 1),
			Point((i + 1)*scale - 1, hist_height - intensity_r),
			CV_RGB(255, 0, 0));

		rectangle(hist_img, Point((i + bins)*scale, hist_height - 1),
			Point((i + bins + 1)*scale - 1, hist_height - intensity_g),
			CV_RGB(0, 255, 0));

		rectangle(hist_img, Point((i + bins * 2)*scale, hist_height - 1),
			Point((i + bins * 2 + 1)*scale - 1, hist_height - intensity_b),
			CV_RGB(0, 0, 255));

	}
	imshow("src", src);
	imshow("RGB Histogram", hist_img);

	waitKey(0);
	destroyAllWindows();
	return 1;

}