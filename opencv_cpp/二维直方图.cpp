#include "opencv2/opencv.hpp"
using namespace cv;

void main()
{
	Mat src = imread("E:\\Visual Studio 2010\\Projects\\opencv\\opencv\\cat1.jpg");
	Mat hsv;
	int Bbins = 256, Gbins = 256;
	int histSize[] = { Bbins, Gbins };
	float hranges[] = { 0, 256 };
	float sranges[] = { 0, 256 };
	const float* ranges[] = { hranges, sranges };
	Mat hist;

	int channels[] = { 0, 1 };
	calcHist(&src, 1, channels, Mat(), hist, 2, histSize, ranges);
	double maxVal = 0;
	minMaxLoc(hist, 0, &maxVal, 0, 0);
	int scale = 2;
	Mat histImg = Mat::zeros(Bbins*(scale), Bbins*(scale), CV_8UC3);
	for (int h = 0; h < Bbins; h++)
		for (int s = 0; s < Bbins; s++)
		{
			float binVal = hist.at<float>(h, s);
			//cout<<"h="<<h<<"s="<<s<<"binValue="<<binVal<<endl;
			//int intensity = cvRound(binVal*255/maxVal);
			int intensity = int(binVal * 255 / maxVal);
			rectangle(histImg, Point(h*scale, s*scale),
				Point((h + 1)*scale - 1, (s + 1)*scale - 1),
				Scalar::all(intensity), CV_FILLED);
		}
	namedWindow("Source", 1);
	imshow("Source", src);
	namedWindow("B-G Histogram", 1);
	imshow("B-G Histogram", histImg);

	waitKey(0);
	destroyAllWindows();

}