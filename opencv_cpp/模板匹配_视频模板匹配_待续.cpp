#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

void main()
{
	Mat frame, resultImg;
	Mat templateImg = imread("E://green.jpg");
	VideoCapture cap("E://1.mp4");
	if (!cap.isOpened())
		return;
	int resultImg_cols, resultImg_rows;

	while (1)
	{
		cap >> frame;
		if (frame.empty())    break;
		Mat showImg = frame.clone();
		resultImg_cols = frame.cols - templateImg.cols + 1;
		resultImg_rows = frame.rows - templateImg.rows + 1;
		resultImg.create(resultImg_cols, resultImg_rows, CV_32FC1);
		matchTemplate(frame, templateImg, resultImg, CV_TM_CCOEFF_NORMED); //化相关系数匹配法(最好匹配1)
		normalize(resultImg, resultImg, 0, 1, NORM_MINMAX);

		double minValue, maxValue;
		Point minLoc, maxLoc;
		Point matchLoc;

		minMaxLoc(resultImg, &minValue, &maxValue, &minLoc, &maxLoc);
		cout << "max_value= " << maxValue << endl;
		//cout<<"min_value= "<<minValue<<endl;
		if (maxValue >= 0.7)
			rectangle(showImg, maxLoc, Point(maxLoc.x + templateImg.cols, maxLoc.y + templateImg.rows), Scalar(0, 255, 0), 2);
		imshow("frame", frame);
		imshow("result", showImg);
		if (27 == waitKey(10))
			break;
	}
	destroyAllWindows();

	waitKey(0);
}